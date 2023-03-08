//
// Created by zeal on 2023/1/11.
//

#ifndef LINKSYSTEM_F0NMESSAGE_H
#define LINKSYSTEM_F0NMESSAGE_H
#include <iostream>
#include <bitset>

class F0nMessage {
    public:
        F0nMessage();
        F0nMessage(const std::string &msg, int N, int M, int P);
        std::string getStrData();
        std::bitset<72> getBitsetData();

        void setN(int N);
        void setM(int M);
        void setP(int P);
        void setLength(int LEN);
        void setMessage(const std::string &msg);

    private:
        std::bitset<2> n;
        std::bitset<3> m;
        std::bitset<2> p;
        std::bitset<6> length;
        std::bitset<55> message;
        std::bitset<72> data;
};


#endif //LINKSYSTEM_F0NMESSAGE_H
