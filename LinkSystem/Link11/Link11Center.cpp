#include "Link11Center.h"

void Link11Center::encoder_Link11(int type, int n, string& msg)
{
	constructCenter.constructMessage(type, n, msg);
}

void Link11Center::decoder_Link11(uint8_t* msg, int& n)
{
	constructCenter.crackMessage(msg, n);
}
