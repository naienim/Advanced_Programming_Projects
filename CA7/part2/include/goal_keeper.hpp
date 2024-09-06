#ifndef __GOAL_KEEPER__
#define __GOAL_KEEPER__

#include "player.hpp"

class Goal_keeper : public Player
{
private:
public:
    Goal_keeper(string _name, float _score, int _price);
    void calculate_score(result _result, goals_taken_from goals_taken);
    shared_ptr<Player> make_copy();
    void print_player_data();
};
#endif