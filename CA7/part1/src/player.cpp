#include "../include/player.hpp"

Player::Player(string _name , string _role , float _score) 
      : name(_name) , role(_role) , score(_score) 
{
    yellow_cards = 0;
    red_cards = 0;
    total_scors = 0;
    num_of_play = 0;
}

shared_ptr<Player> Player::make_copy()
{
    return make_shared<Player>(name,role,score);
}

void Player::change_score(float new_score)
{
    score = new_score;
}

string Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}

float Player::get_score()
{
    return score;
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
    if(yellow_cards >= 3)
        yellow_cards = 0;
    if (num > 0)
    {
        num_of_play++;
        total_scors += num;
    }
}

float Player::round_number(float number)
{
    float value = (int)(number * 10 + 0.5);
    return (float)value / 10;
}

float Player::get_average_score()
{
    if(total_scors == 0 || num_of_play == 0)
        return 0;
    return round_number(total_scors/num_of_play);
}
