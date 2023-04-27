#include <iostream>

#include "encode.h"

using namespace std;

yazi::json::Json Encode::BuildMessage(int type, int n, const string& msg)
{
	yazi::json::Json link11EncodeJson;
	link11EncodeJson["linktype"] = "link11";
	link11EncodeJson["type"] = "encode";

	//编码前导帧
	string preambleframe = BuildPreambleFrame();
	//������λ�ο�֡
	string phaseframe = BuildPhaseFrame();
	//������ʼ֡
	string startframe = BuildStartFrame();
	//��������֡
	string dataframe = BuildDataFrame(type, n, msg);
	//��������֡
	string endframe = BuildEndFrame();

	//结果
	string result = preambleframe + phaseframe + startframe + dataframe + endframe;
	
	link11EncodeJson["preambleframe"] = preambleframe;
	link11EncodeJson["phaseframe"] = phaseframe;
	link11EncodeJson["startframe"] = startframe;
	link11EncodeJson["dataframe"] = dataframe;
	link11EncodeJson["endframe"] = endframe;
	link11EncodeJson["result"] = result;

	cout <<"link11 after encode::" << msg << endl;
	msgUtil.saveToFile(Link11MsgUtil::FILE_NAME, (uint8_t *)msg.c_str(), 10);
	return link11EncodeJson;
}

//��������֡
string Encode::BuildDataFrame(int type, int n, const std::string& msg)
{
	string tmp;

	//����ϢתΪ01����
	Link11MsgUtil msgutil;
	string bitstr = msgutil.StrToBitStr(msg);

	//����4λ���ı��
	string num = to_string(decToBin(n));
	//cout << num << endl;
	for (size_t i = 0; i < 4 - num.length(); i++) {
		tmp += "0";
	}
	tmp += num;
	//cout << tmp << endl;
	
	//��Ϣ��24bit���֣�ÿֻ֡��24bit��Ϣ,ͬʱ��ɺ��������Ȼ��ϲ�
	//��һ֡ǰ4bit�ѱ����ı��ռ��
	int len = bitstr.length();
	int end = 20;//��ʼĩβ

	//�и�20bit�����ݺͱ��ı�ŵ�4bit��ɵ�һ֡
	string s;
	if (20 > len)//������һ���ָ������ָ�ȣ���0
	{
		s = bitstr.substr(0, len);//���һ���ַ�����ԭʼ����
		s.append(end - len, '0');//����numλ�ģ���0
		tmp = encode((tmp + s).c_str());
	}
	else {
		s = bitstr.substr(0, end);//��0��ʼ���ָ�20λ�ַ���
		end = end + DataLen;
		tmp = encode((tmp + s).c_str());

		//��24һ���и�֮������
		for (int start = 20; start < len;)
		{
			if (end > len)//������һ���ָ������ָ�ȣ���0
			{
				s = bitstr.substr(start, len - start);//���һ���ַ�����ԭʼ����
				s.append(end - len, '0');//����numλ�ģ���0
				tmp += encode(s.c_str());
				break;
			}
			s = bitstr.substr(start, DataLen);//��0��ʼ���ָ�24λ�ַ���
			start = end;
			end = end + DataLen;
			tmp += encode(s.c_str());
		}
	}

	return tmp;
}

//����ǰ��֡
string Encode::BuildPreambleFrame()
{
	string tmp;
	for (int i = 0; i < 5; i++) {
		string s(DataLen, '0');
		tmp += encode(s.c_str());
	}
	return tmp;
}

//������λ֡
string Encode::BuildPhaseFrame()
{
	string tmp;
	for (int i = 0; i < 1; i++) {
		string s(DataLen, '0');
		tmp += encode(s.c_str());
	}
	return tmp;
}

string Encode::BuildStartFrame()
{
	string Frame1 = "111100101000110000100000111111"; //0o7450604077
	string Frame2 = "101100110111011010010011100010";//0o5467322342
	string tmp = Frame1 + Frame2; 
	return tmp;
}

string Encode::BuildEndFrame()
{
	string Frame1 = "111111111111111111111111111111"; //0o7777777777
	string Frame2 = "111111111111111111111111111111";//0o7777777777
	string tmp = Frame1 + Frame2;
	return tmp;
}


int Encode::decToBin(int dec) {
	int result = 0, temp = dec, j = 1;
	while (temp) {
		result = result + j * (temp % 2);
		temp = temp / 2;
		j = j * 10;
	}
	return result;
}

Encode::Encode()
{
}

Encode::~Encode()
{
}


