#ifndef __TEAM__
#define __TEAM__

#include "manual.hpp"
#include "player.hpp"
#include "goal_keeper.hpp"
#include "defender.hpp"
#include "mid_fielder.hpp"
#include "forward.hpp"
#include "errors.hpp"
#include <iomanip>

bool can_sort_by_score(shared_ptr<Player> first , shared_ptr<Player> second);
bool can_sort_by_name(shared_ptr<Player> first , shared_ptr<Player> second);
string correct_string(string str);

class Team
{
protected:
    string name;
    vector<shared_ptr<Player>> players;
    float score;
    float total_score;
public:
    Team(string _name , float _score);
    float get_total_score_of_team();
    void add_player(shared_ptr<Player> _player);
    void update_total_score(float num);
    string get_name();
    shared_ptr<Team> make_copy();
    shared_ptr<Player> find_player_by_name(string name);
    void update_players_scores(vector<shared_ptr<Player>> list);
    shared_ptr<Player> find_player_from_list(string name , vector<shared_ptr<Player>> list , string player_role);
    vector<shared_ptr<Player>> sort_list_of_players(vector<shared_ptr<Player>> list , bool (*func)(shared_ptr<Player>, shared_ptr<Player>));
    vector<shared_ptr<Player>> find_list_of_playyers_for_print(vector<shared_ptr<Player>> list , bool rank , string player_role);
    void print_players(vector<shared_ptr<Player>> list , bool rank , string player_role);
};

#endif