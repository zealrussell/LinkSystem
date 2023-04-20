#pragma once
#include "System/ConstructCenter.h"
#include <json/Json.h>

class Link22Center
{
public:
	// 加密器
	yazi::json::Json encoder_Link22(const std::string &msg, int n = 0, int m = 0, int p = 0);
    // 解密器
	yazi::json::Json decoder_Link22(std::string &msg, int &n, int &m, int &p);

private:
    ConstructCenter constructCenter;
    MsgUtil msgUtil;
};

