#include "ExpressionEvaluator.h"

cSect* csect = NULL;

void setCSECT(cSect* x) {
	csect = x;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string& str, const std::string& from,
		const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

bool isValidNumber(string num) {
	unsigned int i = 0;
	if (num[0] == '-')
		i++;
	for (; i < num.length(); i++)
		if (num[i] < '0' || num[i] > '9')
			return false;
	return true;
}

bool isValidOpName(string operand) {
	for (unsigned int i = 0; i < operand.length(); i++)
		if ((operand[i] < 'A' || operand[i] > 'Z')
				&& (operand[i] < 'a' || operand[i] > 'z'))
			return false;
	return true;
}

bool isOperator(char c) {
	return c == '+' || c == '/' || c == '*' || c == '-' || c == '%' || c == '('
			|| c == ')';
}

string valueOf(string name, bool useDummyValues = false) { // get value from optab
	if (name[0] >= '0' && name[0] <= '9')
		return name;
	if (useDummyValues)
		return "10";

    if(name.compare("*")==0){
		return intToString(csect->locCtr,false);
	}

	try {
		return intToString(csect->symTab.at(name)->address, false);
	} catch (out_of_range& orr) {
		if (find(csect->extRef.begin(), csect->extRef.end(), name)
				!= csect->extRef.end()) {
			return "0";
		} else {
			throw(string) "label not found";
		}
	}
}

string substitute(string expression, bool useDummyValues = false) {
	string exp = ""; //.replaceAll(" ", "");   // assuming no spaces in expression
	string name = "";
	bool nextCouldBeAsterix = true;

	for (unsigned int i = 0; i < expression.length();) {
		name = "";

		while (i < expression.length() && !isOperator(expression[i]))
			name += expression[i++];

		if( name.length() == 0 && nextCouldBeAsterix && expression[i] == '*')
		    name += expression[i++];

		if (name.compare("") != 0)
            exp += valueOf(name, useDummyValues); // should be replaced with value from optab

		nextCouldBeAsterix = false;
		while (i < expression.length() && isOperator(expression[i])) {
			if (nextCouldBeAsterix && expression[i] == '*')
				exp += valueOf("*", useDummyValues);
			else
				exp += expression[i];

			if (expression[i] != ')' && (!nextCouldBeAsterix || expression[i] != '*'))
				nextCouldBeAsterix = true;
			else
				nextCouldBeAsterix = false;
			i++;
		}
	}
	return exp;
}

int comparePeriority(char opr1, char opr2) {
	if (opr1 == opr2)
		return 0;
	if (opr1 == ')')
		return -1;
	if (opr2 == ')')
		return 1;
	if (opr1 == '*' || opr1 == '/' || opr1 == '%')
		return 1;
	if (opr2 == '*' || opr2 == '/' || opr2 == '%')
		return -1;
	if (opr1 == '+' || opr1 == '-')
		return 1;
	if (opr2 == '+' || opr2 == '-')
		return -1;
	if (opr2 == '(')
		return -1;
	if (opr1 == '(')
		return 1;
	return 0;
}

float evaluateSimpleExp(float op1, char operation, float op2) {
	switch (operation) {
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '%':
		return (int) op1 % (int) op2;
	}
	return false;
}

int resultingRelativityDegree(int relDeg1, int val1, char operation,
		int relDeg2, int val2) {
	switch (operation) {
	case '*':
		if (relDeg1 != 0 && relDeg2 != 0)
			throw(string) "Error multiplying relative addresses";
		if (relDeg1 == 0 && relDeg2 == 0)
			return 0;
		return (relDeg1 != 0) ? relDeg1 * val2 : relDeg2 * val1;
	case '/':
		if (relDeg1 != 0 || relDeg2 != 0)
			throw(string) "Error deviding relative addresses";
		return 0;
	case '+':
		return relDeg1 + relDeg2;
	case '-':
		return relDeg1 - relDeg2;
	case '%':
		if (relDeg1 != 0 || relDeg2 != 0)
			throw(string) "Error taking modulus of relative addresses";
		return 0;
	}
	return 0;
}

int valueOfExplicitExp(string exp, queue<char> isRelative,
		bool *retFlagIsRelative) {
	stack<char> operations;
	stack<int> values, degreeOfRelativity;

	string op = "";
	unsigned int i;
	bool lastAddedIsOperand = false;
	for (i = 0; i < exp.length();) {
		op = "";
		while ((i < exp.length() && !isOperator(exp[i]))
				|| (exp[i] == '-' && op.length() == 0 && !lastAddedIsOperand))
			op += exp[i++];
		if (op.compare("-") == 0) {
			values.push(-1);
			degreeOfRelativity.push(0);
			operations.push('*');
			lastAddedIsOperand = false;

		} else if (op.length() != 0) {
			values.push(atoi(op.c_str()));
			degreeOfRelativity.push((isRelative.front() == 'R') ? 1 : 0);
			isRelative.pop();
			lastAddedIsOperand = true;
		}

		else if (operations.empty() || exp[i] == '('
				|| comparePeriority(operations.top(), exp[i]) != 1) {
			operations.push(exp[i++]);
			lastAddedIsOperand = false;
		} else // evaluate the top operation in stack
		{
			if (operations.top() == '(' && exp[i] == ')') {
				operations.pop();
				i++;
			} else {
				int op2 = values.top();
				values.pop();
				int rd2 = degreeOfRelativity.top();
				degreeOfRelativity.pop();
				int op1 = values.top();
				values.pop();
				int rd1 = degreeOfRelativity.top();
				degreeOfRelativity.pop();
				int result = evaluateSimpleExp(op1, operations.top(), op2);
				degreeOfRelativity.push(
						resultingRelativityDegree(rd1, op1, operations.top(),
								rd2, op2));
				operations.pop();
				values.push(result);
			}
		}
	}
	while (operations.size() != 0) {
		int op2 = values.top();
		values.pop();
		int rd2 = degreeOfRelativity.top();
		degreeOfRelativity.pop();
		int op1 = values.top();
		values.pop();
		int rd1 = degreeOfRelativity.top();
		degreeOfRelativity.pop();
		int result = evaluateSimpleExp(op1, operations.top(), op2);
		degreeOfRelativity.push(
				resultingRelativityDegree(rd1, op1, operations.top(), rd2,
						op2));
		operations.pop();
		values.push(result);
	}

	if (values.size() == 1) {
		if (degreeOfRelativity.top() != 1 && degreeOfRelativity.top() != 0)
			throw(string) "invalid operations on relative variables";
		*retFlagIsRelative = (degreeOfRelativity.top() == 0) ? false : true;
		int ret = values.top();
		values.pop();
		return ret;
	}
	// through exception
	throw(string) "error evaluating expression";
}

queue<char> validate(string expression) { // returns queue as map for values wheather are relative or absolute
	queue<char> exp;
	string operand = "";
	bool nextSouldBeOperand = true;
	int bracketCounter = 0;

	for (unsigned int i = 0; i < expression.length();) {
		operand = "";
		while (i < expression.length() && !isOperator(expression[i]))
			operand += expression[i++];

		if (operand.length() > 0) {
			if (!nextSouldBeOperand)
				throw(string) "Invalid operations in expression1";
			if (isValidNumber(operand))
				exp.push('A');
			else if (isValidOpName(operand))
				exp.push('R');
			else
				throw(string) "Bad Operand Name";
			nextSouldBeOperand = false;
		}

		while (i < expression.length() && isOperator(expression[i])) {
			if (nextSouldBeOperand && expression[i] == '-')
				break;
			if (nextSouldBeOperand) {
				if (expression[i] == '*') {
					exp.push('R');
					nextSouldBeOperand = false;
				} else if (expression[i] == '(')
					nextSouldBeOperand = true;
				else
					throw(string) "Invalid operations in expression";
			} else {
				if (expression[i] != ')')
					nextSouldBeOperand = true;
				else
					nextSouldBeOperand = false;
			}
			if (expression[i] == '(')
				bracketCounter++;
			if (expression[i] == ')')
				bracketCounter--;
			if (bracketCounter < 0)
				throw(string) "non-matching brackets";
			i++;
		}
	}
	if (nextSouldBeOperand)
		throw(string) "missing operand";
	if (bracketCounter != 0)
		throw(string) "non-matching brackets";

	return exp;
}

int evaluateExpression(string exp, cSect* cs, bool useDummyValues) {
	bool x;
	setCSECT(cs);
	return valueOfExplicitExp(substitute(exp, useDummyValues), validate(exp), &x);
}

bool validateExpression(string exp) {
	try {
		evaluateExpression(exp, csect, true);
	} catch (string& s) {
		return false;
	}
	return true;
}

bool isRelativeExpression(string exp) {
	bool x;
	valueOfExplicitExp(substitute(exp, true), validate(exp), &x);
	return x;
}

int mains() {
	// -(-(-(-2*(3--7)))*(60/4))
	// ((gg+tt+10)*2)-4*tt
	string expression = "*";

	try {
	    cout<< substitute(expression, true);
	    validate(expression);

		cout << "\n---------------------------\n\n";
		cout << "Is valid Expression : " << validateExpression(expression)
				<< '\n';
		cout << "\n---------------------------\n\n";
		cout << "Is Relative Expression : " << isRelativeExpression(expression)
				<< '\n';
		cout << "\n---------------------------\n\n";
		//cout << "Evaluate Expression : " << evaluateExpression(expression)<< '\n';
		cout << "\n---------------------------\n\n";
	} catch (string& s) {
		cout << s << "\n";
	}

	return 0;
}
