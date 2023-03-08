//
// Created by zeal on 2023/1/24.
//

#include "FnMessage.h"

FnMessage::FnMessage() {
    printf(" Fn消息被构造\n");
    data.reset(0);
    data.reset(2);
}

FnMessage::FnMessage(const std::string &msg, int N) {
    if (N != 2 && N != 3 && N != 6) return;
    if (msg.length() < 0 || msg.length() > 62) return;

    setN(N);
    setLength(msg.length());
    setMessage(msg);
    printf("构造了 F%d 消息：%s\n", N, getStrData().c_str());
}

std::string FnMessage::getStrData() {
    std::string res = "0";
    res += this->n.to_string();
    res += this->length.to_string();
    res += this->message.to_string();
    return res;
}

std::bitset<72> FnMessage::getBitsetData() {
    std::string s = getStrData();
    std::bitset<72> res(s);
    return res;
}

void FnMessage::setN(int N) {
    this->n = std::bitset<3>(N);
}

void FnMessage::setLength(int LEN) {
    this->length = std::bitset<6>(LEN);
}

void FnMessage::setMessage(const std::string &msg) {
    this->message = std::bitset<62>(msg);
}
