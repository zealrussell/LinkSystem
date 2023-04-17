#pragma once
#include "dataType.h"
#include <iostream>
#include <string.h>
#include "reed_solomon.h"

template <RS_Length codeLength, RS_Length dataLength>
class Word
{
public:
	symbol *m_S_word;  // Word after symbol conversion.
	symbol *m_RS_word; // Word after RS encoding.

	Word()
	{
		m_S_word = new symbol[dataLength]();
		m_RS_word = new symbol[codeLength]();
	}

	virtual ~Word()
	{
		delete[] m_S_word;
		m_S_word = nullptr;
		delete[] m_RS_word;
		m_RS_word = nullptr;
	}

	// Using RS error correction encoding to process message words, using the Schifra library.
	void RS_handler()
	{
		symbol *symbol_word = this->getS_word();

		string message(dataLength, 0x00);
		for (int i = 0; i < dataLength; i++)
		{
			message[i] = static_cast<char>(symbol_word[i].to_ulong());
		}

		symbol *symbol_RS_word = this->getRS_word();
		memset(symbol_RS_word, 0, sizeof(symbol) * codeLength);
		memcpy(symbol_RS_word, symbol_word, sizeof(symbol) * dataLength);

		if (!Link16_RS::RS(codeLength, dataLength, message, symbol_RS_word))
		{
			std::cout << "RS encoding successful" << std::endl;
		}
		else
		{
			std::cout << "RS encoding failed" << std::endl;
		}
	}

	virtual void clear()
	{
		memset(m_S_word, 0, sizeof(symbol) * dataLength);
		memset(m_RS_word, 0, sizeof(symbol) * codeLength);
	}

	string toString_STDP()
	{
		string res;
		for (int i = 0; i < codeLength; i++)
		{
			res += m_RS_word[i].to_string();
		}
		return res;
	}

	symbol *getS_word()
	{
		return m_S_word;
	}

	symbol *getRS_word()
	{
		return m_RS_word;
	}
	virtual void rewrite(string &bit_str) = 0;
	virtual void to_symbol() = 0;
	virtual string toString() = 0;
};