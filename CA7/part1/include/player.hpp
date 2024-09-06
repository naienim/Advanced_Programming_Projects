#ifndef __PLAYER__
#define __PLAYER__

#include "manual.hpp"

class Player
{
private:
    string name;
    string role;
    float score;
    int yellow_cards;
    int red_cards;
    float total_scors;
    int num_of_play;
public:
    Player(string _name , string _role , float _score);
    shared_ptr<Player> make_copy();
    void change_score(float new_score);
    string get_name();
    float get_score();
    float get_average_score();
    string get_role();
    int get_yellow_cards();
    void empty_yelloW_cards();
    void increase_yellow_cards();
    void update_player(float num);
    float round_number(float number);
};

#endif