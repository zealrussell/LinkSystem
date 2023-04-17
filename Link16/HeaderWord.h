#pragma once
#include "Word.hpp"

// 35bitHeaderWord
class HeaderWord : public Word<RS_Length::code_16_7, RS_Length::data_16_7>
{
private:
	bitset<3> m_type; // Time slot type(Specific regulations check table)
	bitset<1> m_PR;	  // When transmitting free text, used to identify whether the transmission waveform is a double pulse character or a single pulse character
	bitset<15> m_STN; // Terminal source track number, the sending source number of this time limit message
	bitset<16> m_SDU; // Confidential data unit, identifying the encryption method (currently agreed upon: the first 8 bits represent the encryption method, and the last 8 bits are 11001010)
	// AES:00001010  DES:00001011    RSA:00001111

public:
	explicit HeaderWord(bitset<15> STN) : Word(), m_type(bitset<3>("100")), m_PR(bitset<1>(0)),
										  m_SDU(bitset<16>("0000101011001010"))
	{
		m_STN = STN;
	}

	HeaderWord(bitset<3> type, bitset<1> PR, bitset<15> STN) : Word(), m_SDU(bitset<16>("0000101011001010"))
	{
		m_type = type;
		m_PR = PR;
		m_STN = STN;
	}

	~HeaderWord() {}

	void rewrite(string &bit_str);
	void show();
	string toString();
	string toString_15B();
	void to_symbol();
	void setType(bitset<3> type);
	void setPR(bitset<1> PR);
	bitset<15> getSTN();
	bitset<16> getSDU();
	void setSTN(bitset<15> STN);
	void setSDU(bitset<16> SDU);
};