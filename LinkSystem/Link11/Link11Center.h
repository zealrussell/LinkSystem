
#pragma once

#include "Link11MsgUtil.h"
#include "encode.h"
#include "Decode.h"

class Link11Center
{
	public:
		void encoder_Link11(int type, int n, const std::string& msg);
		void decoder_Link11(int& n);

	private:
		Encode encode;
		Decode decode;

		Link11MsgUtil msgUtil;
};

