#include "interface.h"

namespace interface{
	//m,n�Ƿ��͵�ս����Ϣ����,inputs����Ϣ��Ҫ����
	int32_t encoder_Link16(int32_t n, int32_t m, const string& inputs) {
		//����׼��
		string type = to_string(n) + " " + to_string(m);
		if (g_JType.count(type) == 0) {
			std::cout << "The message type sent does not exist" << std::endl;
			return -1;
		}
		std::cout << "The message type sent is:" << g_JType[type] << std::endl;

		srand((unsigned)time(NULL));
		string bit_data = Tools::StrToBitStr(inputs);
		std::cout << "raw_data = " << inputs << std::endl;
		std::cout << "bit_data = " << bit_data << std::endl;

		//�ж��ļ��Ƿ���ڣ���������ɾ��
		if (!Tools::deleteFile()) {
			return -2;
		}

		bitset<15> STN = bitset<15>(Tools::generateBIN(15));
		HeaderWord headerWord = HeaderWord(STN);
		headerWord.show();

		size_t bit_length = bit_data.length();
		//��װ�ͷ��͹��̣�ʹ�ñ�׼��ʽ(STD)���з�װ---���ճ�ʼ��->��չ��->�����ֵ�˳������
		int flag = 3;
		InitialWord iword;
		ExtendWord eword;
		ContinueWord cword;
		while (1) {
			bit_length = bit_data.length();
			if (bit_length <= 0) {
				//ִ��210bit��żУ�鼰�������裬���˳�
				Tools::handlerSTDP(headerWord, iword, eword, cword);
				iword.clear();
				eword.clear();
				cword.clear();
				break;
			}
			if (flag == 0 && bit_length > 0) {
				//ִ��210bit��żУ�鼰�������裬��������һ�ֵĴ��
				Tools::handlerSTDP(headerWord, iword, eword, cword);
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
		return 0;
	}

	int32_t decoder_Link16(string& raw_data, int32_t& n, int32_t& m) {
		//���ļ��ж�������
		string RT_bit_data = Tools::read_msg();
		string bit_msg;

		//TODO:��STDPMsg���װ����������
		STDPMsg stdp_msg;

		while (RT_bit_data.length() != 0) {
			//��ȡһ����Ϣ
			std::cout << "The current message length is:" << RT_bit_data.length() << std::endl;
			string str_group = Tools::getGroup(RT_bit_data);
			stdp_msg.setRawMsg(str_group);

			//�⽻֯
			string str_weave = Tools::decode_weave(str_group);

			//��RS���롢AES���ܡ�BIPУ��
			string bit_data = Tools::decode_RS_AES_BIP_handler(str_weave);
			if (bit_data.empty()) {
				std::cout << "[decode_RS_AES_BIP_handler] Internal function error" << std::endl;
				return -1;
			}

			//��װHeaderWord
			string headerword_str = bit_data.substr(0, 35);
			stdp_msg.setHeaderWord(headerword_str);
			//ȥHeaderWord
			bit_data.erase(0, 35);

			//��װInitialWord
			string iword_str = bit_data.substr(0, 75);
			stdp_msg.setInitialWord(iword_str);
			//��InitialWordȡn, m
			bitset<5> signal = stdp_msg.getInitialWord()->getSignal();
			bitset<3> subSignal = stdp_msg.getInitialWord()->getSubSignal();
			n = static_cast<int32_t>(signal.to_ulong());
			m = static_cast<int32_t>(subSignal.to_ulong());
			//��InitialWord��ȡdata
			bit_msg += stdp_msg.getInitialWord()->getData();
			//ȥInitialWord
			bit_data.erase(0, 75);

			//��װExtendWord
			string eword_str = bit_data.substr(0, 75);
			stdp_msg.setExtendWord(eword_str);
			//��ExtendWord��ȡdata
			bit_msg += stdp_msg.getExtendWord()->getData();
			//ȥExtendWord
			bit_data.erase(0, 75);

			//��װContinueWord
			string cword_str = bit_data.substr(0, 75);
			stdp_msg.setContinueWord(cword_str);
			//��ContinueWord��ȡdata
			bit_msg += stdp_msg.getContinueWord()->getData();
		}
		stdp_msg.setBitMsg(bit_msg);
		raw_data = bit_msg;
		return 0;
	}
}