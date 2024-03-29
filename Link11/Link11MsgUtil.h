//
// Created by zeal on 2022/12/8.
//

#ifndef LINK11_MSGUTIL_H
#define LINK11_MSGUTIL_H
#include <iostream>
#include <bitset>
#include <string>

class Link11MsgUtil{
public:
    uint8_t* StrToCharArray(std::string &str_data, int char_length);

    std::string StrToBitStr(const std::string &data);
    std::string BitStrToStr(const std::string &data);

    template<size_t N> std::string BitsetToStr(const std::bitset<N> &b);
    template<size_t N> uint8_t *BitsetToCharArray(const std::bitset<N> *b, int arraySize);
    std::string CharArrayToBitStr(const uint8_t *data, int char_length);
    std::bitset<72> *CharArrayToBitset(const uint8_t *charArray, int arraySize);

    // 将内容保存至文件中

    void saveToFile(const std::string& FILE_NAME, std::string& data);
    void getDataFromFile(const std::string& FILENAME, std::string& data);
    void deleteFile(const std::string& FILE_NAME);

    static const std::string FILE_NAME;
};

template<size_t N> std::string Link11MsgUtil::BitsetToStr(const std::bitset<N> &b) {
    std::string s = b.to_string();
    return s;
}

/**
 * 将bitset转为uint8数组
 * @tparam N
 * @param b
 * @param arraySize
 * @return
 */
template<size_t N>
uint8_t *Link11MsgUtil::BitsetToCharArray(const std::bitset<N> *b, int arraySize) {
    int len = N * arraySize;
    if (len % 8 != 0) {
        printf("ERROR::Wrong input string length %d,8bit needed ",len);
        return nullptr;
    }
    // 1.将bitset转换成字符串
    std::string s;
    for (int i = 0; i < arraySize; i++) {
        s += BitsetToStr(b[i]);
    }

    // 2.将每8位字符串转位uint8
    uint8_t* data = new uint8_t[len / 8];
    int j = 0;
    for (int i = 0; i < s.length(); i+=8) {
        std::string temp = s.substr(i, 8);
        uint8_t d = std::stoi(temp, 0,2);
        data[j++] = d;
    }
    return data;
}


#endif //LINK11_MSGUTIL_H
