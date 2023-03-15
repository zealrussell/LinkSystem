#include "Link16Center.h"

void Link16Center::encoder_Link16(const string& inputs, int n, int m)
{
	encoder(n, m, inputs);
}

void Link16Center::decoder_Link16(string& msg, int& n, int& m)
{
	decoder(msg, n, m);
}
