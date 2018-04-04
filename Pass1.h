#ifndef PASS1_H_
#define PASS1_H_

#include "Validate.h"
#include "Parser.h"
#include "ExpressionEvaluator.h"
#include "OperandHandler.h"
#include "OpTab.h"
#include "StringUtilities.h"
#include "IO.h"
#include "structs.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>

cSect runPass1(vector<parsedLine> v, bool* started, bool* ended,
		bool* successfull);

#endif
