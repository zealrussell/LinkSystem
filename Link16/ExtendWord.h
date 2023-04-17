#pragma once
#include "Word.hpp"

// 75bit ExtendWord, must be sent in sequence.

class ExtendWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15>
{
private:
	bitset<2> m_format;	  // Format：The binary representation of ExtendWord is 10.
	bitset<68> m_message; // Message: The first six bits store the length of the message (all 1 indicates that the message is full).
	bitset<5> m_BIP;	  // BIP: The first bit is idle, and the last four bits perform verification.

public:
	ExtendWord() : Word(), m_format(0b10) {}

	~ExtendWord() {}

	void rewrite(string &bit_str);
	void clear();
	void to_symbol();
	void handler_word(string &bit_data);
	void show();
	string toString_70B();
	string toString();
	bitset<5> getBIP();
	void setBIP(bitset<5> BIP);
	bitset<68> getMessage();
	string getData();
};