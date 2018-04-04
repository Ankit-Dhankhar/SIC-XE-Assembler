#include "IO.h"

int main2() {

	deleteFile("test.txt");
	map<string, symInfo*>* myMap = new map<string, symInfo*> ();
	vector<string>* exdefs = new vector<string>();
	vector<string>* exrefs = new vector<string>();
	vector<modification>* mods = new vector<modification>();
	vector<string>* opCodes = new vector<string>();
	vector<locatedParsedLine>* lpl = new vector<locatedParsedLine>();

	opCodes->push_back("000000");
	opCodes->push_back("000001");
	opCodes->push_back("000002");
	opCodes->push_back("000003");
	opCodes->push_back("000004");
	opCodes->push_back("000005");
	opCodes->push_back("000006");
	opCodes->push_back("000007");
	opCodes->push_back("000ABC"); // literals
	opCodes->push_back("000DEF"); // literals
	opCodes->push_back("000A67"); // literals
	opCodes->push_back("000728"); // literals
	opCodes->push_back("020000"); // literals
	opCodes->push_back("000008");
	opCodes->push_back("");
	opCodes->push_back("");
	opCodes->push_back("");
	opCodes->push_back("");

	locatedParsedLine _10;
	_10.loc = 10;
	_10.p.opcode = "A";
	_10.p.operand1 = "RRR";

	locatedParsedLine _20;

	_20.loc = 20;
	_20.p.opcode = "A";
	_20.p.operand1 = "RRR";

	locatedParsedLine _30;

	_30.loc = 30;
	_30.p.opcode = "A";
	_30.p.operand1 = "RRR";

	locatedParsedLine _40;

	_40.loc = 40;
	_40.p.opcode = "A";
	_40.p.operand1 = "RRR";

	locatedParsedLine _50;

	_50.loc = 50;
	_50.p.opcode = "A";
	_50.p.operand1 = "RRR";

	locatedParsedLine _60;

	_60.loc = 60;
	_60.p.opcode = "A";
	_60.p.operand1 = "RRR";

	locatedParsedLine _70;

	_70.loc = 70;
	_70.p.opcode = "A";
	_70.p.operand1 = "RRR";

	locatedParsedLine _120;

	_120.loc = 120;
	_120.p.opcode = "A";
	_120.p.operand1 = "RRR";

	locatedParsedLine _80;

	_80.loc = 130;
	_80.p.lable = "*";

	locatedParsedLine _90;

	_90.p.lable = "*";

	locatedParsedLine _100;

	_100.p.lable = "*";

	locatedParsedLine _110;

	_110.p.lable = "*";

	locatedParsedLine _130;

	_130.loc = 130;
	_130.p.lable = "*";

	locatedParsedLine _140;

	_140.loc = 140;
	_140.p.opcode = "A";
	_140.p.operand1 = "RRR";

	locatedParsedLine _150;

	_150.loc = 150;
	_150.p.opcode = "";

	locatedParsedLine _160;

	_160.loc = 160;
	_160.p.opcode = "";

	locatedParsedLine _170;

	_170.loc = 170;
	_170.p.opcode = "";

	locatedParsedLine _180;

	_180.loc = 180;
	_180.p.opcode = "";

	lpl->push_back(_10);
	lpl->push_back(_20);
	lpl->push_back(_30);
	lpl->push_back(_40);
	lpl->push_back(_50);
	lpl->push_back(_60);
	lpl->push_back(_70);
	lpl->push_back(_120);
	lpl->push_back(_80);
	lpl->push_back(_90);
	lpl->push_back(_100);
	lpl->push_back(_110);
	lpl->push_back(_130);
	lpl->push_back(_140);
	lpl->push_back(_150);
	lpl->push_back(_160);
	lpl->push_back(_170);
	lpl->push_back(_180);

	modification _1;
	_1.address = 50;
	_1.exRef = false;
	_1.hbytes = 5;

	mods->push_back(_1);

	modification _2;
	_2.address = 70;
	_2.exRef = true;
	_2.hbytes = 5;
	_2.signs.push_back('+');
	_2.signs.push_back('-');
	_2.refs.push_back("one");
	_2.refs.push_back("two");

	mods->push_back(_2);

	exdefs->push_back("first");
	exdefs->push_back("second");
	exdefs->push_back("third");
	exdefs->push_back("forth");
	exdefs->push_back("fifth");
	exdefs->push_back("sixth");
	exdefs->push_back("seventh");
	exdefs->push_back("eighth");
	exdefs->push_back("ninth");

	exrefs->push_back("BUFFER1");
	exrefs->push_back("BUFEND2");
	exrefs->push_back("BUFFER3");
	exrefs->push_back("BUFEND4");
	exrefs->push_back("BUFFER5");
	exrefs->push_back("BUFEND6");
	exrefs->push_back("BUFFER7");
	exrefs->push_back("BUFEND8");
	exrefs->push_back("BUFEND9");

	symInfo first;
	first.address = 10;
	first.relocatble = true;
	symInfo second;
	second.address = 20;
	second.relocatble = true;
	symInfo third;
	third.address = 30;
	third.relocatble = false;
	symInfo forth;
	forth.address = 40;
	forth.relocatble = false;
	symInfo fifth;
	fifth.address = 50;
	fifth.relocatble = false;
	symInfo sixth;
	sixth.address = 60;
	sixth.relocatble = false;
	symInfo seventh;
	seventh.address = 70;
	seventh.relocatble = true;
	symInfo eighth;
	eighth.address = 80;
	eighth.relocatble = true;
	symInfo ninth;
	ninth.address = 90;
	ninth.relocatble = true;

	myMap->insert(pair<string, symInfo*> ("first", &first));
	myMap->insert(pair<string, symInfo*> ("second", &second));
	myMap->insert(pair<string, symInfo*> ("third", &third));
	myMap->insert(pair<string, symInfo*> ("forth", &forth));
	myMap->insert(pair<string, symInfo*> ("fifth", &fifth));
	myMap->insert(pair<string, symInfo*> ("sixth", &sixth));
	myMap->insert(pair<string, symInfo*> ("seventh", &seventh));
	myMap->insert(pair<string, symInfo*> ("eighth", &eighth));
	myMap->insert(pair<string, symInfo*> ("ninth", &ninth));

	for (map<string, symInfo*>::iterator it = myMap->begin(); it
			!= myMap->end(); ++it) {
		cout << it->first << "\t" << (it->second)->address << "\t"
				<< (it->second)->relocatble << "\n";

	}

	ofstream ofile;
	ofile.open("test.txt", std::ios::app);
	writeHeader(&ofile);
	writeComment(&ofile, ".2345678901234567890");
	writeLine(&ofile, constructLine(11, "ALPHA", "LDA", "#10"));
	writeLine(&ofile, constructLine(100, "THETA", "TIXR", "T"));
	writeLine(&ofile, constructLine(1500, "A", "RMO", "T,X"));
	writeComment(&ofile, ".This is a comment line");
	writeLine(&ofile, constructLine(11, "", "+LDA", "#10"));
	writeLine(&ofile, constructLine(25, "BETA", "LDX", "TEN"));
	writeLine(&ofile, constructLine(17, "", "LDT", "FIVE"));
	writeError(&ofile, "this is an error\nthis is another error");
	writeBorder(&ofile);
	writeSymTab(&ofile, myMap);
	writeBorder_Pass2(&ofile);
	writeHeader_Pass2(&ofile);

	opCode op;
	op.format = 4;
	op.operation = 0x74;
	op.flags = 0b010001;
	op.displacement = 0x1000;
	writeLine(&ofile, constructLine_Pass2(400, "B", "+LDT", "#MAXLENGTH", op.flags, calcOpCode(op)));

	writeError(&ofile, "this is an error");

	op.format = 33;
	op.flags = 0b000000;
	writeLine(&ofile, constructLine_Pass2(400, "", "RESW", "1024", op.flags, calcOpCode(op)));

	ofile.close();

	deleteFile("_test.txt");

	ofile.open("_test.txt", std::ios::app);

	// object file goes here
	writeHeaderRecord(&ofile, "COPY", 0, 77);
	writeDefineRecord(&ofile, exdefs, myMap);
	writeReferRecord(&ofile, exrefs);
	writeModRecords(&ofile, mods);
	writeTextRecords(&ofile, opCodes, lpl);

	ofile.close();

	ifstream file;
	file.open("test.txt");

	string line;
	line = readLine(&file);
	cout << line << endl;

	line = readLine(&file);
	cout << line << endl;

	line = readLine(&file);
	cout << line << endl;

	int i = '=';
	cout << hex << i;

	return 0;
}

int counter = 0;

string constructLine(int address, string label, string op, string operands) {
	int length;
	char spaceChar = SPACE_CHAR;
	char zeroChar = ZERO_CHAR;
	string line;
	string lineNumberStr = intToString(++counter, false);
	length = LINE_NUMBER_LENGTH;
	string addressStr = intToString(address, true);
	adjustStringLength(&lineNumberStr, length, spaceChar, false);
	length = 6;
	adjustStringLength(&addressStr, length, zeroChar, true);
	length = ADDRESS_LENGTH;
	adjustStringLength(&addressStr, length, spaceChar, false);
	length = LABEL_LENGTH;
	if (op.at(0) == '+')
		length -= 1;
	adjustStringLength(&label, length, spaceChar, false);
	length = MNEMONIC_LENGTH;
	if (op.at(0) == '+')
		length += 1;
	adjustStringLength(&op, length, spaceChar, false);
	length = OPERANDS_LENGTH;
	adjustStringLength(&operands, length, spaceChar, false);
	line = lineNumberStr + addressStr + label + op + operands;
	return line;
}

string constructLine_Pass2(int address, string label, string op_str,
		string operands, bitset<6> flags, string opCode) {
	int length;
	char spaceChar = SPACE_CHAR;
	char zeroChar = ZERO_CHAR;
	string line;
	string lineNumberStr = intToString(++counter, false);
	length = LINE_NUMBER_LENGTH;
	string addressStr = intToString(address, true);
	adjustStringLength(&lineNumberStr, length, spaceChar, false);
	length = 6;
	adjustStringLength(&addressStr, length, zeroChar, true);
	length = ADDRESS_LENGTH;
	adjustStringLength(&addressStr, length, spaceChar, false);
	length = LABEL_LENGTH;
	if (op_str.at(0) == '+')
		length -= 1;
	adjustStringLength(&label, length, spaceChar, false);
	length = MNEMONIC_LENGTH;
	if (op_str.at(0) == '+')
		length += 1;
	adjustStringLength(&op_str, length, spaceChar, false);
	length = OPERANDS_LENGTH;
	adjustStringLength(&operands, length, spaceChar, false);
	string flags_str = flags.to_string(), mod_flags_str = "";
	if (flags_str.compare("000000") != 0) {
		for (int i = 0; (unsigned) i < flags_str.size(); i++) {
			mod_flags_str += flags_str[i];
			if ((unsigned) i + 1 < flags_str.size())
				mod_flags_str += " ";
		}
	}
	length = FLAGS_LENGTH;
	adjustStringLength(&mod_flags_str, length, spaceChar, false);
	length = OPCODE_LENGTH;
	adjustStringLength(&opCode, length, spaceChar, false);
	line = lineNumberStr + addressStr + label + op_str + operands
			+ mod_flags_str + opCode;
	return line;
}

void deleteFile(string name) {
	remove(name.c_str());

}

void writeLine(ofstream* file, string line) {
	*file << line << endl;
}

string readLine(ifstream* file) {
	string line = "";
	getline(*file, line);
	return line;
}

void writeHeader(ofstream* file) {

	int fileLineLength = FILE_LINE_LENGTH;
	int lineNumberLength = LINE_NUMBER_LENGTH;
	int addressLength = ADDRESS_LENGTH;
	int labelLength = LABEL_LENGTH;
	int mnemonicLength = MNEMONIC_LENGTH;
	int operandsLength = OPERANDS_LENGTH;
	char spaceChar = SPACE_CHAR;
	char equalChar = EQUAL_CHAR;
	string line = "";
	line = "\t Pass\t1 ... \n";
	writeLine(file, line);
	line = "";
	string temp = "line number";
	adjustStringLength(&temp, lineNumberLength, spaceChar, false);
	line += temp;
	temp = "address";
	adjustStringLength(&temp, addressLength, spaceChar, false);
	line += temp;
	temp = "label";
	adjustStringLength(&temp, labelLength, spaceChar, false);
	line += temp;
	temp = "op";
	adjustStringLength(&temp, mnemonicLength, spaceChar, false);
	line += temp;
	temp = "operands";
	adjustStringLength(&temp, operandsLength, spaceChar, false);
	line += temp;
	writeLine(file, line);
	line = "";
	adjustStringLength(&line, fileLineLength, equalChar, false);
	writeLine(file, line);

}

void writeHeader_Pass2(ofstream* file) {
	int pass2Length = PASS_2_LENGTH;
	int lineNumberLength = LINE_NUMBER_LENGTH;
	int addressLength = ADDRESS_LENGTH;
	int labelLength = LABEL_LENGTH;
	int mnemonicLength = MNEMONIC_LENGTH;
	int operandsLength = OPERANDS_LENGTH;
	int flagsLength = FLAGS_LENGTH;
	int opCodeLength = OPCODE_LENGTH;
	char spaceChar = SPACE_CHAR;
	char equalChar = EQUAL_CHAR;
	string line = "";
	line = "\t Pass\t2 ... \n";
	writeLine(file, line);
	line = "";
	string temp = "line number";
	adjustStringLength(&temp, lineNumberLength, spaceChar, false);
	line += temp;
	temp = "address";
	adjustStringLength(&temp, addressLength, spaceChar, false);
	line += temp;
	temp = "label";
	adjustStringLength(&temp, labelLength, spaceChar, false);
	line += temp;
	temp = "op";
	adjustStringLength(&temp, mnemonicLength, spaceChar, false);
	line += temp;
	temp = "operands";
	adjustStringLength(&temp, operandsLength, spaceChar, false);
	line += temp;
	temp = "n i x b p e";
	adjustStringLength(&temp, flagsLength, spaceChar, false);
	line += temp;
	temp = "opcode";
	adjustStringLength(&temp, opCodeLength, spaceChar, false);
	line += temp;
	writeLine(file, line);
	line = "";
	adjustStringLength(&line, pass2Length, equalChar, false);
	writeLine(file, line);

}

void writeError(ofstream* file, string error) {
	vector<string> vecOfStrs = split(error, '\n');

	for (unsigned int i = 0; i < vecOfStrs.size(); i++) {
		error = vecOfStrs.at(i);
		int errLength = error.length();
		int offset = 19;
		int excess;
		char spaceChar = SPACE_CHAR;
		char asterisk = ASTERISK_CHAR;

		adjustStringLength(&error, errLength + 3, asterisk, true);
		adjustStringLength(&error, errLength + offset, spaceChar, true);
		excess = 63 - errLength;

		adjustStringLength(&error, errLength + excess, spaceChar, false);

		writeLine(file, error);

	}
}

void writeBorder(ofstream* file) {
	char newLine = NEW_LINE_CHAR;
	int fileLineLength = FILE_LINE_LENGTH;
	string line = "";
	char asterickChar = ASTERISK_CHAR;
	for (int i = 0; i < fileLineLength; i++)
		line += asterickChar;
	writeLine(file, newLine + line + newLine);
}

void writeBorder_Pass2(ofstream* file) {
	char newLine = NEW_LINE_CHAR;
	int fileLineLength = PASS_2_LENGTH;
	string line = "";
	char asterickChar = ASTERISK_CHAR;
	for (int i = 0; i < fileLineLength; i++)
		line += asterickChar;
	writeLine(file, newLine + line + newLine);
}

void writeSymTab(ofstream* file, map<string, symInfo*>* theMap) {

	if (theMap->empty())
		return;
	char spaceChar = SPACE_CHAR;
	char dashChar = DASH_CHAR;
	char equalChar = EQUAL_CHAR;
	char zeroChar = ZERO_CHAR;

	string temp, headerLine = "";
	writeLine(file, "\t Symbol\t\t Table\t\t (values in hex)\n");
	temp = "";
	adjustStringLength(&temp, 33, equalChar, false);
	writeLine(file, temp);
	temp = "|\tname";
	adjustStringLength(&temp, 11, spaceChar, false);
	headerLine += temp;
//	writeLine(file, temp);
	temp = "address";
	adjustStringLength(&temp, 10, spaceChar, false);
	headerLine += temp;
	temp = "Abs/Rel";
	temp += "\t|";
	headerLine += temp;
	writeLine(file, headerLine);
	temp = "|\t";
	adjustStringLength(&temp, 28, dashChar, false);
	temp += "\t|";
	writeLine(file, temp);
	for (map<string, symInfo*>::const_iterator it = theMap->begin(); it
			!= theMap->end(); it++) {
		string symbol = "|\t" + it->first;
		symInfo* n = it->second;
		string address = intToString(n->address, true);
		string rel = "";
		if (n->relocatble)
			rel = "Rel";
		else
			rel = "Abs";
		adjustStringLength(&symbol, 11, spaceChar, false);
		string line = symbol;
		adjustStringLength(&address, 4, zeroChar, true);
		adjustStringLength(&address, 5, spaceChar, true);
		adjustStringLength(&address, 10, spaceChar, false);
		line += address;
		adjustStringLength(&address, 10, spaceChar, true);
		adjustStringLength(&rel, 7, spaceChar, true);
		rel += "\t|";
		line += rel;
		writeLine(file, line);
	}
	temp = "";
	adjustStringLength(&temp, 33, equalChar, false);
	writeLine(file, temp);
}

void writeComment(ofstream* file, string comment) {
	int lineNumberLength = LINE_NUMBER_LENGTH;
	int addressLength = ADDRESS_LENGTH;
	char spaceChar = SPACE_CHAR;
	adjustStringLength(&comment,
			comment.size() + lineNumberLength + addressLength, spaceChar, true);
	writeLine(file, comment);
}

void writeHeaderRecord(ofstream* file, string prog_name, int starting_add, int prog_length) { // 1
	char spaceChar = SPACE_CHAR;
	char zeroChar = ZERO_CHAR;

	string line = "\t Header Record :\t\t\n";
	writeLine(file, line);
	line = "H^";
	adjustStringLength(&line, 11, spaceChar, true);
	if (prog_name.compare("") == 0) adjustStringLength(&prog_name, 6, spaceChar, true);
	line += prog_name;
	line += "^";
	string starting_add_str = intToString(starting_add, true);
	adjustStringLength(&starting_add_str, 6, zeroChar, true);
	line += starting_add_str;
	line += "^";
	string prog_length_str = intToString(prog_length, true);
	adjustStringLength(&prog_length_str, 6, zeroChar, true);
	line += prog_length_str;
	writeLine(file, line);
	line = "";
	adjustStringLength(&line, 11, spaceChar, true);
	line += "Program Name: ";
	if (prog_name.compare("") == 0) line += "Unknown.";
	else line += prog_name;
	writeLine(file, line);
	line = "";
	adjustStringLength(&line, 11, spaceChar, true);
	line += "Loading Address: ";
	line += starting_add_str;
	line += "\n";
	writeLine(file, line);

}

void writeTextRecords(ofstream* file, vector<string>* opCodes, vector<locatedParsedLine>* lpl) { // 4
	char zeroChar = ZERO_CHAR;
	char spaceChar = SPACE_CHAR;
	int start_address = 0;
	int end_address = 0;
	string start_address_str;
	string length_str;

	string line = "\tText Record(s) :\t\t\n";
	string temp_line = "";
	writeLine(file, line);

	for (unsigned int i = 0; i< opCodes->size();){
		if ((*opCodes)[i].compare("") == 0 || (*lpl)[i].p.lable.compare("*") == 0){
				i++;
				continue;
		}

		line ="T^";
		adjustStringLength(&line, 11, spaceChar, true);
		start_address = (*lpl)[i].loc;
		start_address_str = intToString(start_address, true);
		adjustStringLength(&start_address_str, 6, zeroChar, true);
		line += start_address_str;
		int x = 0;
		string temp = "";
		while (1){
			if (i >= (*opCodes).size() || x >= 5)
				break;

			if ((*opCodes)[i].compare("") == 0 || (*lpl)[i].p.lable.compare("*") == 0){
					i++;
					break;
			}
			temp += "^";
			temp += (*opCodes)[i];
			if (i+1 < (*opCodes).size()) end_address = (*lpl)[i+1].loc;
			else end_address = (*lpl)[i].loc;
			i++;
			x++;
		}
		length_str = intToString(end_address - start_address, true);
		adjustStringLength(&length_str, 2, zeroChar, true);
		line += "^";
		line += length_str;
		line += temp;
		writeLine(file, line);
	}
}

void writeModRecords(ofstream* file, vector<modification>* mods) { // 5
	char zeroChar = ZERO_CHAR;
	char spaceChar = SPACE_CHAR;
	int address = 0, hBytes = 0;
	string address_str, hBytes_str;
	string line = "\tModification Record(s) :\t\t\n";
	writeLine(file, line);
	for (int i = 0; (unsigned)i < mods->size(); i++) {
		modification mod = (*mods)[i];
		if (mod.exRef) {
			// multiple mod records
			for (int j = 0; (unsigned)j < mod.refs.size(); j++) {
				line = "M^";
				adjustStringLength(&line, 11, spaceChar, true);
				address = mod.address;
				address_str = intToString(address, true);
				line += address_str;
				line += "^";
				hBytes = mod.hbytes;
				hBytes_str = intToString(hBytes, false);
				adjustStringLength(&hBytes_str, 2, zeroChar, true);
				line += hBytes_str;
				line += "^";
				line += mod.signs[j];
				line += mod.refs[j];
				writeLine(file, line);
			}
		}
		else {
			line = "M^";
			adjustStringLength(&line, 11, spaceChar, true);
			address = mod.address;
			address_str = intToString(address, true);
			line += address_str;
			line += "^";
			hBytes = mod.hbytes;
			hBytes_str = intToString(hBytes, false);
			adjustStringLength(&hBytes_str, 2, zeroChar, true);
			line += hBytes_str;
			writeLine(file, line);
		}
	}
	writeLine(file, "");
}

void writeDefineRecord(ofstream* file, vector<string>* exdefs, map<string, symInfo*>* theMap) { // 2
	char zeroChar = ZERO_CHAR;
	char spaceChar = SPACE_CHAR;

	int address = 0;
	int i = 0;
	string address_str;
	string line = "\tDefine Record :\t\t\n";
	writeLine(file, line);
	for (; (unsigned)i < exdefs->size(); i++) {
		line = "D^";
		adjustStringLength(&line, 11, spaceChar, true);
		do {
			if ((unsigned)i >= exdefs->size()) break;
			string s = (*exdefs)[i];
			symInfo* sInfo = theMap->at(s);
			address = sInfo->address;
			address_str = intToString(address, true);
			adjustStringLength(&address_str, 6, zeroChar, true);
			line += (*exdefs)[i];
			line += "^";
			line += address_str;
			if ((i+1) % 5 != 0 && (unsigned)(i+1) < exdefs->size()) line += "^";
			i++;
		} while (i % 5 != 0);
		if ((unsigned)i >= exdefs->size())line += "\n";
		i--;
		writeLine(file, line);
	}

}

void writeReferRecord(ofstream* file, vector<string>* exrefs) { // 3
	char spaceChar = SPACE_CHAR;
	int i = 0;

	string line = "\tRefer Record :\t\t\n";
	writeLine(file, line);
	for (; (unsigned)i < exrefs->size(); i++) {
		line = "R^";
		adjustStringLength(&line, 11, spaceChar, true);
		do {
			if ((unsigned)i >= exrefs->size()) break;
			line += (*exrefs)[i];
			if ((i+1) % 5 != 0 && (unsigned)(i+1) < exrefs->size()) line += "^";
			i++;
		} while (i % 5 != 0);
		if ((unsigned)i >= exrefs->size()) line += "\n";
		i--;
		writeLine(file, line);
	}
}

void writeEndRecord() {

}
