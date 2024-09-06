#include "forward.hpp"

Forward::Forward(string _name, float _score, int _price)
    : Player(_name, _score, _price)
{
    role = roles[FW];
}

void Forward::calculate_score(result _result, goals_taken_from goals_taken)
{
    if (goals == 0)
        score -= 1;
    score += 3 * goals;
    score += assist;
    Player::calculate_score(_result, goals_taken);
}

shared_ptr<Player> Forward::make_copy()
{
    shared_ptr<Forward> copy_player = make_shared<Forward>(name, 0, price);
    copy_player->goals = goals;
    copy_player->own_goals = own_goals;
    copy_player->assist = assist;
    copy_player->role_in_match = role_in_match;
    copy_player->clean_sheets = clean_sheets;
    copy_player->base_score = base_score;
    return copy_player;
}

void Forward::print_player_data()
{
    cout << " | goals: " << goals << " | assists : " << assist << endl;
}