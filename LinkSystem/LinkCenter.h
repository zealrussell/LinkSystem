#pragma once

#include "Link16/Link16Center.h"
#include "Link22/Link22Center.h"

class LinkCenter
{
public:
	void From22to16();
	void From16to22();

private:
	Link16Center link16Center;
	Link22Center link22Center;
};

