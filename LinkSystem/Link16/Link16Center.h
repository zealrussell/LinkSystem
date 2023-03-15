#include "tools.h"
#include "global.h"

#include "decodeTools.h"
#include "STDPMsg.h"
#include "interface.h"

class Link16Center
{
public:
	void encoder_Link16(const string& inputs, int n, int m);
	void decoder_Link16(string& msg, int &n, int &m);
};

