#include "Link16Center.h"

void Link16Center::encoder_Link16(const string& inputs, int n, int m)
{
	interface::encoder_Link16(n, m, inputs);
}

void Link16Center::decoder_Link16(string& msg, int& n, int& m)
{
	interface::decoder_Link16(msg, n, m);
}
