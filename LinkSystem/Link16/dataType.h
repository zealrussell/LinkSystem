#pragma once
#include <bitset>

using namespace std;

typedef bitset<5>	symbol;		//5bit = 1Symbol, ע��sizeof(symbol) = 4

constexpr auto FILENAME = R"(./data.txt)";

const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

enum RS_Length
{
	code_16_7 = 16,
	data_16_7 = 7,
	fec_16_7 = 9,
	code_31_15 = 31,
	data_31_15 = 15,
	fec_31_15 = 16,
};
