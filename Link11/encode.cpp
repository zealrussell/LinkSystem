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
	//编码相位参考帧
	string phaseframe = BuildPhaseFrame();
	//编码起始帧
	string startframe = BuildStartFrame();
	//编码数据帧
	string dataframe = BuildDataFrame(type, n, msg);
	//编码结束帧
	string endframe = BuildEndFrame();

	//结果
	string result = preambleframe + phaseframe + startframe + dataframe + endframe;
	
	link11EncodeJson["preambleframe"] = preambleframe;
	link11EncodeJson["phaseframe"] = phaseframe;
	link11EncodeJson["startframe"] = startframe;
	link11EncodeJson["dataframe"] = dataframe;
	link11EncodeJson["endframe"] = endframe;
	link11EncodeJson["result"] = result;

	cout <<"link11 after encode::" << result << endl;
	msgUtil.saveToFile(Link11MsgUtil::FILE_NAME, result);
	return link11EncodeJson;
}

//构建数据帧
string Encode::BuildDataFrame(int type, int n, const std::string& msg)
{
	string tmp;

	//将消息转为01序列
	Link11MsgUtil msgutil;
	string bitstr = msgutil.StrToBitStr(msg);

	//构建4位报文编号
	string num = to_string(decToBin(n));
	//cout << num << endl;
	for (size_t i = 0; i < 4 - num.length(); i++) {
		tmp += "0";
	}
	tmp += num;
	//cout << tmp << endl;

	tmp += to_string(type);
	
	//消息按24bit划分，每帧只有24bit消息,同时完成汉明码加密然后合并
	//第一帧前4bit已被报文编号占据
	int len = bitstr.length();
	int end = 19;	//初始末尾

	//切割19bit的数据和报文编号的4bit组成第一帧
	string s;
	if (19 > len) //针对最后一个分割串，不足分割长度，补0
	{
		s = bitstr.substr(0, len);	//最后一个字符串的原始部分
		s.append(end - len, '0');	//不足num位的，补0
		tmp = encode((tmp + s).c_str());
	}
	else {
		s = bitstr.substr(0, end);	//从0开始，分割19位字符串
		end = end + DataLen;
		tmp = encode((tmp + s).c_str());

		//按24一组切割之后数据
		for (int start = 19; start < len;)
		{
			if (end > len)//针对最后一个分割串，不足分割长度，补0
			{
				s = bitstr.substr(start, len - start);	//最后一个字符串的原始部分
				s.append(end - len, '0');	//不足num位补0
				break;
			}
			s = bitstr.substr(start, DataLen);	//从0开始，分割24位字符串
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


