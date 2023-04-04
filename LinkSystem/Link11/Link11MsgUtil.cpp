//
// Created by zeal on 2022/12/8.
//

#include "Link11MsgUtil.h"


// 将二进制字符串“0000000100000010” 按 8bit 一组合并转化的字符数组
uint8_t *Link11MsgUtil::StrToCharArray(std::string &str_data, int char_length) {

    int len = str_data.length();

    if (len % 8 != 0) {
        std::cout << "ERROR::Wrong input string length % d, 8bit needed";

        return nullptr;
    }
    uint8_t* data = new uint8_t[char_length]();
    for (int i = 0; i < char_length; i++) {
        std::bitset<8> tmp = std::bitset<8>(str_data.substr(i * 8, 8));
        data[i] = static_cast<uint8_t>(tmp.to_ulong());
    }
    return data;
}
/**
 *
 * @param data
 * @param char_length
 * @return
 */
std::string Link11MsgUtil::CharArrayToBitStr(const uint8_t *data, int char_length) {
    std::string str;
    // 将每8位字符串转位uint8
    for(int i = 0; i < char_length; i++) {
        std::bitset<8> bs(data[i]);
        str += bs.to_string();
    }
    return str;
}
/**
 * 将任意消息转换成 0 1 字符串
 * @param data 任意消息
 * @return 0 1 字符串
 */
std::string Link11MsgUtil::StrToBitStr(const std::string &data) {
    size_t len = data.length();
    std::string res;
    for (int i = 0; i < len; i++) {
        std::bitset<8> bits = std::bitset<8>(data[i]);
        res += bits.to_string();
    }
    return res;
}

/**
 * 将0 1字符串转换成string
 * @param data
 * @return
 */
std::string Link11MsgUtil::BitStrToStr(const std::string &data) {
    if (data.length() == 0 || data.empty()) return "";
    size_t len = data.length();
    std::string res;
    for (int i = 0; i < len; i = i + 8) {
        std::string tmp;
        for (int j = 0; j < 8; j++) {
            tmp += data[i + j];
        }
        std::bitset<8> ch = std::bitset<8>(tmp);
        res += (char)ch.to_ulong();
    }
    return res;
}

/**
 * 将char转换成bitset<72>，每9个转换成一个
 * @param charArray
 * @param arraySize
 * @return
 */
std::bitset<72> *Link11MsgUtil::CharArrayToBitset(const uint8_t *charArray, int arraySize) {
    if (arraySize % 9 != 0) {
        std::cout << "";
        return nullptr;
    }
    std::bitset<72> *data = new std::bitset<72>[arraySize / 9];
    for(int i = 0; i < arraySize; i++) {
    }
    return data;
}