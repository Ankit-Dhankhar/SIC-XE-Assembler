#include "OpTab.h"

map<string, OpInfo*>* opTable = NULL;

static void fillOpTab() {

	OpInfo* info;

	info = new OpInfo;
	info->mnmoneic = "FIX";
	info->format = FORMAT_1;
	info->opCode = 0xC4;
	opTable->insert(pair<string, OpInfo*>("FIX", info));

	info = new OpInfo;
	info->mnmoneic = "NORM";
	info->format = FORMAT_1;
	info->opCode = 0xC8;
	opTable->insert(pair<string, OpInfo*>("NORM", info));

	info = new OpInfo;
	info->mnmoneic = "TIO";
	info->format = FORMAT_1;
	info->opCode = 0xF8;
	opTable->insert(pair<string, OpInfo*>("TIO", info));

	info = new OpInfo;
	info->mnmoneic = "SIO";
	info->format = FORMAT_1;
	info->opCode = 0xF0;
	opTable->insert(pair<string, OpInfo*>("SIO", info));

	info = new OpInfo;
	info->mnmoneic = "FLOAT";
	info->format = FORMAT_1;
	info->opCode = 0xC0;
	opTable->insert(pair<string, OpInfo*>("FLOAT", info));

	info = new OpInfo;
	info->mnmoneic = "HIO";
	info->format = FORMAT_1;
	info->opCode = 0xF4;
	opTable->insert(pair<string, OpInfo*>("HIO", info));

	info = new OpInfo;
	info->mnmoneic = "ADDR";
	info->format = FORMAT_2;
	info->opCode = 0x90;
	opTable->insert(pair<string, OpInfo*>("ADDR", info));

	info = new OpInfo;
	info->mnmoneic = "CLEAR";
	info->format = FORMAT_2;
	info->opCode = 0xB4;
	opTable->insert(pair<string, OpInfo*>("CLEAR", info));

	info = new OpInfo;
	info->mnmoneic = "COMPR";
	info->format = FORMAT_2;
	info->opCode = 0xA0;
	opTable->insert(pair<string, OpInfo*>("COMPR", info));

	info = new OpInfo;
	info->mnmoneic = "DIVR";
	info->format = FORMAT_2;
	info->opCode = 0x9C;
	opTable->insert(pair<string, OpInfo*>("DIVR", info));

	info = new OpInfo;
	info->mnmoneic = "MULR";
	info->format = FORMAT_2;
	info->opCode = 0x98;
	opTable->insert(pair<string, OpInfo*>("MULR", info));

	info = new OpInfo;
	info->mnmoneic = "RMO";
	info->format = FORMAT_2;
	info->opCode = 0xAC;
	opTable->insert(pair<string, OpInfo*>("RMO", info));

	info = new OpInfo;
	info->mnmoneic = "SHIFTL";
	info->format = FORMAT_2;
	info->opCode = 0xA4;
	opTable->insert(pair<string, OpInfo*>("SHIFTL", info));

	info = new OpInfo;
	info->mnmoneic = "SHIFTR";
	info->format = FORMAT_2;
	info->opCode = 0xA8;
	opTable->insert(pair<string, OpInfo*>("SHIFTR", info));

	info = new OpInfo;
	info->mnmoneic = "SUBR";
	info->format = FORMAT_2;
	info->opCode = 0x94;
	opTable->insert(pair<string, OpInfo*>("SUBR", info));

	info = new OpInfo;
	info->mnmoneic = "SVC";
	info->format = FORMAT_2;
	info->opCode = 0xB0;
	opTable->insert(pair<string, OpInfo*>("SVC", info));

	info = new OpInfo;
	info->mnmoneic = "TIXR";
	info->format = FORMAT_2;
	info->opCode = 0xB8;
	opTable->insert(pair<string, OpInfo*>("TIXR", info));

	info = new OpInfo;
	info->mnmoneic = "ADD";
	info->format = FORMAT_3_4;
	info->opCode = 0x18;
	opTable->insert(pair<string, OpInfo*>("ADD", info));

	info = new OpInfo;
	info->mnmoneic = "ADDF";
	info->format = FORMAT_3_4;
	info->opCode = 0x58;
	opTable->insert(pair<string, OpInfo*>("ADDF", info));

	info = new OpInfo;
	info->mnmoneic = "AND";
	info->format = FORMAT_3_4;
	info->opCode = 0x40;
	opTable->insert(pair<string, OpInfo*>("AND", info));

	info = new OpInfo;
	info->mnmoneic = "COMP";
	info->format = FORMAT_3_4;
	info->opCode = 0x28;
	opTable->insert(pair<string, OpInfo*>("COMP", info));

	info = new OpInfo;
	info->mnmoneic = "COMPF";
	info->format = FORMAT_3_4;
	info->opCode = 0x88;
	opTable->insert(pair<string, OpInfo*>("COMPF", info));

	info = new OpInfo;
	info->mnmoneic = "DIV";
	info->format = FORMAT_3_4;
	info->opCode = 0x24;
	opTable->insert(pair<string, OpInfo*>("DIV", info));

	info = new OpInfo;
	info->mnmoneic = "DIVF";
	info->format = FORMAT_3_4;
	info->opCode = 0x64;
	opTable->insert(pair<string, OpInfo*>("DIVF", info));

	info = new OpInfo;
	info->mnmoneic = "OR";
	info->format = FORMAT_3_4;
	info->opCode = 0x44;
	opTable->insert(pair<string, OpInfo*>("OR", info));

	info = new OpInfo;
	info->mnmoneic = "RD";
	info->format = FORMAT_3_4;
	info->opCode = 0xD8;
	opTable->insert(pair<string, OpInfo*>("RD", info));

	info = new OpInfo;
	info->mnmoneic = "RSUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x4C;
	opTable->insert(pair<string, OpInfo*>("RSUB", info));

	info = new OpInfo;
	info->mnmoneic = "SSK";
	info->format = FORMAT_3_4;
	info->opCode = 0xEC;
	opTable->insert(pair<string, OpInfo*>("SSK", info));

	info = new OpInfo;
	info->mnmoneic = "STA";
	info->format = FORMAT_3_4;
	info->opCode = 0x0C;
	opTable->insert(pair<string, OpInfo*>("STA", info));

	info = new OpInfo;
	info->mnmoneic = "STB";
	info->format = FORMAT_3_4;
	info->opCode = 0x78;
	opTable->insert(pair<string, OpInfo*>("STB", info));

	info = new OpInfo;
	info->mnmoneic = "STCH";
	info->format = FORMAT_3_4;
	info->opCode = 0x54;
	opTable->insert(pair<string, OpInfo*>("STCH", info));

	info = new OpInfo;
	info->mnmoneic = "STF";
	info->format = FORMAT_3_4;
	info->opCode = 0x80;
	opTable->insert(pair<string, OpInfo*>("STF", info));

	info = new OpInfo;
	info->mnmoneic = "STI";
	info->format = FORMAT_3_4;
	info->opCode = 0xD4;
	opTable->insert(pair<string, OpInfo*>("STI", info));

	info = new OpInfo;
	info->mnmoneic = "STL";
	info->format = FORMAT_3_4;
	info->opCode = 0x14;
	opTable->insert(pair<string, OpInfo*>("STL", info));

	info = new OpInfo;
	info->mnmoneic = "STS";
	info->format = FORMAT_3_4;
	info->opCode = 0x7C;
	opTable->insert(pair<string, OpInfo*>("STS", info));

	info = new OpInfo;
	info->mnmoneic = "STSW";
	info->format = FORMAT_3_4;
	info->opCode = 0xE8;
	opTable->insert(pair<string, OpInfo*>("STSW", info));

	info = new OpInfo;
	info->mnmoneic = "STT";
	info->format = FORMAT_3_4;
	info->opCode = 0x84;
	opTable->insert(pair<string, OpInfo*>("STT", info));

	info = new OpInfo;
	info->mnmoneic = "STX";
	info->format = FORMAT_3_4;
	info->opCode = 0x10;
	opTable->insert(pair<string, OpInfo*>("STX", info));

	info = new OpInfo;
	info->mnmoneic = "SUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x1C;
	opTable->insert(pair<string, OpInfo*>("SUB", info));

	info = new OpInfo;
	info->mnmoneic = "SUBF";
	info->format = FORMAT_3_4;
	info->opCode = 0x5C;
	opTable->insert(pair<string, OpInfo*>("SUBF", info));

	info = new OpInfo;
	info->mnmoneic = "TD";
	info->format = FORMAT_3_4;
	info->opCode = 0xE0;
	opTable->insert(pair<string, OpInfo*>("TD", info));

	info = new OpInfo;
	info->mnmoneic = "TIX";
	info->format = FORMAT_3_4;
	info->opCode = 0x2C;
	opTable->insert(pair<string, OpInfo*>("TIX", info));

	info = new OpInfo;
	info->mnmoneic = "WD";
	info->format = FORMAT_3_4;
	info->opCode = 0xDC;
	opTable->insert(pair<string, OpInfo*>("WD", info));

	info = new OpInfo;
	info->mnmoneic = "J";
	info->format = FORMAT_3_4;
	info->opCode = 0x3C;
	opTable->insert(pair<string, OpInfo*>("J", info));

	info = new OpInfo;
	info->mnmoneic = "JEQ";
	info->format = FORMAT_3_4;
	info->opCode = 0x30;
	opTable->insert(pair<string, OpInfo*>("JEQ", info));

	info = new OpInfo;
	info->mnmoneic = "JGT";
	info->format = FORMAT_3_4;
	info->opCode = 0x34;
	opTable->insert(pair<string, OpInfo*>("JGT", info));

	info = new OpInfo;
	info->mnmoneic = "JLT";
	info->format = FORMAT_3_4;
	info->opCode = 0x38;
	opTable->insert(pair<string, OpInfo*>("JLT", info));

	info = new OpInfo;
	info->mnmoneic = "JSUB";
	info->format = FORMAT_3_4;
	info->opCode = 0x48;
	opTable->insert(pair<string, OpInfo*>("JSUB", info));

	info = new OpInfo;
	info->mnmoneic = "LDA";
	info->format = FORMAT_3_4;
	info->opCode = 0x00;
	opTable->insert(pair<string, OpInfo*>("LDA", info));

	info = new OpInfo;
	info->mnmoneic = "LDB";
	info->format = FORMAT_3_4;
	info->opCode = 0x68;
	opTable->insert(pair<string, OpInfo*>("LDB", info));

	info = new OpInfo;
	info->mnmoneic = "LDCH";
	info->format = FORMAT_3_4;
	info->opCode = 0x50;
	opTable->insert(pair<string, OpInfo*>("LDCH", info));

	info = new OpInfo;
	info->mnmoneic = "LDF";
	info->format = FORMAT_3_4;
	info->opCode = 0x70;
	opTable->insert(pair<string, OpInfo*>("LDF", info));

	info = new OpInfo;
	info->mnmoneic = "LDL";
	info->format = FORMAT_3_4;
	info->opCode = 0x08;
	opTable->insert(pair<string, OpInfo*>("LDL", info));

	info = new OpInfo;
	info->mnmoneic = "LDS";
	info->format = FORMAT_3_4;
	info->opCode = 0x6C;
	opTable->insert(pair<string, OpInfo*>("LDS", info));

	info = new OpInfo;
	info->mnmoneic = "LDT";
	info->format = FORMAT_3_4;
	info->opCode = 0x74;
	opTable->insert(pair<string, OpInfo*>("LDT", info));

	info = new OpInfo;
	info->mnmoneic = "LDX";
	info->format = FORMAT_3_4;
	info->opCode = 0x04;
	opTable->insert(pair<string, OpInfo*>("LDX", info));

	info = new OpInfo;
	info->mnmoneic = "LPS";
	info->format = FORMAT_3_4;
	info->opCode = 0xD0;
	opTable->insert(pair<string, OpInfo*>("LPS", info));

	info = new OpInfo;
	info->mnmoneic = "MUL";
	info->format = FORMAT_3_4;
	info->opCode = 0x20;
	opTable->insert(pair<string, OpInfo*>("MUL", info));

	info = new OpInfo;
	info->mnmoneic = "MULF";
	info->format = FORMAT_3_4;
	info->opCode = 0x60;
	opTable->insert(pair<string, OpInfo*>("MULF", info));

	info = NULL;
}

map<string, OpInfo*>* getOpTab() {
	if (opTable == NULL) {
		opTable = new map<string, OpInfo*>();
		fillOpTab();
	}
	return opTable;
}

void deleteOpTab() {
	for (map<string, OpInfo*>::iterator it = opTable->begin();
			it != opTable->end(); ++it) {
		OpInfo* ptr = it->second;
		opTable->erase(it->first);
		delete ptr;
	}
	delete opTable;
}
