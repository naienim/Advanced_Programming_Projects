#include "mid_fielder.hpp"

Mid_fielder::Mid_fielder(string _name, float _score, int _price)
    : Player(_name, _score, _price)
{
    role = roles[MD];
}

void Mid_fielder::calculate_score(result _result, goals_taken_from goals_taken)
{
    if (goals_taken.total == 0)
        score += 1;
    score += 3 * goals;
    score += 2 * assist;
    score -= goals_taken.mds;
    Player::calculate_score(_result, goals_taken);
}

shared_ptr<Player> Mid_fielder::make_copy()
{
    shared_ptr<Mid_fielder> copy_player = make_shared<Mid_fielder>(name, 0, price);
    copy_player->goals = goals;
    copy_player->own_goals = own_goals;
    copy_player->assist = assist;
    copy_player->role_in_match = role_in_match;
    copy_player->clean_sheets = clean_sheets;
    copy_player->base_score = base_score;
    return copy_player;
}

void Mid_fielder::print_player_data()
{
    cout << " | goals: " << goals << " | assists : " << assist << " | +clean sheets: " << clean_sheets << endl;
}
