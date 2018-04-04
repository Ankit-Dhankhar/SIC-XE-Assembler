#include "StringUtilities.h"

string intToString(int integer, bool hex) {
	stringstream ss;
	string intAsStr = "";
	if (hex)
		ss << uppercase << std::hex << integer;
	else
		ss << integer;
	intAsStr = ss.str();
	return intAsStr;
}

void adjustStringLength(string* line, int length, char filling, bool lhs) {
	if (lhs)
		for (int i = line->length(); i < length; i++)
			*line = filling + *line;
	else
		for (int i = line->length(); i < length; i++)
			*line += filling;
}

string toUpperCase(string x) {
	unsigned int i;
	string toRet = "";
	for (i = 0; i < x.length(); i++) {
		char pos = x.at(i);
		if (pos <= 122 && pos >= 97) {
			pos -= 32;
		}
		toRet += pos;
	}
	return toRet;
}

/*
 * Trims the leading and forwarding spaces.
 */
string trim(string x) {

	if (x.compare("") == 0)
		return x;

	unsigned int i;
	for (i = 0; i < x.length() && x.at(i) == ' '; i++)
		;

	if (i == x.length())
		return "";

	unsigned int j;
	for (j = x.length() - 1; j >= 0 && x.at(j) == ' '; j--)
		;

	string toRet = "";
	unsigned int k;
	for (k = i; k <= j; k++)
		toRet += x.at(k);

	return toRet;
}

/*
 * Parses a decimal integer from a string.
 */
int parseDecimal(string x) {
	char first = x.at(0);
	unsigned int i = first == '-' || first == '+' ? 1 : 0;

	int result = 0;
	for (; i < x.length(); i++) {
		result *= 10;
		result += (x.at(i) - 48);
	}
	return first == '-' ? -result : result;
}

/*
 * Parses a hexadecimal integer from a string.
 */

int parseHexaDecimal(string x) {
	char first = x.at(0);
	unsigned int i = first == '-' || first == '+' ? 1 : 0;

	int result = 0;
	for (; i < x.length(); i++) {
		result *= 16;

		if (x.at(i) >= 48 && x.at(i) <= 57)
			result += (x.at(i) - 48);
		else
			result += (x.at(i) - 55);
	}
	return first == '-' ? -result : result;
}

/*
 * Parses a float from a string.
 */
float parseFloat(string x) {
	float resFrac = 0.0, resInt = 0.0;
	unsigned int i;

	unsigned int dotPos = x.find(".");

	if (dotPos != x.npos) {
		for (i = dotPos + 1; i < x.length(); i++) {
			resFrac += (x.at(i) - 48);
			resFrac *= 0.1;
		}
	}

	char first = x.at(0);
	i = first == '-' || first == '+' ? 1 : 0;

	for (; i <= dotPos - 1; i++) {
		resInt *= 10;
		resInt += (x.at(i) - 48);
	}
	float res = resFrac;
	res += resInt;

	return first == '-' ? -res : res;
}

/*
 * Splits the given string using the character s as a delimiter.
 */
vector<string> split(string x, char s) {
	vector<string> toRet;
	string temp = "";
	for (unsigned int i = 0; i < x.length(); i++) {
		if (x.at(i) == s) {
			if (temp.length() == 0)
				continue;

			toRet.push_back(temp);
			temp = "";
			continue;
		}
		(temp) += x.at(i);
	}
	if (temp.length() != 0)
		toRet.push_back(temp);

	return toRet;
}

string mergeStrings(string x, string y, char del) {
	x = trim(x);
	y = trim(y);

	if (y.compare("") != 0) {
		return x.append("" + del).append(y);
	}
	return x;
}

bool isNumeric(string s) {
	if (s.length() == 0)
		return false;
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s.at(i) - '0' < 0 || s.at(i) - '0' > 9)
			return false;
	}
	return true;
}

bool isHexa(string s) {
	if (s.length() == 0)
		return false;
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s.at(i) != 'A' && s.at(i) != 'B' && s.at(i) != 'C' && s.at(i) != 'D'
				&& s.at(i) != 'E' && s.at(i) != 'F'
				&& (s.at(i) - '0' < 0 || s.at(i) - '0' > 9))
			return false;
	}
	return true;
}

vector<string> generalSplit(string toSplit, string splitters) {
	vector<string> toRet;
	string temp = "";
	for (unsigned int i = 0; i < toSplit.length(); i++) {
		if (splitters.find(toSplit.at(i)) != string::npos) {
			if (temp.length() == 0)
				continue;

			toRet.push_back(temp);
			temp = "";
			continue;
		}
		(temp) += toSplit.at(i);
	}
	if (temp.length() != 0)
		toRet.push_back(temp);

	return toRet;
}
