#include "../include/manual.hpp"
#include "../include/question.hpp"

Question::Question(int init_idx, string init_ques): index(init_idx), question(init_ques) {
    situation = NO_ANSWER;
}


SingleAnswer::SingleAnswer(int init_idx, string init_ques, int init_count, vector<string> init_choices, int init_ans) 
            : Question(init_idx,init_ques), choices_count(init_count), choices(init_choices), answer(init_ans) {
    my_answer = -1;
}

int SingleAnswer::check_answer(vector<string> inputs)
{
    my_answer = stoi(inputs[answers_start_index]);
    if (my_answer == answer)
        situation = CORRECT;
    else
        situation = WRONG;
    return situation;
}

string SingleAnswer::get_result() {
    ostringstream result;
    result << index << " " << situations[situation];
    if (situation == WRONG) {
        result << " | " << CORRECT_ANSWER << " " << answer << ", " << YOUR_ANSWER << " " << my_answer;
    }
    else if (situation == NO_ANSWER) {
        result << " | " << CORRECT_ANSWER << " " << answer;
    }
    return result.str();
}


MultipleAnswer::MultipleAnswer(int init_idx, string init_ques, int init_count, vector<string> init_choices, vector<string> init_ans) 
            : Question(init_idx,init_ques), choices_count(init_count), choices(init_choices), answers(init_ans) {
    my_answers.clear();
}

bool MultipleAnswer::is_equal(vector<string> first, vector<string> second)
{
    if (first.size() != second.size())
        return false;
 
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    return first == second;
}

int MultipleAnswer::check_answer(vector<string> inputs)
{
    my_answers.clear();
    for (int i = answers_start_index; i < inputs.size(); i++)
        my_answers.push_back(inputs[i]);

    if (is_equal(my_answers, answers))
        situation = CORRECT;
    else
        situation = WRONG;
    return situation;
}

string MultipleAnswer::vector_to_str(vector<string> vect) {
    ostringstream result;
    for (int i = 0; i < vect.size(); i++)
    {
        result << " " << vect[i];
    }
    return result.str();
}

string MultipleAnswer::get_result() {
    string my_ans = "";
    ostringstream result;
    string correct_ans = vector_to_str(answers);
    result << index << " " << situations[situation];
    if (situation == WRONG) {
        my_ans = vector_to_str(my_answers);
        result << " | " << CORRECT_ANSWER << correct_ans << ", " << YOUR_ANSWER << my_ans;
    }
    else if (situation == NO_ANSWER) {
        result << " | " << CORRECT_ANSWER << correct_ans;
    }
    return result.str();
}


ShortAnswer::ShortAnswer(int init_idx, string init_ques, string init_ans) 
            : Question(init_idx,init_ques), answer(init_ans) {
    my_answer = "";
}

int ShortAnswer::check_answer(vector<string> inputs)
{
    my_answer = inputs[answers_start_index];
    if (my_answer == answer)
        situation = CORRECT;
    else
        situation = WRONG;
    return situation;
}

string ShortAnswer::get_result() {
    ostringstream result;
    result << index << " " << situations[situation];
    if (situation == WRONG) {
        result << " | " << CORRECT_ANSWER << " " << answer << ", " << YOUR_ANSWER << " " << my_answer;
    }
    else if (situation == NO_ANSWER) {
        result << " | " << CORRECT_ANSWER << " " << answer;
    }
    return result.str();
}




