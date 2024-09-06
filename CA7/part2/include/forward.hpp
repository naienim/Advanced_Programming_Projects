#ifndef __FORWARD__
#define __FORWARD__

#include "player.hpp"

class Forward : public Player
{
private:
public:
    Forward(string _name, float _score, int _price);
    void calculate_score(result _result, goals_taken_from goals_taken);
    shared_ptr<Player> make_copy();
    void print_player_data();
};
#endif