#pragma once
#include <bitset>

using namespace std;

typedef bitset<5>	symbol;		//5bit = 1Symbol, Attention: sizeof(symbol) = 4

constexpr auto LINK16_LOG_FILEPATH = R"(./data/link16_log.txt)";
constexpr auto LINK16_DATA_FILEPATH = R"(./data/link16_data.txt)";
constexpr auto PLANES_FILEPATH = R"(./data/result.json)";

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

struct Plane
{
	string label;
	double vx;
	double vy;
	double vz;
	double x;
	double y;
	double z;
};