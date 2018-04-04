#ifndef OPCODEGENERATOR_H_
#define OPCODEGENERATOR_H_

#include <iostream>
#include <stdexcept>
#include "Parser.h"
#include "OpTab.h"
#include "IO.h"
#include "StringUtilities.h"
#include "structs.h"
#include "OperandHandler.h"
#include "ExpressionEvaluator.h"

using namespace std;

opCode generateOpCode(parsedLine pl, int loCtr, cSect* current);

string calcOpCode(opCode op);

void binaryToDec(bitset<6> flags, int* ni_val, int* xbpe_val);

#endif
