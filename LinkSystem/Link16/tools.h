#pragma once
#include <string>
#include "Word.hpp"
#include "InitialWord.h"
#include "ExtendWord.h"
#include "ContinueWord.h"
#include "HeaderWord.h"
#include "CRC.h"
#include "AES.h"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <unistd.h>

#define NO_GFLUT
#include "schifra_galois_field.hpp"
#undef NO_GFLUT
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"
#include "schifra_reed_solomon_bitio.hpp"

namespace Tools {
	//encode tools
	inline void save_msg(const string& msg);
	inline bool deleteFile();
	inline string generateBIN(int length);
	inline vector<string> stringSplit(const string& str, char delim);
	inline string StrToBitStr(const string& str);
	inline string BitStrTostr(const string& str);
	inline uint8_t* StrToCharArray(string& str_data, int char_length);
	inline void BIP(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword);
	inline void AES_Encrypt(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword);
	inline void weave(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword);
	inline void handlerSTDP(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword);

	//decode tools
	inline string read_msg();
	inline string getGroup(string& bit_data);
	inline void StrToSymbol(symbol* stdp, size_t length, string& message);
	inline string decode_weave(string& raw_msg);
	inline string decode_RS_code_16_7(symbol* head);
	inline string decode_RS_code_31_15(symbol* head);
	inline string decode_RS_AES_BIP_handler(string& message);
	inline int decode_RS(string& message, string& str_data);
	inline string AES_Decrypt(string& char_data);
	inline bool decode_BIP(string& bit_str);
}

inline int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_RS_word);

namespace Tools {
	void save_msg(const string& msg) {
		std::cout << "A STDP message has been successfully sent" << std::endl;
		ofstream fout;
		fout.open(FILENAME, ios::app);
		if (fout.is_open() == false) {
			std::cout << "Open file " << FILENAME << " Failed" << std::endl;
			return;
		}

		//��????????????
		fout << msg;
		fout.close();
		return;
	}

	//?��??????????????????????
	bool deleteFile() {
		if (access(FILENAME, F_OK) == 0) {
			if (remove(FILENAME) == 0) {
				std::cout << "File successfully deleted" << std::endl;
				return true;
			}
			else {
				std::cout << "File failed deleted" << std::endl;
				return false;
			}
		}
		return true;
	}

	//?????????????????
	string generateBIN(int length) {
		string res;
		for (int i = 0; i < length; i++) {
			res += to_string(rand() % 2);
		}
		return res;
	}

	vector<string> stringSplit(const string& str, char delim) {
		std::stringstream ss(str);
		string item;
		vector<std::string> elems;
		while (getline(ss, item, delim)) {
			if (!item.empty()) {
				elems.push_back(item);
			}
		}
		return elems;
	}

	string StrToBitStr(const string& str) {
		size_t len = str.length();
		string res;
		for (size_t i = 0; i < len; i++) {
			bitset<8> bits = bitset<8>(str[i]);
			res += bits.to_string();
		}
		return res;
	}

	string BitStrTostr(const string& str) {
		size_t len = str.length();
		string res;
		for (size_t i = 0; i < len; i = i + 8) {
			string tmp;
			for (size_t j = 0; j < 8; j++) {
				tmp += str[i + j];
			}
			bitset<8> ch = bitset<8>(tmp);
			res += (char)ch.to_ulong();
		}
		return res;
	}

	//?????????str_data????????8????????
	//????????????????????0000000100000010????8bit????????{ "1", "2" }?????????
	uint8_t* StrToCharArray(string& str_data, int char_length) {
		size_t len = str_data.length();
		if (len % 8 != 0) {
			std::cout << "The string length is error??must be a multiple of 8bit";
			return nullptr;
		}
		uint8_t* data = new uint8_t[char_length]();
		for (int i = 0; i < char_length; i++) {
			bitset<8> tmp = bitset<8>(str_data.substr(i * 8, 8));
			data[i] = static_cast<uint8_t>(tmp.to_ulong());
		}
		return data;
	}

	//???CRC???????��??(???CRCpp??)
	void BIP(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword) {
		string str_data = hword.toString_15B() + iword.toString_70B() + eword.toString_70B() + cword.toString_70B();
		//CRC(237, 225)??225bit???29Bytes???
		str_data += "0000000";
		uint8_t* data = StrToCharArray(str_data, 29);
		if (data == nullptr) {
			return;
		}
		std::uint16_t crc = CRC::CalculateBits(data, 225, CRC::CRC_12_CDMA2000());
		bitset<16> bit_crc = bitset<16>(crc);
		iword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(4, 4)));
		eword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(8, 4)));
		cword.setBIP(bitset<5>("0" + bit_crc.to_string().substr(12, 4)));

		delete[] data;
		data = nullptr;
	}

	void AES_Encrypt(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword) {
		string message = hword.toString() + iword.toString()
			+ eword.toString() + cword.toString();
		//????? = 75 + 75 + 75 + 35 = 260bit??????AES???????????????????256bit?????

		string str_data = message.substr(0, 256);
		uint8_t* plain = StrToCharArray(str_data, 32);

		AES aes(AESKeyLength::AES_256);
		const uint8_t key_16[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
							 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
							 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
							 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
		uint8_t* out = aes.EncryptECB(plain, BLOCK_BYTES_LENGTH * 2, key_16);

		delete[] plain;
		plain = nullptr;

		string tmp;
		for (int i = 0; i < 32; i++) {
			tmp += out[i];
		}

		string bit_str = StrToBitStr(tmp) + message.substr(256, 4);

		delete[] out;
		out = nullptr;

		//??AES??????????????��???
		string bit_header = bit_str.substr(0, 35);
		hword.rewrite(bit_header);

		//??AES??????????????��????
		string bit_iword = bit_str.substr(35, 75);
		iword.rewrite(bit_iword);
		string bit_eword = bit_str.substr(110, 75);
		eword.rewrite(bit_eword);
		string bit_cword = bit_str.substr(185, 75);
		cword.rewrite(bit_cword);
	}

	//???????109Symbol????????????��??��????��??12 x 9???????????Symbol?????????,????????��??��?????????
	void weave(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword) {
		symbol* bit_data = new symbol[108];
		symbol* RS_Header = hword.getRS_word();
		symbol* RS_iword = iword.getRS_word();
		symbol* RS_eword = eword.getRS_word();
		symbol* RS_cword = cword.getRS_word();

		for (int i = 0; i < 108; i++) {
			if (i < 16) {
				bit_data[i] = RS_Header[i];
			}
			else if (i >= 16 && i < 47) {
				bit_data[i] = RS_iword[i - 16];
			}
			else if (i >= 47 && i < 78) {
				bit_data[i] = RS_eword[i - 47];
			}
			else {
				bit_data[i] = RS_cword[i - 78];
			}
		}

		symbol** matrix = new symbol * [12];
		for (int i = 0; i < 12; i++) {
			matrix[i] = new symbol[9];
			for (int j = 0; j < 9; j++) {
				matrix[i][j] = bit_data[i * 9 + j];
			}
		}

		//????
		string res;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 12; j++) {
				res += matrix[j][i].to_string();
			}
		}
		res += RS_cword[30].to_string();
		std::cout << "======The interweave STDP message is as follows:======\n";
		std::cout << res << std::endl;
		save_msg(res);

		//??????
		delete[] bit_data;
		bit_data = nullptr;

		for (int i = 0; i < 12; i++) {
			delete[] matrix[i];
			matrix[i] = nullptr;
		}
		delete[] matrix;
		matrix = nullptr;
	}

	void handlerSTDP(HeaderWord& hword, InitialWord& iword,
		ExtendWord& eword, ContinueWord& cword) {
		//??????��?�70bit -> 75bit
		std::cout << "======" << "Starting parity check" << "======" << std::endl;
		Tools::BIP(hword, iword, eword, cword);

		//???????
		std::cout << "======" << "Starting AES encryption" << "======" << std::endl;
		Tools::AES_Encrypt(hword, iword, eword, cword);

		//Symbol???????????RS????
		hword.to_symbol();
		std::cout << "======" << "HeaderWord executes RS error correction encoding. 7Symbol --> 16Symbol" << "======" << std::endl;
		hword.RS_handler();

		iword.to_symbol();
		std::cout << "======" << "InitialWord executes RS error correction encoding. 15Symbol --> 31Symbol" << "======" << std::endl;
		iword.RS_handler();

		eword.to_symbol();
		std::cout << "======" << "ExtendWord executes RS error correction encoding. 15Symbol --> 31Symbol" << "======" << std::endl;
		eword.RS_handler();

		cword.to_symbol();
		std::cout << "======" << "ContinueWord executes RS error correction encoding. 15Symbol --> 31Symbol" << "======" << std::endl;
		cword.RS_handler();

		//?????????
		std::cout << "======" << "Start performing character interleaving" << "======" << std::endl;
		Tools::weave(hword, iword, eword, cword);
	}

	string read_msg() {
		ifstream fin;
		fin.open(FILENAME, ios::in);
		if (fin.is_open() == false) {
			std::cout << "Open file" << FILENAME << "Failed" << std::endl;
			return "";
		}
		//??��????
		string buffer;
		std::cout << "The data read from the txt document is as follows:" << std::endl;
		while (fin >> buffer) {
			std::cout << buffer << std::endl;
		}
		fin.close();
		return buffer;
	}

	string getGroup(string& bit_data) {
		string group = bit_data.substr(0, 545);
		bit_data.erase(0, 545);
		return group;
	}

	//?????stdp??????????symbol?????????
	void StrToSymbol(symbol* stdp, size_t length, string& message) {
		for (size_t i = 0; i < length; i++) {
			stdp[i] = bitset<5>(message.substr(i * 5, 5));
		}
	}

	//raw_msg????????545
	string decode_weave(string& raw_msg) {
		symbol* bit_data = new symbol[108];
		StrToSymbol(bit_data, 108, raw_msg);

		symbol** matrix = new symbol * [9];
		for (size_t i = 0; i < 9; i++) {
			matrix[i] = new symbol[12];
			for (size_t j = 0; j < 12; j++) {
				matrix[i][j] = bit_data[i * 12 + j];
			}
		}

		string res;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 9; j++) {
				res += matrix[j][i].to_string();
			}
		}
		res += raw_msg.substr(540, 5);

		//??????
		delete[] bit_data;
		bit_data = nullptr;

		for (int i = 0; i < 9; i++) {
			delete[] matrix[i];
			matrix[i] = nullptr;
		}
		delete[] matrix;
		matrix = nullptr;
		return res;
	}

	//????HeaderWord
	string decode_RS_code_16_7(symbol* head) {
		string str_hword(code_31_15, 0x00);
		for (int i = 0; i < data_16_7; i++) {
			str_hword[i] = static_cast<char>(head[i].to_ulong());
		}
		for (int i = data_31_15 + 7; i < code_31_15; i++) {
			str_hword[i] = static_cast<char>(head[i - data_31_15].to_ulong());
		}
		string hword_data(data_31_15, 0x00);
		if (!decode_RS(str_hword, hword_data)) {
			std::cout << "RS decoding successful" << std::endl;
		}
		else {
			std::cout << "RS decoding failed" << std::endl;
		}
		hword_data.erase(data_16_7, 8);
		return hword_data;
	}

	//????Word
	string decode_RS_code_31_15(symbol* head) {
		string str_word(code_31_15, 0x00);
		for (int i = 0; i < code_31_15; i++) {
			str_word[i] = static_cast<char>(head[i].to_ulong());
		}
		string word_data(data_31_15, 0x00);
		if (!decode_RS(str_word, word_data)) {
			std::cout << "RS decoding successful" << std::endl;
		}
		else {
			std::cout << "RS decoding failed" << std::endl;
		}
		return word_data;
	}

	//message????????545
	string decode_RS_AES_BIP_handler(string& message) {
		if (message.length() != 545) {
			std::cout << "Incorrect STDP message format" << std::endl;
			return "";
		}
		symbol* stdp = new symbol[109];
		StrToSymbol(stdp, 109, message);
		string char_data;

		//????HeaderWord
		symbol* hword = stdp;
		char_data += decode_RS_code_16_7(hword);

		//????InitialWord
		symbol* iword = hword + code_16_7;
		char_data += decode_RS_code_31_15(iword);

		//????ExtendWord
		symbol* eword = iword + code_31_15;
		char_data += decode_RS_code_31_15(eword);

		//????ContinueWord
		symbol* cword = eword + code_31_15;
		char_data += decode_RS_code_31_15(cword);

		//??????
		delete[] stdp;
		stdp = nullptr;

		//AES????
		string bit_data = AES_Decrypt(char_data);

		//BIP???��??
		if (!decode_BIP(bit_data)) {
			std::cout << "BIP parity error" << std::endl;
			return "";
		}

		return bit_data;
	}

	string AES_Decrypt(string& char_data) {
		string str_data;
		for (auto i : char_data)
		{
			bitset<5> bs(i);
			str_data += bs.to_string();
		}

		string ciper_data = str_data.substr(0, 256);
		uint8_t* cipher = Tools::StrToCharArray(ciper_data, 32);

		AES aes(AESKeyLength::AES_256);
		const uint8_t key_16[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
							 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
							 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
							 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
		uint8_t* plain = aes.DecryptECB(cipher, BLOCK_BYTES_LENGTH * 2, key_16);

		delete[] cipher;
		cipher = nullptr;

		string tmp;
		for (int i = 0; i < 32; i++) {
			tmp += plain[i];
		}

		delete[] plain;
		plain = nullptr;

		string bit_str = Tools::StrToBitStr(tmp) + str_data.substr(256, 4);
		return bit_str;
	}

	//message????????char
	int decode_RS(string& message, string& str_data) {
		/* Finite Field Parameters */
		const std::size_t field_descriptor = 5;
		const std::size_t generator_polynomial_index = 0;
		const std::size_t generator_polynomial_root_count = 16;

		/* Reed Solomon Code Parameters */
		const std::size_t code_length = RS_Length::code_31_15; //(2^5 - 1)
		const std::size_t data_length = RS_Length::data_31_15;
		const std::size_t fec_length = RS_Length::fec_31_15;

		/* 5-bit Symbol Parameter */
		const int mask = 0x0000001F;

		/* Instantiate Finite Field and Generator Polynomials */
		const schifra::galois::field field(field_descriptor,
			schifra::galois::primitive_polynomial_size02,
			schifra::galois::primitive_polynomial02);

		schifra::galois::field_polynomial generator_polynomial(field);

		if (
			!schifra::make_sequential_root_generator_polynomial(field,
				generator_polynomial_index,
				generator_polynomial_root_count,
				generator_polynomial)
			)
		{
			std::cout << "Error - Failed to create sequential root generator!" << std::endl;
			return 1;
		}

		/* Instantiate Encoder and Decoder (Codec) */
		typedef schifra::reed_solomon::decoder<code_length, fec_length> decoder_t;

		const decoder_t decoder(field, generator_polynomial_index);

		string data = message.substr(0, 15);
		string fec = message.substr(15, 16);
		/* Instantiate RS Block For Codec */
		schifra::reed_solomon::block<code_length, fec_length> block(data, fec);

		if (!decoder.decode(block))
		{
			std::cout << "Error - Critical decoding failure! "
				<< "Msg: " << block.error_as_string() << std::endl;
			return 1;
		}
		block.data_to_string(str_data);
		return 0;
	}

	bool decode_BIP(string& bit_str) {
		string str_data = bit_str.substr(4, 15) + bit_str.substr(35, 70) + bit_str.substr(35 + 75, 70)
			+ bit_str.substr(35 + 75 * 2, 70);
		string str_BIP = bit_str.substr(35 + 70, 5) + bit_str.substr(35 + 75 + 70, 5)
			+ bit_str.substr(35 + 75 * 2 + 70, 5);
		str_data += "0000000";

		uint8_t* data = Tools::StrToCharArray(str_data, 29);
		if (data == nullptr) {
			return false;
		}
		std::uint16_t crc = CRC::CalculateBits(data, 225, CRC::CRC_12_CDMA2000());
		bitset<16> bit_crc = bitset<16>(crc);

		string str_BIP_cmp = "0" + bit_crc.to_string().substr(4, 4) + "0" + bit_crc.to_string().substr(8, 4)
			+ "0" + bit_crc.to_string().substr(12, 4);
		return (str_BIP_cmp == str_BIP) ? true : false;
	}
}

int RS(const size_t codeLength, const size_t dataLength, string& message, symbol* symbol_msg) {
	/* Finite Field Parameters */
	const std::size_t field_descriptor = 5;
	const std::size_t generator_polynomial_index = 0;
	const std::size_t generator_polynomial_root_count = 16;

	/* Reed Solomon Code Parameters */
	const std::size_t code_length = RS_Length::code_31_15; //(2^5 - 1)
	const std::size_t data_length = RS_Length::data_31_15;
	const std::size_t fec_length = RS_Length::fec_31_15;

	/* 5-bit Symbol Parameter */
	const int mask = 0x0000001F;

	/* Instantiate Finite Field and Generator Polynomials */
	const schifra::galois::field field(field_descriptor,
		schifra::galois::primitive_polynomial_size02,
		schifra::galois::primitive_polynomial02);

	schifra::galois::field_polynomial generator_polynomial(field);

	if (
		!schifra::make_sequential_root_generator_polynomial(field,
			generator_polynomial_index,
			generator_polynomial_root_count,
			generator_polynomial)
		)
	{
		std::cout << "Error - Failed to create sequential root generator!" << std::endl;
		return 1;
	}

	/* Instantiate Encoder and Decoder (Codec) */
	typedef schifra::reed_solomon::encoder<code_length, fec_length> encoder_t;

	const encoder_t encoder(field, generator_polynomial);

	/* Instantiate RS Block For Codec */
	schifra::reed_solomon::block<code_length, fec_length> block;

	/* Pad message with nulls up until the code-word length */
	message.resize(code_length, 0x00);

	/* Transform message into Reed-Solomon encoded codeword */
	//??Symbol???????message?��????????????block???��??��??????????????????block.data??(????????????????FEC??)
	if (!encoder.encode(message, block))
	{
		std::cout << "Error - Critical encoding failure! "
			<< "Msg: " << block.error_as_string() << std::endl;
		return 1;
	}

	//?????str_fec
	string str_fec(RS_Length::fec_31_15, 0x00);
	block.fec_to_string(str_fec);

	if (codeLength == RS_Length::code_31_15 && dataLength == RS_Length::data_31_15) {
		//Assemble(Word)
		for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++) {
			bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
		}
	}

	else if (codeLength == RS_Length::code_16_7 && dataLength == RS_Length::data_16_7) {
		//Assemble(Header)??????fec???7Symbol?????��
		for (int i = RS_Length::data_16_7; i < RS_Length::code_16_7; i++) {
			bitset<8> temp = bitset<8>(str_fec[i]);
			symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
		}
	}
	else {
		return 1;
	}
	return 0;
}
