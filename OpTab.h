#ifndef OPTAB_H_
#define OPTAB_H_

#include <map>
#include <string>

#include "structs.h"

using namespace std;

const unsigned char FORMAT_1 = 1;
const unsigned char FORMAT_2 = 2;
const unsigned char FORMAT_3_4 = 3;

void deleteOpTab();
map<string, OpInfo*>* getOpTab();

#endif
