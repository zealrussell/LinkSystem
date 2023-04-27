//
// Created by zeal on 2022/12/2.
//

#ifndef LINK22_CONSTRUCTCENTER_H
#define LINK22_CONSTRUCTCENTER_H

#include <vector>
#include <json/Json.h>

#include "../Utils/MsgUtil.h"
#include "../Utils/CrcUtil.h"
#include "../Utils/AESUtil.h"
#include "../Utils/RSInclude/rs.hpp"

using namespace yazi::json;
class ConstructCenter {
    public:
        ConstructCenter();
    
        ~ConstructCenter();

        // 入口
        Json constructMessage(const std::string &msg, int n = 0,int m = 0, int p = 0);
        // 解密
        Json crackMessage(const uint8_t *data, int symbolNum, std::string &msg, int &n, int &m, int &p);

        static void print(const unsigned char* state, int len);

    private:
        unsigned char iv[16] = {103,35,148,239,76,213,47,118,255, 222,123,176,106,134,98,92};
        unsigned char key[16] = {143,194,34,208,145,203,230,143,177,246,97,206,145,92,255,84};

        void initCenter();
        void changeKey(const uint8_t *newKey);

        uint8_t *beginConstruct(const std::string &msg, int type, int n = 0, int p = 0,int m = 0);
        uint8_t *beginAssemble(const std::bitset<72> &b1, const std::bitset<72> &b2);
        uint8_t *beginDisassemble(const uint8_t *data);

        // 编码相关
        uint8_t *beginAes(const std::bitset<72> *data, int arrayNum);
        uint8_t *beginCrc(const uint8_t *data, int arrayNum);
        uint8_t *beginRs(const uint8_t *crcCode, const uint8_t *msgCode, int arrayNum = 18);

        // 解码相关
        uint8_t *beginDeAes(const uint8_t *data, int arrayNum);
        bool beginDeCrc(const uint8_t* crcCode, const uint8_t *data, int arrayNum);
        uint8_t *beginDeRs(const uint8_t *rsCode, int arrayNum);

        Json link22EncodeJson;
        Json link22DecodeJson;
        
        MsgUtil msgUtil;
        AESModeOfOperation aes;
        CrcUtil crcUtil;
        RS::ReedSolomon<21, 15> rs;
        

};



#endif //LINK22_CONSTRUCTCENTER_H
