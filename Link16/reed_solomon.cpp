#include "reed_solomon.h"

namespace Link16_RS
{
    int RS(const size_t codeLength, const size_t dataLength, string &message, symbol *symbol_msg)
    {
        /* Finite Field Parameters */
        const std::size_t field_descriptor = 5;
        const std::size_t generator_polynomial_index = 0;
        const std::size_t generator_polynomial_root_count = 16;

        /* Reed Solomon Code Parameters */
        const std::size_t code_length = RS_Length::code_31_15; //(2^5 - 1)
        const std::size_t data_length = RS_Length::data_31_15;
        const std::size_t fec_length = RS_Length::fec_31_15;

        /* 5-bit Symbol Parameter */
        const int mask = 0x0000001F;

        /* Instantiate Finite Field and Generator Polynomials */
        const schifra::galois::field field(field_descriptor,
                                           schifra::galois::primitive_polynomial_size02,
                                           schifra::galois::primitive_polynomial02);

        schifra::galois::field_polynomial generator_polynomial(field);

        if (
            !schifra::make_sequential_root_generator_polynomial(field,
                                                                generator_polynomial_index,
                                                                generator_polynomial_root_count,
                                                                generator_polynomial))
        {
            std::cout << "Error - Failed to create sequential root generator!" << std::endl;
            return 1;
        }

        /* Instantiate Encoder and Decoder (Codec) */
        typedef schifra::reed_solomon::encoder<code_length, fec_length> encoder_t;

        const encoder_t encoder(field, generator_polynomial);

        /* Instantiate RS Block For Codec */
        schifra::reed_solomon::block<code_length, fec_length> block;

        /* Pad message with nulls up until the code-word length */
        message.resize(code_length, 0x00);

        /* Transform message into Reed-Solomon encoded codeword */
        //??Symbol???????message?��????????????block???��??��??????????????????block.data??(????????????????FEC??)
        if (!encoder.encode(message, block))
        {
            std::cout << "Error - Critical encoding failure! "
                      << "Msg: " << block.error_as_string() << std::endl;
            return 1;
        }

        //?????str_fec
        string str_fec(RS_Length::fec_31_15, 0x00);
        block.fec_to_string(str_fec);

        if (codeLength == RS_Length::code_31_15 && dataLength == RS_Length::data_31_15)
        {
            // Assemble(Word)
            for (int i = RS_Length::data_31_15; i < RS_Length::code_31_15; i++)
            {
                bitset<8> temp = bitset<8>(str_fec[i - RS_Length::data_31_15]);
                symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
            }
        }

        else if (codeLength == RS_Length::code_16_7 && dataLength == RS_Length::data_16_7)
        {
            // Assemble(Header)??????fec???7Symbol?????��
            for (int i = RS_Length::data_16_7; i < RS_Length::code_16_7; i++)
            {
                bitset<8> temp = bitset<8>(str_fec[i]);
                symbol_msg[i] = symbol(temp.to_string().substr(3, 5));
            }
        }
        else
        {
            return 1;
        }
        return 0;
    }
}