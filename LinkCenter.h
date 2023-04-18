#pragma once

#include "Link16/Link16Center.h"
#include "Link22/Link22Center.h"
#include "Link11/Link11Center.h"

class LinkCenter
{
public:
	void From22to16();
	void From16to22(const string& msg_encrypted_16, string& msg_encrypted_22);
	void From11to16();
	void From16to11();

	void create_Link11();
	void create_Link16(const std::string &msg, int n, int m);
	void create_Link22(const std::string &msg, int n, int m = 0, int p = 0);

private:
	std::string getData();

	Link11Center link11Center;
	Link16Center link16Center;
	Link22Center link22Center;
};