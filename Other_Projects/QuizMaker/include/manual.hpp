#ifndef __MANUAL__
#define __MANUAL__

#include <bits/stdc++.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <utility>
#include <memory>
#include <set>

using namespace std;

enum situations_index {NO_ANSWER , CORRECT , WRONG};
const vector<string> situations = {"no_answer" , "correct" , "wrong"};
const vector<string> situations_msg = {"no answer." , "correct answer." , "wrong answer."}; 
enum questions_type_index {SINGLE , MULTIPLE , SHORT};
const vector<string> questions_type = {"single_answer" , "multiple_answer" , "short_answer"}; 
enum commands_index {SUBMIT , FINISH};
const vector<string> commands = {"submit_answer" , "finish_exam"};

const char SEPARATOR = ' ';
const int answers_start_index = 2;
const string CORRECT_ANSWER = "correct answer:";
const string YOUR_ANSWER = "your answer:";
const string FINAL_GRADE_MSG = "final grade:";

#endif