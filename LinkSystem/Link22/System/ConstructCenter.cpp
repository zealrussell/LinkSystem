//
// Created by zeal on 2022/12/2.
//

#include "ConstructCenter.h"
#include "F0nMessage.h"
#include "FnpMessage.h"
#include "FnMessage.h"

#define DMSGLEN 2 * MSGLEN

ConstructCenter::ConstructCenter(){
    printf("Construct begin \n\n");
    initCenter();
    typeMap[0][7][10] = "秘钥滚动";
    typeMap[0][1][2] = "电子战 位置";
}


uint8_t *ConstructCenter::beginAssemble (const std::bitset<72> &b1, const std::bitset<72> &b2) {
    std::bitset<72> p[2];
    p[0] = b1;
    p[1] = b2;
    uint8_t *aesCode = beginAes(p, 2);
    uint8_t *crcCode = beginCrc(aesCode, 18);
    uint8_t *rsCode = beginRs(crcCode, aesCode,18);
    delete aesCode;
    delete crcCode;

    return rsCode;
}

/**
 * 解码过程
 * @param data 36个消息
 * @return 解码后的18个消息
 */
uint8_t *ConstructCenter::beginDisassemble(const uint8_t *data) {

    uint8_t *rsCode = beginDeRs(data,36);

    uint8_t crcCode[2];
    uint8_t aesCode[18];
    // 从rsCode中提取crcCode和aesCode
    memcpy(crcCode, rsCode, 2 * sizeof(uint8_t));
    memcpy(aesCode, rsCode + 3 * sizeof(uint8_t), 18 * sizeof(uint8_t));
    delete rsCode;

    // 通过比较crcCode，判断传输过程中是否发生错误
    bool crcFlag = beginDeCrc(crcCode, aesCode, 18);
    if (!crcFlag) {
        printf("ERROR:: CRC code checked failed!!!\n");
        return nullptr;
    }

    uint8_t *message = beginDeAes(aesCode, 18);

    return message;
}


void ConstructCenter::initCenter() {
    aes.set_key(key);
    aes.set_mode(MODE_OFB);
    aes.set_iv(iv);
}


/**
 * 进行aes
 *
 * @param data
 * @return 18个uint
 */
uint8_t *ConstructCenter::beginAes(const std::bitset<72> *data ,int arrayNum) {
    printf("-------------------------------------------begin AES-------------------------------- \n");

    uint8_t *input =  msgUtil.BitsetToCharArray(data,arrayNum);
    uint8_t temp[100];
    int inlen = sizeof(uint8_t) * 9 * arrayNum;
    printf("AES::before aes: ");
    print(input, inlen);
    int outlen = aes.Encrypt(input, inlen, temp);

    uint8_t *output = new uint8_t [outlen];
    memcpy(output, temp, outlen);
    printf("AES::after aes %d : ",outlen);
    print(output, outlen);

    delete input;
    printf("-------------------------------------------end AES-------------------------------------\n\n");
    return output;
}


/**
 * 生成16位crc码
 * @param msg 待编码的消息
 * @param arrayNum uint8个数
 * @return crc码
 */
uint8_t *ConstructCenter::beginCrc(const uint8_t *msg, int arrayNum) {
    printf("------------------------------------------begin CRC16----------------------------------\n");
    uint8_t data[18] = {0};
    memcpy(data, msg, arrayNum * sizeof(uint8_t));
    uint8_t *code = new uint8_t[2];
    crcUtil.get_crc16(data,arrayNum, code);

    printf("Crc code is: ");
    print(code,2 * sizeof(uint8_t));
    printf("------------------------------------------end CRC16------------------------------------\n\n");
    return code;
}


/**
 * https://github.com/mersinvald/Reed-Solomon
 * RS<36,21>
 * @param crcCode
 * @param msgCode
 * @param arrayNum
 * @return 36个
 */
uint8_t *ConstructCenter::beginRs(const uint8_t *crcCode, const uint8_t *msgCode, int arrayNum) {
    printf("-------------------------------------------begin RS--------------------------------------\n");

    // 1.合并消息
    uint8_t data[21] = {0};
    memcpy(data, crcCode, 2 * sizeof(uint8_t));
    memcpy(data + 3, msgCode, 18 * sizeof(uint8_t));

    printf("RS::code before: ");
    print(data,21);
    // 2.rs编码
    uint8_t *output = new uint8_t[36];
    rs.Encode(data, output);
    printf("RS::code after: ");
    print(output,36);
    printf("-------------------------------------------end RS--------------------------------------\n\n");
    return output;
}

/**
 * rs解码
 * @param rsCode
 * @param arrayNum
 * @return 返回21个
 */
uint8_t *ConstructCenter::beginDeRs(const uint8_t *rsCode, int arrayNum) {
    printf("-------------------------------------------begin DeRS--------------------------------------\n");
    printf("Code before deres:");
    print(rsCode, arrayNum);

    uint8_t *output = new uint8_t[21];
    rs.Decode(rsCode,output);

    printf("Code after deres:");
    print(output, 21);
    printf("-------------------------------------------end DeRS--------------------------------------\n\n");
    return output;
}

bool ConstructCenter::beginDeCrc(const uint8_t *crcCode, const uint8_t *data, int arrayNum) {
    printf("-------------------------------------------begin DeCrc--------------------------------------\n");
    printf("Original crcCode:: ");
    print(crcCode, 2);
    printf("Original data:: ");
    print(data, arrayNum);

    uint8_t *code = new uint8_t[2];
    crcUtil.get_crc16(const_cast<uint8_t *>(data), arrayNum,code);

    printf("Now crcCode:: ");
    print(code, 2);

    int res = memcmp(code, crcCode, 2 * sizeof(uint8_t));
    printf("-------------------------------------------end DeCrc--------------------------------------\n\n");
    if (res != 0) return false;
    else return true;
}

/**
 * 解aes
 * @param data
 * @return
 */
uint8_t *ConstructCenter::beginDeAes(const uint8_t *data, int arrayNum) {
    printf("-------------------------------------------begin DeAes--------------------------------------\n");
    printf("Code before deaes:: ");
    print(data, arrayNum);

    uint8_t *output = new uint8_t [18];
    aes.Decrypt(const_cast<unsigned char *>(data), 18, output);

    printf("Code after deaes:: ");
    print(output, 18);
    printf("-------------------------------------------end DeAes--------------------------------------\n\n");
    return output;
}

/**
 * ******
 * 系统入口
 * ******
 * @return
 */

void ConstructCenter::constructMessage(const std::string &msg, int n, int m, int p) {
    // printf("Please selece Link22 type: \n");
    // printf("1. F0n.m-p    2. Fn-p     3. Fn\n");
    uint8_t *res = nullptr;
    int type = msgUtil.getTypeByNPM(n, p, m);

    if (type == 1) {
        printf("F0n.m-p message will be construct....\n");
        // 更改秘钥消息
        if (n == 0 && m == 7 && p == 10) {
            const uint8_t *message = msgUtil.StrToCharArray(msg, msg.length());
            changeKey(message);
            delete[] message;
            return;
        } else if (n == 0 && m == 1 && p == 2) {
          
            res = beginConstruct(msg, 1, n ,p ,m);
        } else {
            res = beginConstruct(msg, 1, n, p, m);
        }
    } else if (type == 2) {
        res = beginConstruct(msg, 2, n ,p);
    } else if (type == 3) {
        res = beginConstruct(msg, 3, n);
    }
}

// 填充，生成F系列消息
uint8_t *ConstructCenter::beginConstruct(const std::string &msg, int type, int n, int p, int m) {
    // 1. 将输入的string消息转换成01字符串
    printf("\n The message needed to be constructed is: %s\n",msg.c_str());
    std::string str = msgUtil.StrToBitStr(msg);
    printf("The %lu bit binary string before compeleted are: %s\n",str.length(),str.c_str());
    // 2. 计算切分的报文数
    int strLen = str.length();
    int MSGLEN;
    if (type == 1) MSGLEN = 55;
    else if (type == 2) MSGLEN = 61;
    else MSGLEN = 62;
    int num = 0;
    while (num * DMSGLEN < strLen) num++;
    printf("%d data will be constructed \n",num);
    uint8_t *temp = new uint8_t [num * 36 * sizeof(uint8_t)];
    uint8_t *res = temp;
    // 3. 分段填充
    int remainLen = str.length();
    int i = 0;
    // 3.1 处理整的部分
    while(remainLen > DMSGLEN) {
        uint8_t *data = nullptr;
        if (type == 1) {
            F0nMessage m1(str.substr(i,MSGLEN), n, m, p);
            F0nMessage m2(str.substr(i + MSGLEN,DMSGLEN), n, m, p);
            data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
        } else if (type == 2) {
            FnpMessage m1(str.substr(i,MSGLEN), n, p);
            FnpMessage m2(str.substr(i + MSGLEN,DMSGLEN), n, p);
            data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
        } else if (type == 3) {
            FnMessage m1(str.substr(i,MSGLEN), n);
            FnMessage m2(str.substr(i + MSGLEN,DMSGLEN), n);
            data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
        }
        remainLen -= DMSGLEN;
        i += DMSGLEN;
        memcpy(temp, data, 36);
        temp += 36 * sizeof(uint8_t);
        delete data;
    }
    // 3.2 处理不足的部分
    if(remainLen > 0 && remainLen <= DMSGLEN) {
        uint8_t *data = nullptr;
        if(remainLen > MSGLEN) {
            if (type == 1) {
                F0nMessage m1(str.substr(i,MSGLEN), n, m, p);
                F0nMessage m2(str.substr(i + MSGLEN), n, m, p);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            } else if (type == 2) {
                FnpMessage m1(str.substr(i,MSGLEN), n, p);
                FnpMessage m2(str.substr(i + MSGLEN), n, p);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            } else if (type == 3) {
                FnMessage m1(str.substr(i,MSGLEN), n);
                FnMessage m2(str.substr(i + MSGLEN), n);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            }
        } else {
            if (type == 1) {
                F0nMessage m1(str.substr(i), n, m, p);
                F0nMessage m2("", n, m, p);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            } else if (type == 2) {
                FnpMessage m1(str.substr(i), n, p);
                FnpMessage m2("", n, p);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            } else if (type == 3) {
                FnMessage m1(str.substr(i), n);
                FnMessage m2("", n);
                data = beginAssemble(m1.getBitsetData(), m2.getBitsetData());
            }
        }
        memcpy(temp, data, 36);
        temp += 36 * sizeof(uint8_t);
        delete data;
    }

    printf("The final %d symbol data after encode are: ", num);
    // 1symbol = 144bit = 36uint8
    print(res, 36 * num);
    printf("\n\n\n");
    msgUtil.saveToFile(MsgUtil::FILE_NAME, res, 36 * num);
    return res;
}

/**
 * 解密函数
 * @param data 待解密是数据
 */
void ConstructCenter::crackMessage(const uint8_t *data, int symbolNum, std::string &msg, int &n, int &m, int &p) {
    // int arrayNum;
    // printf("请输入码元个数：");
    // std::cin >> arrayNum;
    printf("Origin %d data: ", symbolNum);
    print(data, 36 * symbolNum);

    std::string message;
    bool flag = true;
    // 1.分为每symbol传入
    for (int i = 0; i < 36 * symbolNum; i += 36) {
        uint8_t tmp[36];
        memcpy(tmp, data + i, 36 * sizeof(uint8_t));
        // 2. 解码成 18，即两个 72bit 数据
        uint8_t *symbol = beginDisassemble(tmp);
        std::string str = msgUtil.CharArrayToBitStr(symbol, 18);
        delete symbol;
        // 3. 从link22消息中提取信息
        if (str.length() == 144) {
            message += msgUtil.getDataFromMessage(str.substr(0, 72));
            message += msgUtil.getDataFromMessage(str.substr(72,72));
            if (flag) {
                msgUtil.getTypeFromMessage(str.substr(0, 72),n,m,p);
                flag != flag;
            }
        }
    }

    // 将二进制消息转换成字符消息
    msg = msgUtil.BitStrToStr(message);
    printf("DECOD:: The real message is: %s\n", msg.c_str());
}


/**
 * 更新aes秘钥操作
 * @param newKey 新秘钥
 */
void ConstructCenter::changeKey(const uint8_t *newKey) {
    memcpy(this->key, newKey, 16 * sizeof(uint8_t));
    printf("New AES key is:");
    print(newKey, 16);
}

/**
 * 打印uint8数组
 * @param state 数组
 * @param len 数组长度
 */
void ConstructCenter::print(const uint8_t *state, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("%x  ", state[i]);
    }
    printf("\n");
}


ConstructCenter::~ConstructCenter() {
    printf("Construct finish!!\n");
}



