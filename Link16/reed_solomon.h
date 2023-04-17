#pragma once
#include <string>
#include <iostream>
#include "dataType.h"

#define NO_GFLUT
#include "schifra_galois_field.hpp"
#undef NO_GFLUT
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"
#include "schifra_reed_solomon_bitio.hpp"

namespace Link16_RS
{
    int RS(const size_t codeLength, const size_t dataLength, string &message, symbol *symbol_RS_word);
}