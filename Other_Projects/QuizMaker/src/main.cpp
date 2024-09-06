#include "../include/manual.hpp"
#include "../include/question.hpp"
#include "../include/quiz.hpp"

//Assumption 1:
// If a question is answered more than once, only the first answer will be considered 
// and the rest will be ignored and no message will be printed for them.

//Assumption 2:
// If the user answers a question that does not exist, 
// the message "question not exist" will be printed for him/her


int main(int argc, char *argv[]) {
    shared_ptr<TopLevel> quiz = make_shared<TopLevel>();
    if (argc > 1) {
        quiz->get_questions_from_file(argv[1]);
        quiz->get_quiz();
        quiz->show_result_of_exam();
    }
    else {
        exit(EXIT_FAILURE);
    }
}
