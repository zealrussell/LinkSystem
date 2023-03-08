#pragma once
#include "System/ConstructCenter.h"

class Link22Center
{
public:
	void decode_Link22(std::string msg,int m = 0, int n = 0, int p = 0);
	void encode_Link16(std::string data);
};

