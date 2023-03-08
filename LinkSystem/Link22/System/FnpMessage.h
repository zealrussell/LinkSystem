//
// Created by zeal on 2023/1/24.
//

#ifndef LINKSYSTEM_FNPMESSAGE_H
#define LINKSYSTEM_FNPMESSAGE_H
#include<iostream>
#include <bitset>

class FnpMessage {
    public:
        FnpMessage();
        FnpMessage(const std::string &msg,int n, int p);
        std::string getStrData();
        std::bitset<72> getBitsetData();

        void setN(int n);
        void setP(int p);
        void setLength(int length);
        void setMessage(const std::string &msg);

private:
    std::bitset<3> n;
    std::bitset<1> p;
    std::bitset<6> length;
    std::bitset<61> message;
    std::bitset<72> data;
};


#endif //LINKSYSTEM_FNPMESSAGE_H
