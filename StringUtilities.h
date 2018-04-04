#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <iostream>
#include <vector>
#include "sstream"

using namespace std;

string intToString(int integer, bool hex);

void adjustStringLength(string* line, int length, char filling, bool lhs);

string toUpperCase(string x);

string trim(string x);

bool isNumeric(string s);

bool isHexa(string s);

int parseDecimal(string x);

int parseHexaDecimal(string x);

float parseFloat(string x);

vector<string> split(string x, char s);

string mergeStrings(string x, string y, char del);

vector<string> generalSplit(string toSplit, string splitters);

#endif
