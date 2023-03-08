#pragma once
#include "tools.h"
#include "global.h"

#include "decodeTools.h"
#include "STDPMsg.h"

class Link16Center
{
public:
	int encoder_Link16(int m, int n, string& inputs);
	int decoder_Link16();
};

