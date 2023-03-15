#pragma once
#include "tools.h"
#include "global.h"

#include "decodeTools.h"
#include "STDPMsg.h"

int32_t encoder(int32_t n, int32_t m, const string& inputs);
int32_t decoder(string& raw_data, int32_t& n, int32_t& m);