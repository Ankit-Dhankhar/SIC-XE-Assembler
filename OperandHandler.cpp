#include "OperandHandler.h"

cSect* curCSECT;

void setCurCSECT(cSect* x) {
	curCSECT = x;
}

int getValueOf(string name) { // get value from optab
	if (name.compare("*") == 0) {
		return curCSECT->locCtr;
	}

	try {
		return curCSECT->symTab.at(name)->address;
	} catch (out_of_range& orr) {
		if (find(curCSECT->extRef.begin(), curCSECT->extRef.end(), name)
				!= curCSECT->extRef.end()) {
			return 0;
		} else {
			throw(string) "label not found";
		}
	}
}

bool isValidNum(string num) {
	unsigned int i = 0;
	if (num[0] == '-')
		i++;
	for (; i < num.length(); i++)
		if (num[i] < '0' || num[i] > '9')
			return false;
	return true;
}

bool isValidOpNm(string operand) {
	if(operand.compare("*")==0)
		return true;
	for (unsigned int i = 0; i < operand.length(); i++)
		if ((operand[i] < 'A' || operand[i] > 'Z')
				&& (operand[i] < 'a' || operand[i] > 'z'))
			return false;
	return true;
}

bool isValidHexConstant(string op) {
	if (op.length() < 3 || op[0] != 'X' || op[1] != '\''
			|| op[op.length() - 1] != '\'')
		return false;
	return isHexa(op.substr(2, op.length() - 3));
}

bool isValidByteConstant(string op) {
	if (op.length() < 3 || op[0] != 'C' || op[1] != '\''
			|| op[op.length() - 1] != '\'')
		return false;
	return true;
}

bool isValidImmediateOp(string op) {
	if (op.length() < 2 || op[0] != '#')
		return false;
	string rest = op.substr(1);
	return isValidNum(rest) || isValidOpNm(rest) || isValidHexConstant(rest)
			|| isValidByteConstant(rest);
}

bool isValidIndirectOp(string op) {
	if (op.length() < 2 || op[0] != '@')
		return false;
	string rest = op.substr(1);
	return isValidNum(rest) || isValidOpNm(rest);
}

bool isValidLiteralOp(string op) {
	if (op.length() < 2 || op[0] != '=')
		return false;
	string rest = op.substr(1);
	//////// don't know what to write
	return isValidNum(rest) || isValidOpNm(rest) || isValidHexConstant(rest)
			|| isValidByteConstant(rest);
}

int findExpressionType(string op) {
	if (op.length() == 0)
		return -1;
	if (isValidImmediateOp(op))
		return 0;
	if (isValidIndirectOp(op))
		return 1;
	if (isValidLiteralOp(op))
		return 2;
	if (isValidHexConstant(op))
		return 3;
	if (isValidByteConstant(op))
		return 4;
	if (isValidNum(op))
		return 5;
	if (validateExpression(op))
		return 6;
	return -1;
}

int valueOfByteConstant(string op) {
	int value = 0;
	for (unsigned int i = 0; i < op.length(); i++)
		value += ((int) op[i]) << (i * 8);
	return value;
}

int valueOfImmediateOperand(string op) {
	string rest = op.substr(1);
	if (isValidHexConstant(rest))
		return parseHexaDecimal(rest.substr(2, rest.length() - 3));
	if (isValidByteConstant(rest))
		return valueOfByteConstant(rest.substr(2, rest.length() - 3));
	if (isValidOpNm(rest))
		return getValueOf(rest);
	if (isValidNum(rest))
		return parseDecimal(rest);

	throw(string) "invalid immediate operand";
}

int valueOfIndirectOperand(string op) {
	string rest = op.substr(1);
	if (isValidOpNm(rest))
		return getValueOf(rest);
	if (isValidNum(rest))
		return parseDecimal(rest);
	throw(string) "invalid indirect operand";
}

int valueOfLiteralOperand(string op) {

	string rest = op.substr(1);
	if (isValidHexConstant(rest))
		return parseHexaDecimal(rest.substr(2, rest.length() - 3));
	if (isValidByteConstant(rest))
		return valueOfByteConstant(rest.substr(2, rest.length() - 3));
	if (isValidNum(rest))
		return parseDecimal(rest);

	throw(string) "invalid literal operand";
}

int addressOfLiteralOperand(string op) {
	try
	{
		return curCSECT->litTab.at(op);
	} catch(out_of_range& err){
		throw(string) "invalid literal operand";
	}
}




int evaluateOperand(string operand, cSect* x) {
	int type = findExpressionType(operand);
	setCurCSECT(x);
	switch (type) {
	case 0: // #
		return valueOfImmediateOperand(operand);
	case 1: // @
		return valueOfIndirectOperand(operand);
	case 2: // =
		return valueOfLiteralOperand(operand);
	case 3:	// Hex Constant
		return parseHexaDecimal(operand.substr(2, operand.length() - 3));
	case 4:	// Byte Constant
		return valueOfByteConstant(operand.substr(2, operand.length() - 3));
	case 5:	// int constant
		return parseDecimal(operand);
	case 6: // expression
		return evaluateExpression(operand, curCSECT, false);
	default:
		throw(string) "invalid operand";
	}
}

int mainz() {
	try {
		cout << evaluateOperand("#BUFFER");
	} catch (string& x) {
		cout << x << "\n";
	}
	return 0;
}
