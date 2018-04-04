#include "OpCodeGenerator.h"

map<string, unsigned char>* registers = NULL;

map<string, unsigned char>* getRegMap() {
	if (registers != NULL)
		return registers;

	registers = new map<string, unsigned char>();
	registers->insert(pair<string, unsigned char>("A", 0));
	registers->insert(pair<string, unsigned char>("X", 1));
	registers->insert(pair<string, unsigned char>("L", 2));
	registers->insert(pair<string, unsigned char>("B", 3));
	registers->insert(pair<string, unsigned char>("S", 4));
	registers->insert(pair<string, unsigned char>("T", 5));
	registers->insert(pair<string, unsigned char>("F", 6));
	return registers;
}

opCode generateOpCode(parsedLine pl, int loCtr, cSect* current) {
	opCode toRet;
	string modOp = (pl.opcode).at(0) == '+' ? (pl.opcode).substr(1) : pl.opcode;
	modOp = toUpperCase(modOp);
	string op1 = toUpperCase(pl.operand1);
	string op2 = toUpperCase(pl.operand2);

	OpInfo* info;
	try {
		info = getOpTab()->at(modOp); //Only if instruction, not directive
	} catch (out_of_range& orr) { //Directive
		int value = 0;
		if (modOp.compare("WORD") == 0) {
			toRet.format = 11;

			value = evaluateOperand(pl.operand1, current);

			if (value >= -(1 << 23) && value <= (1 << 23) - 1) {
				toRet.displacement = value;
			} else {
				throw new string("Too large to store");
			}
		} else if (modOp.compare("BYTE") == 0) {
			toRet.format = 22;

			if (op1.at(0) == 'C') { //max 7 ascii characters +3 'C' '\'' '\''
				if (op1.size() <= 10) {
					toRet.displacement = evaluateOperand(pl.operand1, current);
				} else {
					throw new string("Too large to store");
				}
			} else if (op1.at(0) == 'X') {
				if (op1.size() <= 17) { //max 14 hexa characters +3 'X' '\'' '\''
					toRet.displacement = evaluateOperand(pl.operand1, current);
				} else {
					throw new string("Too large to store");
				}
			}
		} else if (modOp.at(0) == '=') {
			toRet.format = 22;
			toRet.displacement = valueOfLiteralOperand(pl.opcode);
		} else {
			toRet.format = 33;
		}
		return toRet;
	}

	unsigned char format = info->format;

	if (format == FORMAT_1) {
		toRet.operation = info->opCode;
		toRet.displacement = 0;
		toRet.format = FORMAT_1;
		toRet.flags[5] = 1;
		toRet.flags[4] = 1;
		toRet.flags[3] = 0;
		toRet.flags[2] = 0;
		toRet.flags[1] = 0;
		toRet.flags[0] = 0;
	} else if (format == FORMAT_2) {
		toRet.operation = info->opCode;
		toRet.reg1 = getRegMap()->at(op1);
		toRet.reg2 = (op2).compare("") != 0 ? registers->at(op2) : 0;
		toRet.format = FORMAT_2;
		toRet.flags[5] = 1;
		toRet.flags[4] = 1;
		toRet.flags[3] = 0;
		toRet.flags[2] = 0;
		toRet.flags[1] = 0;
		toRet.flags[0] = 0;
	} else {
		// format 3 or 4
		toRet.operation = info->opCode;
		toRet.format = FORMAT_3_4;

		if (modOp.compare("RSUB") == 0) {
			toRet.displacement = 0;
			toRet.flags[5] = 1; //n
			toRet.flags[4] = 1; //i
			toRet.flags[3] = 0; //x
			return toRet;
		}
		toRet.flags[0] = (pl.opcode).at(0) == '+' ? 1 : 0; //e

		if (op1.at(0) == '#') { //Immediate
			toRet.flags[5] = 0; //n
			toRet.flags[4] = 1; //i
			toRet.flags[3] = 0; //x
		} else if ((pl.operand1).at(0) == '@') { //Indirect
			toRet.flags[5] = 1; //n
			toRet.flags[4] = 0; //i
			toRet.flags[3] = 0; //x
		} else {
			toRet.flags[5] = 1; //n
			toRet.flags[4] = 1; //i
			toRet.flags[3] = (op2).compare("X") == 0 ? 1 : 0; //x
		}

		int address = 0;
		try {
			if (findExpressionType(pl.operand1) == 2)
				address = addressOfLiteralOperand(pl.operand1);
			else
				address = evaluateOperand(pl.operand1, current);
		} catch (string& err) {
			throw err;
		}

		if (toRet.flags[0]) { //Extended? (20 bits)
			toRet.flags[2] = 0; //b
			toRet.flags[1] = 0; //p
			if (address >= -(1 << 19) && address <= (1 << 19) - 1)
				toRet.displacement = address;
			else
				throw new string("Too large to store");
		} else { //only 12 bits
			toRet.flags[2] = 0; //b
			toRet.flags[1] = 1; //p
			int disp = 0;
			if (findExpressionType(pl.operand1) == 6
					|| findExpressionType(pl.operand1) == 1
					|| findExpressionType(pl.operand1) == 2
					|| (findExpressionType(pl.operand1) == 0
							&& isValidOpNm(pl.operand1)))
				disp = address - loCtr;
			else
				disp = address; //Numeric value after #
			if (disp >= -(1 << 11) && disp <= (1 << 11) - 1) { //Because PC is signed
				toRet.displacement = disp;
			} else {
				throw new string("Too large to store");
			}
		}
	}
	return toRet;
}

string calcOpCode(opCode op) {
	string returnedString = "";
	if (op.format == 11) { // reserved word, length = 6
		string final_opCode = intToString(op.displacement, true);
		adjustStringLength(&final_opCode, 6, '0', true);
		return final_opCode;
	} else if (op.format == 22) { // reserved byte, length = 2
		string final_opCode = intToString(op.displacement, true);
		adjustStringLength(&final_opCode, 2, '0', true);
		return final_opCode;
	} else if (op.format == 33) {
		return returnedString;
	} else if (op.format == FORMAT_1) {
		returnedString = intToString(op.operation, true);
	} else if (op.format == FORMAT_2) {
		returnedString = ((intToString(op.operation, true)
				+ intToString(op.reg1, false)) + intToString(op.reg2, false));
	} else { // format = 3 or 4
		int ni_val = 0, xbpe_val = 0;
		binaryToDec(op.flags, &ni_val, &xbpe_val);
		string disp_str = intToString(op.displacement, true);
		if (op.flags[0] == 0) {
			adjustStringLength(&disp_str, 3, '0', true);
			disp_str = disp_str.substr(disp_str.length() - 3);
		} else {
			adjustStringLength(&disp_str, 5, '0', true);
			disp_str = disp_str.substr(disp_str.length() - 5);
		}
		returnedString = ((intToString(op.operation + ni_val, true)
				+ intToString(xbpe_val, true)) + disp_str);
	}
	return returnedString;
}

void binaryToDec(bitset<6> flags, int* ni_val, int* xbpe_val) { // takes all 6 flags
	bitset<4> xbpe_flags;
	for (int i = 0; i < 4; i++)
		xbpe_flags[i] = flags[i];

	bitset<2> ni_flags;
	for (int i = 0; i < 2; i++)
		ni_flags[i] = flags[i + 4];

	*ni_val = *xbpe_val = 0;
	stringstream ss_1, ss_2;
	ss_1 << uppercase << std::hex << ni_flags.to_ulong();
	ss_1 >> std::hex >> *ni_val;
	ss_2 << std::hex << uppercase << xbpe_flags.to_ulong();
	ss_2 >> std::hex >> *xbpe_val;
}
