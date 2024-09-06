#ifndef __MID_FIELDER__
#define __MID_FIELDER__

#include "player.hpp"

class Mid_fielder : public Player
{
private:
public:
    Mid_fielder(string _name, float _score, int _price);
    void calculate_score(result _result, goals_taken_from goals_taken);
    shared_ptr<Player> make_copy();
    void print_player_data();
};
#endif