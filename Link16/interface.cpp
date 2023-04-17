#include "interface.h"

namespace interface
{
	// n. m: the type of tactical message sent.
	// inputs: the main content of the message.
	string encoder_Link16(int32_t n, int32_t m, const string &inputs)
	{
		// Data preparation.
		string type = to_string(n) + " " + to_string(m);
		if (g_JType.count(type) == 0)
		{
			std::cout << "The message type sent does not exist." << std::endl;
			return "-1";
		}
		std::cout << "The message type sent is:" << g_JType[type] << std::endl;

		srand((unsigned)time(NULL));
		string bit_data = Tools::StrToBitStr(inputs);
		std::cout << "raw_data = " << inputs << std::endl;
		std::cout << "bit_data = " << bit_data << std::endl;

		// Determine if the file exists and delete it if it exists.
		if (!Tools::deleteFile())
		{
			return "-2";
		}

		bitset<15> STN = bitset<15>(Tools::generateBIN(15));
		HeaderWord headerWord = HeaderWord(STN);
		headerWord.show();

		size_t bit_length = bit_data.length();
		// Encapsulation and sending process: Encapsulation using standard format (STD):
		//  arranged in the order of initial word ->extended word ->continued word.
		int flag = 3;
		InitialWord iword;
		ExtendWord eword;
		ContinueWord cword;
		string encode_str;
		while (1)
		{
			bit_length = bit_data.length();
			if (bit_length <= 0)
			{
				// ִPerform 210bit parity and subsequent steps, and finally exit.
				encode_str += Tools::handlerSTDP(headerWord, iword, eword, cword);
				iword.clear();
				eword.clear();
				cword.clear();
				break;
			}
			if (flag == 0 && bit_length > 0)
			{
				// ִPerform 210bit parity check and subsequent steps, and proceed with a new round of packaging.
				encode_str += Tools::handlerSTDP(headerWord, iword, eword, cword);
				iword.clear();
				eword.clear();
				cword.clear();
				flag = 3;
			}
			switch (flag)
			{
			case 3:
			{
				iword.clear();
				iword.handler_word(bit_data, type);
				iword.show();
				break;
			}
			case 2:
			{
				eword.clear();
				eword.handler_word(bit_data);
				eword.show();
				break;
			}
			case 1:
			{
				cword.clear();
				cword.handler_word(bit_data);
				cword.show();
				break;
			}
			default:
				break;
			}
			flag--;
		}
		return encode_str;
	}

	int32_t decoder_Link16(string &raw_data, int32_t &n, int32_t &m)
	{
		// Reading data from a file.
		string RT_bit_data = Tools::read_msg();
		string bit_msg;
		STDPMsg stdp_msg;

		while (RT_bit_data.length() != 0)
		{
			// Intercept a set of messages.
			std::cout << "The current message length is:" << RT_bit_data.length() << std::endl;
			string str_group = Tools::getGroup(RT_bit_data);
			stdp_msg.setRawMsg(str_group);

			// De-interleaving.
			string str_weave = Tools::decode_weave(str_group);

			// Decoding RS encoding, AES decryption, BIP verification.
			string bit_data = Tools::decode_RS_AES_BIP_handler(str_weave);
			if (bit_data.empty())
			{
				std::cout << "[decode_RS_AES_BIP_handler] Internal function error" << std::endl;
				return -1;
			}

			// Encapsulate HeaderWord.
			string headerword_str = bit_data.substr(0, 35);
			stdp_msg.setHeaderWord(headerword_str);
			// Remove HeaderWord.
			bit_data.erase(0, 35);

			// Encapsulate InitialWord.
			string iword_str = bit_data.substr(0, 75);
			stdp_msg.setInitialWord(iword_str);
			// Take n, m from InitialWord.
			bitset<5> signal = stdp_msg.getInitialWord()->getSignal();
			bitset<3> subSignal = stdp_msg.getInitialWord()->getSubSignal();
			n = static_cast<int32_t>(signal.to_ulong());
			m = static_cast<int32_t>(subSignal.to_ulong());
			// Retrieve data from InitialWord.
			bit_msg += stdp_msg.getInitialWord()->getData();
			// Remove InitialWord.
			bit_data.erase(0, 75);

			// Encapsulate ExtendWord.
			string eword_str = bit_data.substr(0, 75);
			stdp_msg.setExtendWord(eword_str);
			// Retrieve data from ExtendWord.
			bit_msg += stdp_msg.getExtendWord()->getData();
			// Remove ExtendWord.
			bit_data.erase(0, 75);

			// Encapsulate ContinueWord.
			string cword_str = bit_data.substr(0, 75);
			stdp_msg.setContinueWord(cword_str);
			// Retrieve data from ontinueWord.
			bit_msg += stdp_msg.getContinueWord()->getData();
		}
		stdp_msg.setBitMsg(bit_msg);
		raw_data = bit_msg;
		return 0;
	}
}