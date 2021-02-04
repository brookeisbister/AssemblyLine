// Name:				Brooke Isbister
// Seneca Student ID:	166344184
// Seneca email:		bisbister@myseneca.ca
// Date of completion:	November 6, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utilities.h"

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }
size_t Utilities::getFieldWidth() const { return m_widthField; }
void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }
char Utilities::getDelimiter() { return m_delimiter; }

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token;
	if (next_pos <= str.length()) {
		size_t end_pos = str.find(getDelimiter(), next_pos);
		if (end_pos != std::string::npos) {
			token = str.substr(next_pos, end_pos - next_pos);
			next_pos = end_pos + 1;
		}
		else {
			token = str.substr(next_pos);
			next_pos = str.length() + 1;
		}
		if (token.empty() && (next_pos != str.length() + 1)) {
	more = false;
	throw str + "-- Error: Token Failure";
		}
		if (getFieldWidth() < token.length())
			setFieldWidth(token.length());
		more = next_pos <= str.length();
	}
		return token;
	}