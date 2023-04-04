#pragma once
#include <string>
#include <iostream>
#include "hamming.h"
#include "Link11MsgUtil.h"

using namespace std;

#define dataLen 24
#define FrameLen 29
#define PreambleLen 5

class Decode
{
public:
	string CrackMessage(uint8_t* msg, int &n);

private:
	string CrackDataFrame(const std::string& msg, int& n);
	string CrackPreambleFrame(const std::string& msg);
	string CrackPhaseFrame(const std::string& msg);
};



