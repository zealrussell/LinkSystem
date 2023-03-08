//
// Created by zeal on 2022/12/2.
//

#ifndef LINKSYSTEM_CRCUTIL_H
#define LINKSYSTEM_CRCUTIL_H
#include <iostream>
#include <bitset>
typedef unsigned short int uint16;
typedef unsigned int uint;
class CrcUtil {
    public:
        static std::bitset<9> crc9(uint16 data[], int len);
        static std::bitset<16> crc16(uint16 data[], int len);
        void get_crc16 (uint8_t *bufData, uint buflen, uint8_t *pcrc);
};


#endif //LINKSYSTEM_CRCUTIL_H
