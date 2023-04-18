#include "LinkCenter.h"

// 1. ���ı��ж�ȡ����
// 2. ����ת��

void LinkCenter::From22to16()
{
	// link22 ��Ϣ����
	std::string msg_22, msg_16;
	int m_22, n_22, p_22;
	int n_16 = 0, m_16 = 0;
	// 1. ��link22 �����н���� msg, m, n, p
	link22Center.decoder_Link22(msg_22, n_22, m_22, p_22);

	// 2. �ж� ��������ת��

	// case 1: ֱ��
	// ѡ�� F00.7-10 ��Կ������Ϣ��Ϊ
	if (m_22 == 0 && n_22 == 7 && p_22 == 10)
	{
		n_16 = 31;
		m_16 = 11;
		msg_16 = msg_22;
	}
	// case 2��ת��
	else if (m_22 == 2 && n_22 == 2)
	{
		n_16 = 3;
		m_16 = 2;
		msg_16 = msg_22.substr(0, msg_22.find_first_of(":"));
	}
	// case 3��ɾ��
	// F5-0 ���к����ĺ�����ٶ�
	else if (m_22 == 4 && n_22 == 1)
	{
		n_16 = 3;
		m_16 = 2;
		msg_16 = msg_22.substr(0, msg_22.find_first_of(":"));
	}
	link16Center.encoder_Link16(msg_16, n_16, m_16);
}

void LinkCenter::From16to22(const string &msg_encrypted_16, string &msg_encrypted_22)
{

	string msg_16, msg_22;
	int n_16, m_16;
	link16Center.decoder_Link16(msg_16, n_16, m_16);
	std::cout << "-------------link16 decode finish ------------" << std::endl;
	int n_22 = 0, m_22 = 0, p_22 = 0;
	// 直译
	if (n_16 == 31 && m_16 == 11)
	{
		m_22 = 0;
		n_22 = 7;
		p_22 = 10;
		msg_22 = msg_16;
	}
	// 转译
	else if (n_16 == 00 && m_16 == 00)
	{
		m_22 = 1;
		n_22 = 4;
		p_22 = -1;
	}
	// 增译
	else if (n_16 == 3 && m_16 == 2)
	{
		m_22 = 1;
		n_22 = 4;
		p_22 = -1;
		msg_22 = msg_16 + ";speed=0";
	}
	// printf("\n\n\n\n\n\n\n\n");
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
	if (n_16 == 1 && m_16 == 1)
	{
	}
}

void LinkCenter::create_Link11()
{
	// link11Center.en coder_Link11();
}

void LinkCenter::create_Link16(const std::string &msg, int n, int m)
{
	link16Center.encoder_Link16(msg, n, m);
}

void LinkCenter::create_Link22(const std::string &msg, int n, int m, int p)
{
	link22Center.encoder_Link22(msg, n, m, p);
}
