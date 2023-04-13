#include "LinkCenter.h"

// 1. 从文本中读取数据
// 2. 进行转换

void LinkCenter::From22to16()
{
	// link22 消息数据
	std::string msg_22, msg_16;
	int m_22, n_22, p_22;
	int n_16 = 0, m_16 = 0;
	// 1. 从link22 数据中解码出 msg, m, n, p
	link22Center.decoder_Link22(msg_22, n_22, m_22, p_22);

	// 2. 判断 进行那种转换

	// case 1: 直译 
	// 选择 F00.7-10 密钥滚动消息作为
	if (m_22 == 0 && n_22 == 7 && p_22 == 10) {
		n_16 = 31;
		m_16 = 11;
		msg_16 = msg_22;
	}
	// case 2：转译
	else if (m_22 == 2 && n_22 == 2) {
		n_16 = 3;
		m_16 = 2;
		msg_16 = msg_22.substr(0, msg_22.find_first_of(":"));
	}
	// case 3：删译
	// F5-0 空中航迹的航向和速度
	else if (m_22 == 4 && n_22 == 1) {
		n_16 = 3;
		m_16 = 2;
		msg_16 = msg_22.substr(0, msg_22.find_first_of(":"));
	}
	link16Center.encoder_Link16(msg_16, n_16, m_16);
}

void LinkCenter::From16to22() {
	
	string msg_16, msg_22;
	int n_16, m_16;
	link16Center.decoder_Link16(msg_16, n_16, m_16);
	int n_22 = 0, m_22 = 0, p_22 = 0;
	// 直译
	if (n_16 == 31 && m_16 == 11) {
		m_22 = 0;
		n_22 = 7;
		p_22 = 10;
		msg_22 = msg_16;
	}
	// 转译
	else if (n_16 == 00 && m_16 == 00) {
		m_22 = 1;
		n_22 = 4;
		p_22 = -1;
	}
	// 增 译
	else if (n_16 == 3 && m_16 == 2) {
		m_22 = 1;
		n_22 = 4;
		p_22 = -1;
		msg_22 = msg_16 + ";speed=0";
	}
	printf("\n\n\n\n\n\n\n\n");
	link22Center.encoder_Link22(msg_22, n_22, m_22, p_22);
}

void LinkCenter::From11to16()
{
	string msg_11;
	int n_11;

	link11Center.decoder_Link11(msg_11, n_11);

}

void LinkCenter::From16to11()
{
	string msg_16, msg_22;
	int n_16, m_16;
	link16Center.decoder_Link16(msg_16, n_16, m_16);
	if (n_16 == 1 && m_16 == 1) {

	}

}

void LinkCenter::create_Link11()
{
	// link11Center.en coder_Link11();
}


void LinkCenter::create_Link16(const std::string& msg, int n, int m)
{
	link16Center.encoder_Link16(msg, n, m);
}

void LinkCenter::create_Link22(const std::string& msg, int n, int m, int p)
{
	link22Center.encoder_Link22(msg, n, m, 0);
}
