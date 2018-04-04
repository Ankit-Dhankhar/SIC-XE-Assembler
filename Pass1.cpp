#include "Pass1.h"
string errorMessage;
vector<parsedLine> literals;
bool literalExistance;
int handelBYTE(string x) {
	string val = "";
	if (x.at(0) == 'x' || x.at(0) == 'X' || x.at(0) == 'c' || x.at(0) == 'C') {
		if (x.at(1) == '\'' && x.at(x.length() - 1) == '\'') {

			for (unsigned int i = 2; i < x.length() - 1; i++) {
				val += x.at(i);
			}
		} else {
			errorMessage += "\nnot a hexadecimal/character string";
			return 0;
		}
	} else {
		errorMessage += "\nillegal operand!!!";
		return 0;
	}

	if (x.at(0) == 'c' || x.at(0) == 'C')
		return val.length();

	return val.length() % 2 == 0 ? val.length() / 2 : val.length() / 2 + 1;
}

void addLableToSymTab(string x, cSect* curr) {
	if (x.compare("") != 0) {
		try {
			curr->symTab.at(x);
			errorMessage += "\nDuplicate Label Definition";
		} catch (out_of_range& oor) {
			symInfo* c = new symInfo;
			c->address = curr->locCtr;
			c->relocatble = true;
			curr->symTab.insert(pair<string, symInfo*>(x, c));
		}
	}
}

void writeFomatted(parsedLine pl, cSect* current) {
	toWrite x;
	x.data = constructLine((*current).locCtr, pl.lable, pl.opcode,
			mergeStrings(pl.operand1, pl.operand2, ','));
	x.type = 1;
	current->dataSect.push_back(x);
	locatedParsedLine temp;
	temp.p = pl;
	temp.loc = current->locCtr;
	current->locpl.push_back(temp);
}

void incLocCtr(cSect* cur, int incr) {
	cur->locCtr += incr;
	if (cur->locCtr > 0x33039) {
		errorMessage += "\nout of range address";
	}
}

void writeAndIncr(int incr, parsedLine pl, cSect* curr, bool* started,
		bool* ended) {
	if (!*started) {
		*started = true;
		curr->locCtr = 0;
		writeFomatted(pl, curr);
		addLableToSymTab(pl.lable, curr);
		incLocCtr(curr, incr);
	} else if (*started && !*ended) {
		writeFomatted(pl, curr);
		addLableToSymTab(pl.lable, curr);
		incLocCtr(curr, incr);
	} else if (*ended) {
		errorMessage += "\nDefinition After END";
	}
}

bool hasExternalReference(parsedLine pl, cSect* current, vector<string>* refs,
		vector<char>* signs) {
	if (pl.operand1.find("(") != string::npos
			&& pl.operand1.find(")") != string::npos) {
		errorMessage += "\nBrackets are not allowed";
		return false;
	}

	vector<string> all = generalSplit(pl.operand1, "+-*/");
	bool answer = false;
	string myOperand = pl.operand1;
	for (unsigned int i = 0; i < all.size(); i++) {
		if (find(current->extRef.begin(), current->extRef.end(), all[i])
				!= current->extRef.end()) {
			refs->push_back(all[i]);
			answer = true;
			int position = myOperand.find(all[i]);
			myOperand.substr(position + all[i].size());
			if (position == 0) {
				signs->push_back('+');
			} else {
				char temp = myOperand.at(position - 1);
				if (temp == '+' || temp == '-')
					signs->push_back(temp);
			}
		}
	}
	return answer;
}

void handelModRecord(parsedLine pl, cSect* current) {
	modification mod;
	bool hasP = trim(pl.opcode).at(0) == '+';
	bool hasExRef = hasExternalReference(pl, current, &(mod.refs),
			&(mod.signs));

	if (hasP) {
		mod.address = current->locCtr + 1;
		mod.hbytes = 5;
		if (hasExRef) {
			mod.exRef = true;
		} else {
			mod.exRef = false;
		}
		current->mods.push_back(mod);
	} else {
		if (hasExRef) {
			mod.exRef = true;
			if (toUpperCase(pl.opcode).compare("BYTE") == 0) {
				mod.address = current->locCtr;
				mod.hbytes = 2 * handelBYTE(pl.operand1);
				current->mods.push_back(mod);
			} else if (toUpperCase(pl.opcode).compare("WORD") == 0) {
				mod.address = current->locCtr;
				mod.hbytes = 6;
				current->mods.push_back(mod);
			} else {
				errorMessage += "\nUsing ExtRef with no +";
			}
		}
	}
}
bool checkLabels(vector<string> labels, cSect* current) {
	if (labels.size() == 1 && labels[0] == "*")
		return true;
	for (unsigned int i = 0; i < labels.size(); i++) {
		if (labels[i].at(0) == '#' || labels[i].at(0) == '@')
			labels[i] = labels[i].substr(1);
		if (!isNumeric(labels[i])) {
			try {
				current->symTab.at(labels[i]);
			} catch (out_of_range& x) {
				return false;
			}
		}
	}
	return true;
}
void handleEquate(parsedLine pl, cSect * current) {
	if (findExpressionType(pl.operand1) != -1) {

		vector<string> labels = generalSplit(pl.operand1, "+-*/");
		if (pl.operand1.compare("*") == 0)
			labels.push_back("*");
		if (!checkLabels(labels, current)) {
			errorMessage += "\nUNIDENTIFIED LABELS";
			return;
		} else {
			int value;
			try {
				value = evaluateOperand(pl.operand1, current);
			} catch (string* e) {
				errorMessage += "\nUnable to evaluate the given expression";
				delete e;
				return;
			}
			symInfo* c = new symInfo;
			c->address = value;
			c->relocatble = true;
			current->symTab.insert(pair<string, symInfo*>(pl.lable, c));
			writeFomatted(pl, current);
		}
	} else {

		errorMessage += "\nInvalid Expression";
	}
}

void handleOrg(parsedLine pl, cSect* current) {
	if (validateExpression(pl.operand1)) {
		vector<string> labels = generalSplit(pl.operand1, "+-*/");
		if (!checkLabels(labels, current)) {
			errorMessage += "\n UNIDENTIFIED LABELS";
			return;
		} else {
			int value;
			try {
				value = evaluateExpression(pl.operand1, current);
			} catch (string* e) {
				errorMessage += "\nUnable to evaluate the given expression";
				delete e;
				return;
			}
			writeFomatted(pl, current);
			current->locCtr = value;
		}
	} else {
		errorMessage += "\nInvalid Expression";
	}
}

bool isLit(string pl) {
	if (pl.at(0) == '=')
		return true;
	return false;
}

int literalLength(string literal, cSect* current) {
	int x;

	int y = evaluateOperand(literal, current);
	if (literal.at(1) == 'C') {
		string s = literal.substr(3, literal.length() - 4);
		x = s.length();
	} else if (literal.at(1) == 'X') {
		string s = literal.substr(3, literal.length() - 4);
		x = s.length() * 2;
	} else
		x = 3;
	return x;

}
void writeLiterals(cSect* current) {
	literalExistance = false;
	for (unsigned int i = 0; i < literals.size(); i++) {
		parsedLine p;
		p.lable = "*";
		p.opcode = trim(literals[i].operand1);
		p.operand1 = "";
		p.operand2 = "";
		p.err = "";
		writeFomatted(p, current);
		current->litTab.insert(
				pair<string, int>(trim(literals[i].operand1), current->locCtr));
		    //  Increment by the literal length
		  	incLocCtr(current, literalLength(literals[i].operand1, current));

	}
	literals.clear();
}

void addExtRefs(parsedLine pl, cSect* current) {
	if (current->extRef.size() == 0) {
		current->extRef = generalSplit(pl.operand1, ",");
		for (unsigned int i = 0; i < current->extRef.size(); i++) {
			current->extRef[i] = trim(current->extRef[i]);
		}
	} else
		errorMessage +=
				"\nEXTREF can be written only once in a control section";
}

void addExtDefs(parsedLine pl, cSect* current) {
	if (current->extDef.size() == 0) {
		current->extDef = generalSplit(pl.operand1, ",");
		for (unsigned int i = 0; i < current->extDef.size(); i++) {
			current->extDef[i] = trim(current->extDef[i]);
		}
	} else
		errorMessage +=
				"\nEXTDEF can be written only once in a control section";
}

void getlocCtrIncr(parsedLine pl, cSect* current, bool* started, bool* ended) {
	int incr = validate(pl);
	if (pl.operand1.length() > 0 && isLit(pl.operand1)) {
		bool add = true;
		for(unsigned int y = 0; y < literals.size() ; y++)
		{
			if(literals[y].operand1.compare(pl.operand1)==0){
				add = false;
				break;
			}
		}
		if(add)
		{
			literals.push_back(pl);
		}
		literalExistance = true;
	}
	handelModRecord(pl, current);
	if (incr == -1) { // Directive
		string upper = toUpperCase(pl.opcode);
		if (upper.compare("START") == 0) {
			if (!*started) {
				*started = true;
				incLocCtr(current, parseHexaDecimal(pl.operand1));
				writeFomatted(pl, current);
				addLableToSymTab(pl.lable, current);
			} else {
				errorMessage += "\nMisplaced START";
			}
		} else if (upper.compare("END") == 0) {
			if (!*started) {
				errorMessage += "\nEnded before START";
			} else if (*started && !*ended) {
				*ended = true;
				incLocCtr(current, 0);
				writeFomatted(pl, current);
				addLableToSymTab(pl.lable, current);
			} else if (*ended) {
				errorMessage += "\nMultiple END clauses.";
			}
		} else if (upper.compare("BYTE") == 0) {
			writeAndIncr(handelBYTE(pl.operand1), pl, current, started, ended);
		} else if (upper.compare("WORD") == 0) {
			writeAndIncr(3, pl, current, started, ended);
		} else if (upper.compare("RESB") == 0) {
			writeAndIncr(parseDecimal(pl.operand1), pl, current, started,
					ended);
		} else if (upper.compare("RESW") == 0) {
			writeAndIncr(parseDecimal(pl.operand1) * 3, pl, current, started,
					ended);
		} else if (upper.compare("EQU") == 0) {
			handleEquate(pl, current);
		} else if (upper.compare("ORG") == 0) {
			handleOrg(pl, current);
		} else if (upper.compare("LTORG") == 0) {
			writeFomatted(pl, current);
			writeLiterals(current);
		} else if (upper.compare("EXTREF") == 0) {
			writeFomatted(pl, current);
			addExtRefs(pl, current);
		} else if (upper.compare("EXTDEF") == 0) {
			writeFomatted(pl, current);
			addExtDefs(pl, current);
		}
	} else { //Operations (formats)
		if (!*started) {
			*started = true;
			current->locCtr = 0;
			writeFomatted(pl, current);
			addLableToSymTab(pl.lable, current);
			incLocCtr(current, incr);
		} else if (*started && !*ended) {
			writeFomatted(pl, current);
			addLableToSymTab(pl.lable, current);
			incLocCtr(current, incr);
		} else if (*ended) {
			errorMessage += "\nDefinition After END";
		}
	}
}

bool isComment(parsedLine pl) {
	return trim(pl.opcode).at(0) == '.';
}

bool isEmptyLine(parsedLine pl) {
	if (pl.lable.compare("") == 0 && pl.opcode.compare("") == 0
			&& pl.operand1.compare("") == 0 && pl.operand2.compare("") == 0)
		return true;

	return false;
}

cSect runPass1(vector<parsedLine> v, bool* started, bool* ended,
		bool* successfull) {
	parsedLine pl;
	cSect current;
	current.locCtr = 0;
	literals.clear();
	literalExistance = false;
	for (unsigned int i = 0; i < v.size(); i++) {
		pl = v[i];
		if (isEmptyLine(pl)) {
			continue;
		}
		if (isComment(pl)) {
			toWrite x;
			x.data = pl.opcode;
			x.type = 0;
			current.dataSect.push_back(x);
			continue;
		}
		try {
			getlocCtrIncr(pl, &current, started, ended);
		} catch (string* e) {
			writeFomatted(pl, &current);
			*(successfull) = false;
			errorMessage += "\n";
			errorMessage += *e;
			delete e;
		}
		if (errorMessage.compare("") != 0) {
			toWrite x;
			*successfull = false;
			x.data = errorMessage;
			x.type = -1;
			current.dataSect.push_back(x);
			errorMessage = "";
		}
	}
	if (literalExistance)
		writeLiterals(&current);
	return current;
}
