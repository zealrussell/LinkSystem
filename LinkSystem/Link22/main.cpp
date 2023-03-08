#include <iostream>

#include "System/ConstructCenter.h"

using namespace std;

int main() {


     ConstructCenter con;
     uint8_t *res = con.constructMessage();
     con.crackMessage(res);
    //unsigned char ss[]  = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c, 0x98} ;
    //CrcUtil crc;
    //uint8_t *crcCode = new uint8_t[2];
    //crc.get_crc16(ss,18,crcCode);


    return 0;
}
