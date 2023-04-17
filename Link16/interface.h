#pragma once
#include "tools.h"
#include "global.h"

#include "STDPMsg.h"

namespace interface
{
    string encoder_Link16(int32_t n, int32_t m, const string &inputs);
    int32_t decoder_Link16(string &raw_data, int32_t &n, int32_t &m);
}