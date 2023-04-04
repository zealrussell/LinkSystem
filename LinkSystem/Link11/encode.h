#ifndef ENCODE_H
#define ENCODE_H

#include <string>
#include <iostream>
#include "hamming.h"
#include "Link11MsgUtil.h"

using namespace std;

#define DataLen 24
#define FrameLen 29
#define PreambleLen 5

class Encode
{
public:
	Encode();
	~Encode();
	uint8_t* BuildMessage(int type, int n, string& msg);


private:
	string BuildDataFrame(int type, int n, const std::string& msg);
	string BuildPreambleFrame();
	string BuildPhaseFrame();
	string BuildStartFrame();
	string BuildEndFrame();
	int decToBin(int dec);

};


#endif