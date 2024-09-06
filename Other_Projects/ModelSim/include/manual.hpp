#ifndef __MANUAL__
#define __MANUAL__

#include <iostream>
#include <memory>
#include <functional>
#include <bits/stdc++.h>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <set>
#include <map>

using namespace std;

const int Z = -1;
const int ONE_VALUE = 1;
const int ZERO_VALUE = 0;

const string Z_STRING = "z";
const string ONE_STRING = "1";
const string ZERO_STRING = "0";

const string INPUTS_NAME = "in";
const string OUTPUTS_NAME = "out";

const string AND_GATE_NAME = "and";
const string OR_GATE_NAME = "or";
const string NOT_GATE_NAME = "not";
const string XOR_GATE_NAME = "xor";
const string NAND_GATE_NAME = "nand";
const string NOR_GATE_NAME = "nor";

const string EXIST_MODULE_ERROR = "this module already exists";
const string DUPLICATE_ID_ERROR = "duplicate ID";
const string INCOMPATIBLE_ERROR = "incompatible inputs";
const string ID_NOT_FOUND_ERROR = "ID not found";
const string GATE_NOT_FOUND_ERROR = "gate/module not found";
const string INVALID_VALUE_ERROR = "value not valid";
const string INVALID_CONNECTION_ERROR = "invalid connection";

const string PROGRAM_NAME = "my_ModelSim_program";

const char COMMAND_SEPARATOR = ' ';

enum wire_type {INPUT, OUTPUT};
enum search_status {IO, GATES, ALL};

enum request {NEW_MODULE, CONNECT, ADD, PUT, END_MODULE, PRINT};
const vector<string> commands = {"new_module", "connect", "add", "put", "end_module", "print"};

struct info {
    string name;
    int status;
};

#endif