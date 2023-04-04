#include "Link11ConstructCenter.h"

void Link11ConstructCenter::constructMessage(int type, int n, string& msg)
{
	uint8_t* res = encode.BuildMessage(type, n, msg);
	cout << res << endl;
}

void Link11ConstructCenter::crackMessage(uint8_t* msg, int& n)
{
	string recvmsg = decode.CrackMessage(msg, n);
	printf("接收到编号M.%d的报文，解码后消息为：", n);
	cout << recvmsg << endl;
}
