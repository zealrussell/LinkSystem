#include <iostream>
#include <bitset>
#include "ContinueWord.h"
#include "tools.h"

// Rewrite all main fields in the word with the bit string "bit_str".
// The string must only consist of 0 or 1 and have a length of 75.
void ContinueWord::rewrite(string &bit_str)
{
	if (bit_str.length() != 75)
	{
		std::cout << "[rewrite]: bit_str length is illegal" << std::endl;
		return;
	}
	for (int i = 0; i < 75; i++)
	{
		if (bit_str[i] != '0' && bit_str[i] != '1')
		{
			std::cout << "[rewrite]: bit_str content is illegal" << std::endl;
			return;
		}
	}
	m_format = bitset<2>(bit_str.substr(0, 2));
	m_signal = bitset<5>(bit_str.substr(2, 7));
	m_message = bitset<63>(bit_str.substr(7, 70));
	m_BIP = bitset<5>(bit_str.substr(70, 5));
}

void ContinueWord::clear()
{
	m_format.reset();
	m_signal.reset();
	m_message.reset();
	m_BIP.reset();
	Word::clear();
}

void ContinueWord::to_symbol()
{
	string temp = {0};
	temp = m_format.to_string() + m_signal.to_string() + m_message.to_string() + m_BIP.to_string();

	int flag = 0;
	for (int i = 0; i < 15; i++)
	{
		m_S_word[i] = symbol(temp.substr(flag, 5));
		flag += 5;
	}
}

void ContinueWord::handler_word(string &bit_data)
{
	size_t len = bit_data.length();
	bitset<63> message;
	if (len < 57)
	{
		message = bitset<63>(bit_data);
		bitset<63> high = bitset<63>(len);
		high = high << 57;
		message = message | high;
		bit_data.clear();
	}
	else
	{
		string temp = bit_data.substr(0, 57);
		bit_data.erase(0, 57);
		message = bitset<63>(temp);
		bitset<63> high;
		high.set();
		high = high << 57;
		message = message | high;
	}
	m_message = message;
}

void ContinueWord::show()
{
	std::cout << "======"
			  << "ContinueWord has been filled in"
			  << "======" << std::endl;
	std::cout << "continue_word:" << std::endl;
	std::cout << "\tformat\t\t=\t" << m_format << std::endl;
	std::cout << "\tsignal\t\t=\t" << m_signal << std::endl;
	std::cout << "\tmessage\t\t=\t" << m_message << std::endl;
	std::cout << "\tBIP\t\t=\t" << m_BIP << std::endl;
	Tools::save_msg(LINK16_LOG_FILEPATH, "======ContinueWord has been filled in======");
	Tools::save_msg(LINK16_LOG_FILEPATH, "continue_word:");
	Tools::save_msg(LINK16_LOG_FILEPATH, "\tformat\t\t=\t" + m_format.to_string());
	Tools::save_msg(LINK16_LOG_FILEPATH, "\tsignal\t\t=\t" + m_signal.to_string());
	Tools::save_msg(LINK16_LOG_FILEPATH, "\tmessage\t\t=\t" + m_message.to_string());
	Tools::save_msg(LINK16_LOG_FILEPATH, "\tBIP\t\t\t=\t" + m_BIP.to_string());
}

void ContinueWord::assembleJson(Json &json)
{
	Json tmpJson;
	tmpJson["format"] = m_format.to_string();
	tmpJson["signal"] = 0;
	tmpJson["subSignal"] = 0;
	tmpJson["length"] = 0;
	tmpJson["message"] = m_message.to_string();
	tmpJson["BIP"] = m_BIP.to_string();
	json["continueWord"].append(tmpJson);
}

string ContinueWord::toString_70B()
{
	return m_format.to_string() + m_signal.to_string() + m_message.to_string();
}

string ContinueWord::toString()
{
	return m_format.to_string() + m_signal.to_string() + m_message.to_string() + m_BIP.to_string();
}

bitset<5> ContinueWord::getBIP()
{
	return m_BIP;
}

void ContinueWord::setBIP(bitset<5> BIP)
{
	m_BIP = BIP;
}

bitset<63> ContinueWord::getMessage()
{
	return m_message;
}

string ContinueWord::getData()
{
	string message = getMessage().to_string();
	bitset<6> high = bitset<6>(message.substr(0, 6));
	if (high.all())
	{
		return message.substr(6);
	}
	else if (high.none())
	{
		return "";
	}
	else
	{
		int len = static_cast<int>(high.to_ulong());
		return message.substr(63 - len);
	}
}