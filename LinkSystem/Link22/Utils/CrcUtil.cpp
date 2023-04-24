//
// Created by zeal on 2022/12/2.
//

#include "CrcUtil.h"

#define DATA_SIZE 16
#define CRC_SIZE 9

using namespace std;

static const int PATTERN9 = 0x1; // g(x) = x^9 + 1
static const int PATTERN16 = 0x1; // g(x) = x^16 + 1

bitset<9> CrcUtil::crc9(uint16 data[], int len) {
    cout<< "---------------------------------begin CRC9-------------------------------" << endl;
    cout <<"CRC- the datas are: ";
    for (int i = 0; i < len; ++i) {
        cout << hex << data[i] << " ";
    }
    cout << endl;

    uint remainder = 0;
    int nremainder = 0;
    int j,k;
    uint bit,lb;
    uint fb,cb;
    for (int i = 0; i < len; i++) {

        for (j = DATA_SIZE - 1; j >= 0; j--) {
            bit = (data[i] & (1 << j)) > 0;
            lb = (remainder & (1 << (CRC_SIZE - 1))) > 0;
            fb = lb ^ bit;
            nremainder = fb;
            for (k = 1; k < CRC_SIZE; k++) {
                cb = (remainder & (1 << (k - 1))) >> k - 1;
                if (PATTERN9 & (1 << k)) {
                    nremainder |= (cb ^ fb) << k;
                } else {
                    nremainder |= cb << k;
                }
            }
            remainder = nremainder;
        }
    }
    remainder &= 0x1FF;
    bitset<9> crcSet(remainder);

    cout << "CRC- code is: "  << crcSet.to_string() << endl;
    cout<< "---------------------------------end CRC9-------------------------------" << endl;

    return crcSet;
}

bitset<16> CrcUtil::crc16(uint16 data[], int len) {
    cout <<"CRC16- the datas are: ";
    for (int i = 0; i < len; ++i) {
        cout << hex << data[i] << " ";
    }
    cout << endl;
    uint CRC_SIZE16 = 16;
    uint remainder = 0;
    int nremainder = 0;
    int j,k;
    uint bit,lb;
    uint fb,cb;
    for (int i = 0; i < len; i++) {

        for (j = DATA_SIZE - 1; j >= 0; j--) {
            bit = (data[i] & (1 << j)) > 0;
            lb = (remainder & (1 << (CRC_SIZE16 - 1))) > 0;
            fb = lb ^ bit;
            nremainder = fb;
            for (k = 1; k < CRC_SIZE16; k++) {
                cb = (remainder & (1 << (k - 1))) >> k - 1;
                if (PATTERN16 & (1 << k)) {
                    nremainder |= (cb ^ fb) << k;
                } else {
                    nremainder |= cb << k;
                }
            }
            remainder = nremainder;
        }
    }
    remainder &= 0x1FF;
    bitset<16> crcSet(remainder);

    cout << "CRC16- code is: "  << crcSet.to_string() << endl;
    return crcSet;

}

void CrcUtil::get_crc16(uint8_t *bufData, uint buflen, uint8_t *pcrc) {
    int ret = 0;
    unsigned short CRC = 0xffff;
    unsigned short POLYNOMIAL = 0x8001;
    int i, j;

    //指令为空
    if (bufData == NULL) {
        cout << "CRC：输入的数据为空" << endl;
        return;
    }

    //校验计算的长度为0
    if (buflen == 0) {
        return;
    }

    for (i = 0; i < buflen; i++) {
        CRC ^= bufData[i];

        //总共八次右移操作
        for (j = 0; j < 8; j++) {
            if ((CRC & 0x0001) != 0) {
                //右移的移出位为1
                CRC >>= 1;
                CRC ^= POLYNOMIAL;
            } else {
                //右移的移出位为0
                CRC >>= 1;
            }
        }
    }


    printf("CRC::code = %X\n", CRC);
    //低位在前，高位在后
    pcrc[0] = (unsigned char) (CRC & 0x00ff);
    pcrc[1] = (unsigned char) (CRC >> 8);
}
