//
// Created by zeal on 2022/12/8.
//

#include "MsgUtil.h"
#include <fstream>
#include <string>
#include <map>

const std::string MsgUtil::FILE_NAME = "./data.txt";
extern std::map<std::string, int> CodetoType;
extern std::map<std::string, std::string> CodetoName;

//输入字符串str_data长度必须为8的整数倍
//功能：将二进制字符串“0000000100000010”按8bit一组合并转化{ "1", "2" }的字符数组
uint8_t *MsgUtil::StrToCharArray(const std::string &str_data, int char_length) {
    size_t len = str_data.length();
    if (len % 8 != 0) {
        std::cout << "Incorrect input";
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
std::string MsgUtil::CharArrayToBitStr(const uint8_t *data, int char_length) {
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
std::string MsgUtil::StrToBitStr(const std::string &data) {
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
std::string MsgUtil::BitStrToStr(const std::string &data) {
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
std::bitset<72> *MsgUtil::CharArrayToBitset(const uint8_t *charArray, int arraySize) {
    if (arraySize % 9 != 0) {
        std::cout << "";
        return nullptr;
    }
    std::bitset<72> *data = new std::bitset<72>[arraySize / 9];
    for(int i = 0; i < arraySize; i++) {
    }
    return data;
}
/**
 * 从F系列消息字01字符串中获取报文数据
 * @param message 72位01字符串
 * @return 报文消息
 */
std::string MsgUtil::getDataFromMessage(const std::string &message) {
    // F系列消息 系列指示符为 0
    if (message.length() != 72 || message[0] != '0') return "";
    printf("The messages before extract: %s \n", message.c_str());
    // 1. 判断M消息类型
    std::string type = message.substr(1,3);
    int pos = 0;
    // 标识指示符
    if (type == "000") {
        // F0n.m-p
        pos = 11;
    } else if (type == "001" || type == "100" || type == "101") {
        // Fn-p
        pos = 5;
    } else if (type == "010" || type == "011" || type == "110") {
        // Fn
        pos = 4;
    } else return "";
    // 2. 读取报文长度
    int len = std::stoi(message.substr(pos,6),0,2);
    // 3. 获取消息字数据
    std::string res = message.substr(72 - len, len);
    printf("The messages after extract: %s\n",res.c_str());

    return res;
}

/**
 * 从F系列消息字01字符串中获取报文类型
 * @param messagetype
 * @return
 */
void MsgUtil::getTypeFromMessage(const std::string &message, int &n_out, int &m_out, int &p_out) {
    // F系列消息 系列指示符为 0
    if (message.length() != 72 || message[0] != '0') return;
    printf("The messages type needed to get be from link22 are %s \n", message.c_str());
    // 1. 判断M消息类型
    
    n_out = 0;
    m_out = 2;
    p_out = 7;

    if (message[0] != 0) return;

    // std::string n = message.substr(1, 4);
    int n = getNumFromLinkMsg(message.substr(1, 4));
    // 标识指示符
    // F0n.m-p
    if (n == 0) {
        n_out = getNumFromLinkMsg(message.substr(4, 6));
        m_out = getNumFromLinkMsg(message.substr(6, 9));
        p_out = getNumFromLinkMsg(message.substr(9, 11));
        // Fn-p
    } else if (n == 1 || n == 4 || n == 5) {
        n_out = n;
        m_out = -1;
        p_out = getNumFromLinkMsg(message.substr(4, 5));
    // Fn
    } else if (n == 2 || n == 3 || n == 6) {
       
        n_out = n;
    } else return;

}

int MsgUtil::getTypeByNPM(int n, int p, int m)
{
    std::string key = n + "_" + m + '_' + p;
    return CodetoType[key];
}

// 从link22比特报文中获取n m p的十进制值
int MsgUtil::getNumFromLinkMsg(std::string msg) {
    std::reverse(msg.begin(), msg.end());
    return std::stoi(msg, NULL, 2);
}
// 文件操作******************************************* 
 
void MsgUtil::saveToFile(const std::string &FILE_NAME, const uint8_t *data, int dataNum) {
    std::ofstream fout;
    fout.open(FILE_NAME, std::ofstream::out);
    if (fout.is_open() == false) {
        std::cout << "ERROR:: open the file " << FILE_NAME << "failed!!   " << std::endl;
        return;
    }
    std::cout << "FILE:: begin save data to " <<FILE_NAME << std::endl;
    std::string msg = CharArrayToBitStr(data, dataNum);
    fout << msg;
    fout.close();
    std::cout << "FILE:: save finish " << std::endl << std::endl;
}

void MsgUtil::getDataFromFile(const std::string &FILENAME, std::string &data) {
    std::ifstream fin;
    fin.open(FILENAME, std::ios::in);
    if (fin.is_open() == false) {
        std::cout << "Error:: open file " << FILENAME << "failed!!! " << std::endl;
        return;
    }
    //每次读一行
    std::cout << "The data readed from txt are: " << std::endl;
    while (fin >> data) {
        std::cout << data <<  std::endl;
    }
    std::cout << "total:" << data.length() << std::endl << std::endl;
    fin.close();
}