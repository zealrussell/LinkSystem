#pragma once
#include "Link11ConstructCenter.h"

class Link11Center
{
	public:
		void encoder_Link11(int type, int n, string& msg);
		void decoder_Link11(uint8_t* msg, int& n);

	private:
		Link11ConstructCenter constructCenter;
		MsgUtil msgUtil;
};

