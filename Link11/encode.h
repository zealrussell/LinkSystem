#ifndef ENCODE_H
#define ENCODE_H

#include <string>
#include <iostream>
#include "hamming.h"
#include "Link11MsgUtil.h"
#include <json/Json.h>

using namespace std;

#define DataLen 24
#define FrameLen 29
#define PreambleLen 5

class Encode
{
public:
	Encode();
	~Encode();
	yazi::json::Json BuildMessage(int type, int n, const string& msg);


private:
	string BuildDataFrame(int type, int n, const std::string& msg);
	string BuildPreambleFrame();
	string BuildPhaseFrame();
	string BuildStartFrame();
	string BuildEndFrame();
	int decToBin(int dec);

	Link11MsgUtil msgUtil;
};


#endif