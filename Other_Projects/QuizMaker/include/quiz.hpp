#ifndef __QUIZ__
#define __QUIZ__

#include "manual.hpp"
#include "question.hpp"

class TopLevel {
private:
    vector<shared_ptr<Question>> questions;
    set<int> answered_questions;
    int correct_answers;
    int num_of_questions;
public:
    TopLevel();
    void add_single_question(ifstream &input_file, int index);
    void add_multiple_question(ifstream &input_file, int index);
    void add_short_question(ifstream &input_file, int index);
    void get_questions_from_file(string file_name);
    void check_answer(vector<string> inputs);
    void get_quiz();
    string get_final_grade();
    void show_result_of_exam();
};

vector<string> make_apart(string line_of_file, char separator);

template<typename T>
void show_message(T message);

#endif