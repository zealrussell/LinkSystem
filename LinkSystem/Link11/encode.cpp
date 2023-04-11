#include <iostream>

#include "encode.h"

using namespace std;

uint8_t* Encode::BuildMessage(int type, int n, const string& msg)
{

	//构建前导帧
	string preambleframe = BuildPreambleFrame();
	//构建相位参考帧
	string phaseframe = BuildPhaseFrame();
	//构建起始帧
	string startframe = BuildStartFrame();
	//构建数据帧
	string dataframe = BuildDataFrame(type, n, msg);
	//构建结束帧
	string endframe = BuildEndFrame();

	//组合
	string result = preambleframe + phaseframe + startframe + dataframe + endframe;
	//cout << msg << endl;
	//cout << (uint8_t*)msg.c_str() << endl;
	
	return (uint8_t*)result.c_str();
}

//构建数据帧
string Encode::BuildDataFrame(int type, int n, const std::string& msg)
{
	string tmp;

	//将消息转为01序列
	Link11MsgUtil msgutil;
	string bitstr = msgutil.StrToBitStr(msg);

	//构造4位报文编号
	string num = to_string(decToBin(n));
	//cout << num << endl;
	for (int i = 0; i < 4 - num.length(); i++) {
		tmp += "0";
	}
	tmp += num;
	//cout << tmp << endl;
	
	//消息按24bit划分，每帧只有24bit消息,同时完成汉明码加密然后合并
	//第一帧前4bit已被报文编号占据
	int len = bitstr.length();
	int end = 20;//初始末尾

	//切割20bit的数据和报文编号的4bit组成第一帧
	string s;
	if (20 > len)//针对最后一个分割串，不足分割长度，补0
	{
		s = bitstr.substr(0, len);//最后一个字符串的原始部分
		s.append(end - len, '0');//不足num位的，补0
		tmp = encode((tmp + s).c_str());
	}
	else {
		s = bitstr.substr(0, end);//从0开始，分割20位字符串
		end = end + DataLen;
		tmp = encode((tmp + s).c_str());

		//按24一组切割之后数据
		for (int start = 20; start < len;)
		{
			if (end > len)//针对最后一个分割串，不足分割长度，补0
			{
				s = bitstr.substr(start, len - start);//最后一个字符串的原始部分
				s.append(end - len, '0');//不足num位的，补0
				tmp += encode(s.c_str());
				break;
			}
			s = bitstr.substr(start, DataLen);//从0开始，分割24位字符串
			start = end;
			end = end + DataLen;
			tmp += encode(s.c_str());
		}
	}

	return tmp;
}

//构建前导帧
string Encode::BuildPreambleFrame()
{
	string tmp;
	for (int i = 0; i < 5; i++) {
		string s(DataLen, '0');
		tmp += encode(s.c_str());
	}
	return tmp;
}

//构建相位帧
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


