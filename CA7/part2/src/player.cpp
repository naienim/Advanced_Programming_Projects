#include "../include/player.hpp"
#include "player.hpp"

Player::Player(string _name, float _score, int _price)
    : name(_name), score(_score), price(_price)
{
    yellow_cards = 0;
    red_cards = 0;
    total_scores = 0;
    num_of_play = 0;
    goals = 0;
    own_goals = 0;
    assist = 0;
    clean_sheets = 0;
}

void Player::calculate_score(result _result, goals_taken_from goals_taken)
{
    switch (_result)
    {
    case WON:
        score += 5;
        break;
    case TIED:
        score += 1;
        break;
    case LOST:
        score -= 1;
        break;

    default:
        break;
    }
    if (goals_taken.total == 0)
        clean_sheets++;
    score -= 3 * own_goals;
    base_score = score;
    score = (int)((float)10.f / (1.f + exp(-score / 6.f)));
}

void Player::change_score(float new_score)
{
    score = new_score;
}

string Player::get_role()
{
    return role;
}

int Player::get_goals()
{
    return goals;
}

int Player::get_price()
{
    return price;
}

string Player::get_name()
{
    return name;
}

float Player::get_score()
{
    return score;
}

float Player::get_base_score()
{
    return base_score;
}

int Player::get_yellow_cards()
{
    return yellow_cards;
}

void Player::empty_yelloW_cards()
{
    yellow_cards = 0;
}

void Player::increase_yellow_cards()
{
    yellow_cards++;
}

void Player::update_player(float num)
{
    if (yellow_cards >= 3)
        yellow_cards = 0;
    if (num > 0)
    {
        num_of_play++;
        total_scores += num;
    }
}

/* float Player::round_number(float number)
{
    float value = (int)(number * 10.f + 0.5f);
    return (float)value / 10.f;
} */

int Player::get_average_score()
{
    if (total_scores == 0.f || num_of_play == 0.f)
        return 0;
    return (int)(total_scores / num_of_play);
}

void Player::increase_num_of_element(string element)
{
    if (element == name_of_elements[GOALS_TO])
        goals++;
    else if (element == name_of_elements[OWN_GOAL])
        own_goals++;
    else if (element == name_of_elements[ASSIST])
        assist++;
}

void Player::set_role_in_match(roles_in_playground _role)
{
    role_in_match = _role;
}
