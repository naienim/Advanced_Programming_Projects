#include "goal_keeper.hpp"

Goal_keeper::Goal_keeper(string _name, float _score, int _price)
    : Player(_name, _score, _price)
{
    role = roles[GK];
}

void Goal_keeper::calculate_score(result _result, goals_taken_from goals_taken)
{
    if (goals_taken.total == 0)
        score += 5;
    else
        score -= goals_taken.total;
    Player::calculate_score(_result, goals_taken);
}

shared_ptr<Player> Goal_keeper::make_copy()
{
    shared_ptr<Goal_keeper> copy_player = make_shared<Goal_keeper>(name, 3, price);
    copy_player->goals = goals;
    copy_player->own_goals = own_goals;
    copy_player->assist = assist;
    copy_player->role_in_match = role_in_match;
    copy_player->clean_sheets = clean_sheets;
    copy_player->base_score = base_score;
    return copy_player;
}

void Goal_keeper::print_player_data()
{
    cout << " | +clean sheets: " << clean_sheets << endl;
}