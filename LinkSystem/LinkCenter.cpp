#include "LinkCenter.h"

// 1. ���ı��ж�ȡ����
// 2. ����ת��
// 3. д�뵽�ı���

void LinkCenter::From22to16()
{
	// link22 ��Ϣ����
	std::string msg;
	int m, n, p;
	// 1. ��link22 �����н���� msg, m, n, p
	link22Center.decoder_Link22(msg, n, m, p);

	// 2. �ж� ��������ת��

	// case 1: ֱ�� 
	// ѡ�� F00.7-10 ��Կ������Ϣ��Ϊ
	if (m == 0 && n == 7 && p == 10) {

	}
	// case 2��ת��
	else if (m == 2 && n == 2) {

	}
	// case 3��ɾ��
	// F5-0 ���к����ĺ�����ٶ�
	else if (m == 4 && n == 1) {
		int m_16 = 3, n_16 = 2;
		std::string msg_16 = msg.substr(0, msg.find_first_of(":"));
		msg  = "sudu:10";
		// link16Center.encoder_Link16(m_16, n_16, msg_16);
	}

}

void LinkCenter::From16to22() {
	
	link16Center.encoder_Link16("hellozeal",1, 2);
	string msg;
	int n, m, p;
	link16Center.decoder_Link16(msg,n,m);
	cout << "11111111111111:  " << msg << endl << endl;
	//link22Center.encoder_Link22("hellozeal",0,1,2);
}
