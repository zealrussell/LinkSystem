
#pragma once

#include "Link11MsgUtil.h"
#include "encode.h"
#include "Decode.h"

#include <json/Json.h>
using namespace yazi::json;

class Link11Center
{
	public:
		Json encoder_Link11(const std::string& msg, int type, int n);
		Json decoder_Link11(std::string &msg, int& n);

	private:
		Encode encode;
		Decode decode;

		Link11MsgUtil msgUtil;
};

