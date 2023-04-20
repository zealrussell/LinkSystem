#include "Link22Center.h"
#include "Utils/MsgUtil.h"

yazi::json::Json Link22Center::encoder_Link22(const std::string& msg, int n, int m, int p)
{
	return constructCenter.constructMessage(msg, n, m, p);
}

yazi::json::Json Link22Center::decoder_Link22(std::string& msg, int& n, int& m, int& p)
{
    std::string dataStr;
    msgUtil.getDataFromFile(MsgUtil::FILE_NAME, dataStr);
    int arrayNum = dataStr.length() / 8;
    uint8_t *data = msgUtil.StrToCharArray(dataStr, arrayNum);
    int symbolNum = arrayNum / 36;
	return constructCenter.crackMessage(data, symbolNum, msg, n, m, p);
}