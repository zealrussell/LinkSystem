#pragma once
#include <string>
#include <iostream>
#include "hamming.h"
#include "Link11MsgUtil.h"
#include <json/Json.h>

using namespace std;

#define dataLen 24
#define FrameLen 29
#define PreambleLen 5

class Decode
{
public:
	yazi::json::Json CrackMessage(string data, string &msg, int &n);

private:
	string CrackDataFrame(const std::string& msg, int& n);
	string CrackPreambleFrame(const std::string& msg);
	string CrackPhaseFrame(const std::string& msg);
};



