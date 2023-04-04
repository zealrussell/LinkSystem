#ifndef LINK11CONSTRUCTCENTER_H
#define LINK11CONSTRUCTCENTER_H

#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <stdint.h>

#include "hamming.h"
#include "Link11MsgUtil.h"
#include "encode.h"
#include "Decode.h"

using namespace std;

class Link11ConstructCenter
{
public:
	void constructMessage(int type, int n, string& msg);
	void crackMessage(uint8_t* msg, int& n);
private:
	Encode encode;
	Decode decode;
};

#endif