#include "Link11Center.h"

void Link11Center::encoder_Link11(int type, int n, const std::string& msg)
{
	uint8_t* res = encode.BuildMessage(type, n, msg);
	msgUtil.saveToFile(Link11MsgUtil::FILE_NAME, res, 10);
	cout << res << endl;
}

void Link11Center::decoder_Link11(std::string &msg, int& n)
{
	std::string dataStr;
	msgUtil.getDataFromFile(Link11MsgUtil::FILE_NAME, dataStr);
	msg = decode.CrackMessage(msg, n);
	printf("���յ����M.%d�ı��ģ��������ϢΪ��", n);
	cout << msg << endl;
}
