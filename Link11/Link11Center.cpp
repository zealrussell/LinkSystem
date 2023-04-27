#include "Link11Center.h"

Json Link11Center::encoder_Link11(const std::string& msg, int type, int n)
{
	Json encodeJson = encode.BuildMessage(type, n, msg);
	return encodeJson;
}

Json Link11Center::decoder_Link11(std::string &msg, int& n)
{
	std::string dataStr;
	msgUtil.getDataFromFile(Link11MsgUtil::FILE_NAME, dataStr);
	Json decodeJson = decode.CrackMessage(dataStr, msg, n);
	printf("接收到编号M.%d的报文, 解码后消息为: %s", n, msg);
	return decodeJson;
}
