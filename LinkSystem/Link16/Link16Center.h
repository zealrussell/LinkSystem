#include "tools.h"
#include "global.h"

#include "STDPMsg.h"
#include "interface.h"

class Link16Center
{
public:
	void encoder_Link16(const std::string& inputs, int n, int m);
	void decoder_Link16(std::string& msg, int &n, int &m);
};

