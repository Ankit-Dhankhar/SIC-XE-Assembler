#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <bitset>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct OpInfo {
	string mnmoneic;
	unsigned char format;
	unsigned char opCode;
};

struct parsedLine {
	string lable;
	string opcode;
	string operand1;
	string operand2;
	string err;
};

struct opCode {
	unsigned char operation;

	int displacement;

	bitset<6> flags; //  n i x b p e -> 1 1 0 0 0 0
	unsigned char format; // 1, 2, 3 or 4

	unsigned char reg1;
	unsigned char reg2;
};

struct symInfo {
	int address;
	bool relocatble;
};

struct toWrite {
	string data;
	int type;
	/*
	 * -1 for errors
	 *  0 for comments
	 *  1 for formatted lines
	 *  */
};

struct modification {
	int address;
	int hbytes;

	bool exRef;
	vector<char> signs;
	vector<string> refs;
};
struct locatedParsedLine{
	parsedLine p;
	int loc;
};
//+ --> modification record.
struct cSect {
	string name;
	int locCtr;
	vector<string> extRef;
	vector<string> extDef;
	map<string, int> litTab;
	vector<toWrite> dataSect;
	vector<locatedParsedLine> locpl;
	vector<modification> mods;
	map<string, symInfo*> symTab;
};

#endif
