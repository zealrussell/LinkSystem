#include "Link22Center.h"
#include "Utils/MsgUtil.h"

void Link22Center::encoder_Link22(const std::string& msg, int n, int m, int p)
{
	constructCenter.constructMessage(msg, n, m, p);
}

void Link22Center::decoder_Link22(std::string& msg, int& n, int& m, int& p)
{
    std::string dataStr;
    msgUtil.getDataFromFile(MsgUtil::FILE_NAME, dataStr);
    int arrayNum = dataStr.length() / 8;
    uint8_t *data = msgUtil.StrToCharArray(dataStr, arrayNum);
    int symbolNum = arrayNum / 36;
	constructCenter.crackMessage(data, symbolNum, msg, n, m, p);
}