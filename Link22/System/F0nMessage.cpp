//
// Created by zeal on 2023/1/11.
//

#include "F0nMessage.h"

F0nMessage::F0nMessage() {
    printf(" F0n.m-p message has been constructed\n");
    data.reset(0);
    data.reset(1);
    data.reset(2);
    data.reset(3);
}
F0nMessage::F0nMessage(const std::string &msg, int N, int M, int P) {
    if (N < 0 || N > 3) return;
    if (M < 0 || M > 7) return;
    if (P < 0 || P > 3) return;
    if (msg.length() < 0 || msg.length() > 55) return;

    setN(N);
    setM(M);
    setP(P);
    setLength(msg.length());
    setMessage(msg);
    printf("F0%d.%d-%d message has been constructed: %s\n",N, M, P, getStrData().c_str());
}

std::string F0nMessage::getStrData() {
    std::string res = "0000";
    res += this->n.to_string();
    res += this->m.to_string();
    res += this->p.to_string();
    res += this->length.to_string();
    res += this->message.to_string();
    return res;
}

std::bitset<72> F0nMessage::getBitsetData() {
    std::string s = getStrData();
    std::bitset<72> res(s);
    return res;
}

void F0nMessage::setN(int N) {
    this->n = std::bitset<2>(N);
}

void F0nMessage::setM(int M) {
    this->m = std::bitset<3>(M);
}

void F0nMessage::setP(int P) {
    this->p = std::bitset<2>(P);
}

void F0nMessage::setLength(int LEN) {
    this->length = std::bitset<6>(LEN);
}

void F0nMessage::setMessage(const std::string &msg) {
    this->message = std::bitset<55>(msg);
}







