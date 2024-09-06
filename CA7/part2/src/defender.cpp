#include "defender.hpp"

Defender::Defender(string _name, float _score, int _price)
    : Player(_name, _score, _price)
{
    role = roles[DF];
}

void Defender::calculate_score(result _result, goals_taken_from goals_taken)
{
    if (goals_taken.total)
        score += 2;
    score += 4 * goals;
    score += 3 * assist;
    if (role_in_match == DF_LEFT)
        score -= goals_taken.right;
    else if (role_in_match == DF_RIGHT)
        score -= goals_taken.left;
    else
        score -= goals_taken.mid;
    Player::calculate_score(_result, goals_taken);
}

shared_ptr<Player> Defender::make_copy()
{
    shared_ptr<Defender> copy_player = make_shared<Defender>(name, 1, price);
    copy_player->goals = goals;
    copy_player->own_goals = own_goals;
    copy_player->assist = assist;
    copy_player->role_in_match = role_in_match;
    copy_player->clean_sheets = clean_sheets;
    copy_player->base_score = base_score;
    return copy_player;
}

void Defender::print_player_data()
{
    cout << " | goals: " << goals << " | assists : " << assist << " | +clean sheets: " << clean_sheets << endl;
}