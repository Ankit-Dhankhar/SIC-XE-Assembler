#ifndef IO_H_
#define IO_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <map>
#include "StringUtilities.h"
#include "structs.h"
#include "OpCodeGenerator.h"

using namespace std;

#define FILE_LINE_LENGTH 63;
#define PASS_2_LENGTH 89;
#define LINE_NUMBER_LENGTH 16;
#define ADDRESS_LENGTH 15;
#define LABEL_LENGTH 9;
#define MNEMONIC_LENGTH 8;
#define OPERANDS_LENGTH 16;
#define FLAGS_LENGTH 15;
#define OPCODE_LENGTH 10;
#define SPACE_CHAR 0x20;
#define ZERO_CHAR 0x30
#define ASTERISK_CHAR 0x2A;
#define DASH_CHAR 0x2D;
#define NEW_LINE_CHAR 0x0A;
#define EQUAL_CHAR 0x3D;
#define TAB_CHAR 0x09;

string constructLine(int lineNumber, string label, string op, string operands);

string constructLine_Pass2(int address, string label, string op_str,
		string operands, bitset<6> flags, string opCode);

void deleteFile(string name);

void writeLine(ofstream* file, string line);

string readLine(ifstream* file);

void writeHeader(ofstream* file);

void writeHeader_Pass2(ofstream* file);

void writeError(ofstream* file, string error);

void writeBorder(ofstream* file);

void writeBorder_Pass2(ofstream* file);

void writeSymTab(ofstream* file, map<string, symInfo*>* theMap);

void writeComment(ofstream* file, string comment);

void writeHeaderRecord(ofstream* file, string prog_name, int starting_add, int prog_length);

void writeTextRecords(ofstream* file, vector<string>* opCodes, vector<locatedParsedLine>* lpl);

void writeModRecords(ofstream* file, vector<modification>* mods);

void writeDefineRecord(ofstream* file, vector<string>* exdefs, map<string, symInfo*>* theMap);

void writeReferRecord(ofstream* file, vector<string>* exrefs);

void writeEndRecord();

#endif
