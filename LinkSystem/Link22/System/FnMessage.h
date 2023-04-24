//
// Created by zeal on 2023/1/24.
//

#ifndef LINK22_FNMESSAGE_H
#define LINK22_FNMESSAGE_H

#include <iostream>
#include <bitset>
class FnMessage {
    public:
        FnMessage();
        FnMessage(const std::string &msg, int N);
        std::string getStrData();
        std::bitset<72> getBitsetData();

        void setN(int N);
        void setLength(int length);
        void setMessage(const std::string &msg);

    private:
        std::bitset<3> n;
        std::bitset<6> length;
        std::bitset<62> message;
        std::bitset<72> data;
};


#endif //LINK22_FNMESSAGE_H
