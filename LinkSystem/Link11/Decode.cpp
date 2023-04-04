#include "Decode.h"

string Decode::CrackMessage(uint8_t* msg, int& n)
{
	//ת��Ϊstring
	string tmp = (char*)msg;
	//cout << tmp << endl;

	//����ǰ��֡
	string preambleframe = CrackPreambleFrame(tmp);
	//cout << preambleframe << endl
	//	<< preambleframe.length() << endl;

	//������λ�ο�֡
	string phaseframe = CrackPhaseFrame(tmp);
	//cout << phaseframe << endl
	//	<< phaseframe.length() << endl;
	
	//��������֡
	string dataframe = CrackDataFrame(tmp,n);
	//cout << dataframe << endl
	//	<< dataframe.length() << endl;

	//��01����תΪ��Ϣ
	Link11MsgUtil msgutil;
	string str = msgutil.BitStrToStr(dataframe);
	return str;
}

//��������֡
string Decode::CrackDataFrame(const std::string& msg, int& n)
{
	//��������֡����
	int len = msg.length() - 6 * FrameLen - 4 * 30;
	
	//�ָ������֡
	string dataframe = msg.substr(6 * FrameLen + 2 * 30, len);
	
	//��Ϣ��֡����,ͬʱ��ɺ��������Ȼ��ϲ�
	int end = FrameLen;//�ָ����С

	string tmp;

	for (int start = 0; start < len;)
	{
		string s;
		s = dataframe.substr(start, FrameLen);
		start = end;
		end = end + FrameLen;
		tmp += decode(s.c_str());
	}
	//ǰ4bitΪ���ı��
	string datanum = tmp.substr(0, 4);
	//����Ϊ����
	string data = tmp.substr(4, tmp.length()-8);//��ȡ�ĳ���ӦΪchar���͵�λ��8������

	//�������ձ��ĵı��
	n = stoi(datanum, 0, 2);

	return data;
}

//����ǰ��֡
string Decode::CrackPreambleFrame(const std::string& msg)
{
	string preambleframe = msg.substr(0, 5 * FrameLen);

	//��Ϣ��֡����,ͬʱ��ɺ��������Ȼ��ϲ�
	int end = FrameLen;//�ָ����С
	int len = preambleframe.length();

	string tmp;

	for (int start = 0; start < len;)
	{
		string s;
		s = preambleframe.substr(start, FrameLen);
		start = end;
		end = end + FrameLen;
		tmp += decode(s.c_str());
	}

	return tmp;
}

//������λ�ο�֡
string Decode::CrackPhaseFrame(const std::string& msg)
{
	string phaseframe = msg.substr(5 * FrameLen, 1 * FrameLen);

	//��Ϣ��֡����,ͬʱ��ɺ��������Ȼ��ϲ�
	int end = FrameLen;//�ָ����С
	int len = phaseframe.length();

	string tmp;

	for (int start = 0; start < len;)
	{
		string s;
		s = phaseframe.substr(start, FrameLen);
		start = end;
		end = end + FrameLen;
		tmp += decode(s.c_str());
	}
	return tmp;
}

