#include "../include/manual.hpp"
#include "../include/question.hpp"
#include "../include/quiz.hpp"

vector<string> make_apart(string line_of_file, char separator = ' ')
{
    string file_element;
    vector<string> inputs;
    vector<string> result;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
        inputs.push_back(file_element);
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i] != "")
            result.push_back(inputs[i]);
    }
    return result;
}

template<typename T>
void show_message(T message) {
    cout << message << endl;
}

TopLevel::TopLevel() {
    answered_questions.clear();
    questions.clear();
    num_of_questions = 0;
    correct_answers = 0;
}

void TopLevel::add_single_question(ifstream &input_file, int index) {
    int ans;
    int count;
    string question;
    string line_of_file;
    vector<string> choices;
    getline(input_file, line_of_file);
    question = line_of_file;
    getline(input_file, line_of_file);
    count = stoi(line_of_file);
    for (int i = 0; i < count; i++)
    {
        getline(input_file, line_of_file);  
        choices.push_back(line_of_file);
    }
    getline(input_file, line_of_file);
    ans = stoi(line_of_file);
    questions.push_back(make_shared<SingleAnswer>(index,question,count,choices,ans));
}

void TopLevel::add_multiple_question(ifstream &input_file, int index) {
    vector<string> choices;
    vector<string> answers;
    string line_of_file;
    string question;
    int count;
    getline(input_file, line_of_file);
    question = line_of_file;
    getline(input_file, line_of_file);
    count = stoi(line_of_file);
    for (int i = 0; i < count; i++)
    {
        getline(input_file, line_of_file);  
        choices.push_back(line_of_file);
    }
    getline(input_file, line_of_file);
    answers = make_apart(line_of_file, SEPARATOR);
    questions.push_back(make_shared<MultipleAnswer>(index,question,count,choices,answers));
}

void TopLevel::add_short_question(ifstream &input_file, int index) {
    string line_of_file;
    string question;
    string ans;
    getline(input_file, line_of_file);
    question = line_of_file;
    getline(input_file, line_of_file);
    ans = line_of_file;
    questions.push_back(make_shared<ShortAnswer>(index,question,ans));
}

void TopLevel::get_questions_from_file(string file_name) {
    int index = 1;
    ifstream input_file(file_name);
    string line_of_file;
    while (getline(input_file, line_of_file))
    {
        if (line_of_file == questions_type[SINGLE])
            add_single_question(input_file,index);
        else if (line_of_file == questions_type[MULTIPLE])
            add_multiple_question(input_file,index);
        else if (line_of_file == questions_type[SHORT])
            add_short_question(input_file,index);
        else
            continue;
        num_of_questions++;
        index++;
    }
    input_file.close();
}

void TopLevel::check_answer(vector<string> inputs) {
    int index = stoi(inputs[1]) - 1;
    int situation = NO_ANSWER;
    if (index >= questions.size() || index <= -1)
        throw runtime_error("question not exist");
    if (answered_questions.find(index) == answered_questions.end())
    {
        answered_questions.insert(index);
        situation = questions[index]->check_answer(inputs);
        if (situation == CORRECT)
            correct_answers++;
        show_message<string>(situations_msg[situation]);
    }
}

void TopLevel::get_quiz()
{
    string line;
    vector<string> inputs;
    while (getline(cin, line)) {
        try
        {
            inputs = make_apart(line, SEPARATOR);
            if (inputs.size() == 0)
                continue;
            else if (inputs[0] == commands[SUBMIT])
                check_answer(inputs);
            else if (inputs[0] == commands[FINISH])
                break;

            if (answered_questions.size() == num_of_questions)
                break;
        }
        catch(const exception& e)
        {
            show_message(e.what());
        }
    }
}

string TopLevel::get_final_grade() {
    float final_grade = (float(correct_answers) / num_of_questions) * 100;
    final_grade = float(int(final_grade * 10)) / 10;
    ostringstream result;
    result << fixed << setprecision(1) << FINAL_GRADE_MSG << " " << final_grade;
    return result.str();
}

void TopLevel::show_result_of_exam() {
    string message = "";
    for (int i = 0; i < questions.size(); i++)
    {
        message = questions[i]->get_result();
        show_message<string>(message);
    }
    message = get_final_grade();
    show_message<string>(message);
}