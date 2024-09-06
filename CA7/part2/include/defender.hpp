#ifndef __DEFENDER__
#define __DEFENDER__

#include "player.hpp"

class Defender : public Player
{
private:
public:
    Defender(string _name, float _score, int _price);
    void calculate_score(result _result, goals_taken_from goals_taken);
    shared_ptr<Player> make_copy();
    void print_player_data();
};
#endif