#pragma once
#include "Word.hpp"

// 75bit ContinueWord, can be sent out of sequence.

class ContinueWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15>
{
private:
	bitset<2> m_format;	  // Format：The binary representation of ContinueWord is 01.
	bitset<5> m_signal;	  // Siganl: Each J-series message allows a maximum of 32 continuation words to be defined.
	bitset<63> m_message; // Message: The first six bits store the length of the message (all 1 indicates that the message is full).
	bitset<5> m_BIP;	  // BIP: The first bit is idle, and the last four bits perform verification.

public:
	ContinueWord() : Word(), m_format(0b01) {}

	~ContinueWord() {}

	void rewrite(string &bit_str);
	void clear();
	void to_symbol();
	void handler_word(string &bit_data);
	void show();
	string toString_70B();
	string toString();
	bitset<5> getBIP();
	void setBIP(bitset<5> BIP);
	bitset<63> getMessage();
	string getData();
};