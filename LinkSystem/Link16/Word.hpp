#pragma once
#include "dataType.h"
#include <iostream>
#include <string.h>

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

template <RS_Length codeLength, RS_Length dataLength>
class Word {
public:
	symbol* m_S_word;      //symbol转换后的Word
	symbol* m_RS_word;     //RS编码后的Word

	Word() {
		m_S_word = new symbol[dataLength]();
		m_RS_word = new symbol[codeLength]();
	}

	virtual ~Word()
	{
		delete[] m_S_word;
		m_S_word = nullptr;
		delete[] m_RS_word;
		m_RS_word = nullptr;
	}

	int RS(const size_t rsCodeLength, const size_t rsDataLength, string& message, symbol* symbol_msg) {
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
		//??Symbol???????message???????????????block???????????????????????????block.data??(????????????????FEC??)
		if (!encoder.encode(message, block))
		{
			std::cout << "Error - Critical encoding failure! "
				<< "Msg: " << block.error_as_string() << std::endl;
			return 1;
		}

		//?????str_fec
		string str_fec(RS_Length::fec_31_15, 0x00);
		block.fec_to_string(str_fec);

		if (rsCodeLength == RS_Length::code_31_15 && rsDataLength == RS_Length::data_31_15) {
			//Assemble(Word)
			for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++) {
				bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
				symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
			}
		}

		else if (rsCodeLength == RS_Length::code_16_7 && rsDataLength == RS_Length::data_16_7) {
			//Assemble(Header)??????fec???7Symbol???????
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

	
	//用RS纠错编码处理消息字，使用schifra库
	void RS_handler() {
		symbol* symbol_word = this->getS_word();

		////print
		//std::cout << "编码前symbol_word = " << std::endl;
		//for (int i = 0; i < dataLength; i++) {
		//	std::cout << symbol_word[i].to_string();
		//}
		//std::cout << std::endl;

		string message(dataLength, 0x00);
		for (int i = 0; i < dataLength; i++) {
			message[i] = static_cast<char>(symbol_word[i].to_ulong());
		}

		////print
		//std::cout << "RS编码前转换后的symbol(二进制表示): " << std::endl;
		//for (int i = 0; i < dataLength; i++) {
		//	for (int j = 7; j >= 0; j--) {
		//		std::cout << ((message[i] >> j) & 1);
		//	}
		//}
		//std::cout << std::endl;

		symbol* symbol_RS_word = this->getRS_word();
		memset(symbol_RS_word, 0, sizeof(symbol) * codeLength);
		memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * dataLength);

		if (!RS(codeLength, dataLength, message, symbol_RS_word)) {
			std::cout << "RS encoding successful" << std::endl;
		}
		else {
			std::cout << "RS encoding failed" << std::endl;
		}

		////print
		//std::cout << "编码后symbol_RS_word = " << std::endl;
		//for (int i = 0; i < codeLength; i++) {
		//	std::cout << symbol_RS_word[i].to_string();
		//}
		//std::cout << std::endl;
	}

	virtual void clear() {
		memset(m_S_word, 0, sizeof(symbol) * dataLength);
		memset(m_RS_word, 0, sizeof(symbol) * codeLength);
	}

	string toString_STDP() {
		string res;
		for (int i = 0; i < codeLength; i++) {
			res += m_RS_word[i].to_string();
		}
		return res;
	}

	symbol* getS_word() {
		return m_S_word;
	}

	symbol* getRS_word() {
		return m_RS_word;
	}
	virtual void rewrite(string& bit_str) = 0;
	virtual void to_symbol() = 0;
	virtual string toString() = 0;
};
