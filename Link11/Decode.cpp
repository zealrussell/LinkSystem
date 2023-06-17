#include "Decode.h"

yazi::json::Json Decode::CrackMessage(const std::string &tmp, string &msg, int& type, int& n)
{
	yazi::json::Json link11DecodeJson;
	link11DecodeJson["linktype"] = "link11";
	link11DecodeJson["type"] = "decode";

	//����ǰ��֡
	string preambleframe = CrackPreambleFrame(tmp);
	//cout << preambleframe << endl
	//	<< preambleframe.length() << endl;

	//������λ�ο�֡
	string phaseframe = CrackPhaseFrame(tmp);
	//cout << phaseframe << endl
	//	<< phaseframe.length() << endl;
	
	//��������֡
	string dataframe = CrackDataFrame(tmp, type, n);
	//cout << dataframe << endl
	//	<< dataframe.length() << endl;

	//��01����תΪ��Ϣ
	Link11MsgUtil msgutil;
	// ���
	msg = msgutil.BitStrToStr(dataframe);

	link11DecodeJson["depreambleframe"] = preambleframe;
	link11DecodeJson["dephaseframe"] = phaseframe;
	link11DecodeJson["dedataframe"] = dataframe;
	link11DecodeJson["originstring"] = "msg";

	return link11DecodeJson;
}

//��������֡
string Decode::CrackDataFrame(const std::string& message, int& type, int& n)
{
	//��������֡����
	int len = message.length() - 6 * FrameLen - 4 * 30;
	
	//�ָ������֡
	string dataframe = message.substr(6 * FrameLen + 2 * 30, len);
	
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
	//����λΪ��������
	string typenum = tmp.substr(4, 1);
	//����Ϊ����
	string data = tmp.substr(5, tmp.length()-8);//��ȡ�ĳ���ӦΪchar���͵�λ��8������

	//�������ձ��ĵı��
	n = stoi(datanum, 0, 2);
	//�������ܱ��ĵ�����
	type = stoi(typenum, 0, 2);

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