#include "tools.h"
#include "global.h"

#include "STDPMsg.h"
#include "interface.h"
#include <json/Json.h>

class Link16Center
{
public:
	yazi::json::Json encoder_Link16(const string &inputs, int32_t n, int32_t m);
	yazi::json::Json decoder_Link16(string &raw_data, int32_t &n, int32_t &m);
};