#include "Decode.h"

string Decode::CrackMessage(string tmp, int& n)
{
	
	//cout << tmp << endl;

	//解码前导帧
	string preambleframe = CrackPreambleFrame(tmp);
	//cout << preambleframe << endl
	//	<< preambleframe.length() << endl;

	//解码相位参考帧
	string phaseframe = CrackPhaseFrame(tmp);
	//cout << phaseframe << endl
	//	<< phaseframe.length() << endl;
	
	//解码数据帧
	string dataframe = CrackDataFrame(tmp,n);
	//cout << dataframe << endl
	//	<< dataframe.length() << endl;

	//将01序列转为消息
	Link11MsgUtil msgutil;
	string str = msgutil.BitStrToStr(dataframe);
	return str;
}

//解码数据帧
string Decode::CrackDataFrame(const std::string& msg, int& n)
{
	//计算数据帧长度
	int len = msg.length() - 6 * FrameLen - 4 * 30;
	
	//分割出数据帧
	string dataframe = msg.substr(6 * FrameLen + 2 * 30, len);
	
	//消息按帧划分,同时完成汉明码解码然后合并
	int end = FrameLen;//分割定长大小

	string tmp;

	for (int start = 0; start < len;)
	{
		string s;
		s = dataframe.substr(start, FrameLen);
		start = end;
		end = end + FrameLen;
		tmp += decode(s.c_str());
	}
	//前4bit为报文编号
	string datanum = tmp.substr(0, 4);
	//其后均为数据
	string data = tmp.substr(4, tmp.length()-8);//截取的长度应为char类型的位长8的整数

	//声明接收报文的编号
	n = stoi(datanum, 0, 2);

	return data;
}

//解码前导帧
string Decode::CrackPreambleFrame(const std::string& msg)
{
	string preambleframe = msg.substr(0, 5 * FrameLen);

	//消息按帧划分,同时完成汉明码解码然后合并
	int end = FrameLen;//分割定长大小
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

//解码相位参考帧
string Decode::CrackPhaseFrame(const std::string& msg)
{
	string phaseframe = msg.substr(5 * FrameLen, 1 * FrameLen);

	//消息按帧划分,同时完成汉明码解码然后合并
	int end = FrameLen;//分割定长大小
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

