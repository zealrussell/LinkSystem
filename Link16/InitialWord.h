#pragma once
#include "Word.hpp"

// 75bit InitialWord
class InitialWord : public Word<RS_Length::code_31_15, RS_Length::data_31_15>
{
private:
	bitset<2> m_format;		// Format：The binary representation of InitialWord is 00.
	bitset<5> m_signal;		// Signal: Message category (n identification in Jn. m)
	bitset<3> m_sub_signal; // SubSignal: Message subclass (m identification in Jn. m)
	bitset<3> m_length;		// Length: Represents the total number of ExtendWords or ContinueWords after the initial word, up to 7
	bitset<57> m_message;	// Message: The first six bits store the length of the message (all 1 indicates that the message is full).
	bitset<5> m_BIP;		// BIP: The first bit is idle, and the last four bits perform verification.

public:
	InitialWord() : Word(), m_format(0b00) {}

	~InitialWord() {}

	void rewrite(string &bit_str);
	void clear();
	void to_symbol();
	void handler_word(string &bit_data, string &type);
	void show();
	string toString_70B();
	string toString();
	bitset<5> getBIP();
	void setBIP(bitset<5> BIP);
	void setSignal(bitset<5> signal);
	void setSubSignal(bitset<3> sub_signal);
	bitset<5> getSignal();
	bitset<3> getSubSignal();
	bitset<57> getMessage();
	string getData();
};