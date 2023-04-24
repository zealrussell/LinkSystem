#pragma once
#include "System/ConstructCenter.h"

class Link22Center
{
public:
	// 加密器
	void encoder_Link22(const std::string &msg, int n = 0, int m = 0, int p = 0);
    // 解密器
	void decoder_Link22(std::string &msg, int &n, int &m, int &p);

private:
    ConstructCenter constructCenter;
    MsgUtil msgUtil;
};

