#ifndef __QUESTION__
#define __QUESTION__

#include "manual.hpp"

class Question {
protected:
    int index;
    string question;
    int situation;
public:
    Question(int _index, string _question);
    virtual int check_answer(vector<string> inputs) = 0;
    virtual string get_result() = 0;
};

class SingleAnswer : public Question {
private:
    int choices_count;
    vector<string> choices;
    int answer;
    int my_answer;
public:
    SingleAnswer(int init_idx, string init_ques, int init_count, vector<string> init_choices, int init_ans);
    virtual int check_answer(vector<string> inputs);
    virtual string get_result();
};

class MultipleAnswer : public Question {
private:
    int choices_count;
    vector<string> choices;
    vector<string> answers;
    vector<string> my_answers;
public:
    MultipleAnswer(int init_idx, string init_ques, int init_count, vector<string> init_choices, vector<string> init_ans);
    bool is_equal(vector<string> first, vector<string> second);
    string vector_to_str(vector<string> vect);
    virtual int check_answer(vector<string> inputs);
    virtual string get_result();
};

class ShortAnswer : public Question {
private:
    string answer;
    string my_answer;    
public:
    ShortAnswer(int init_idx, string init_ques, string init_ans);
    virtual int check_answer(vector<string> inputs);
    virtual string get_result();
};

#endif