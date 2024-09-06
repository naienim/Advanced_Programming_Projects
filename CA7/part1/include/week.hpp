#ifndef __WEEK__
#define __WEEK__

#include "manual.hpp"
#include "match.hpp"

class Week
{
private:
    vector<shared_ptr<Match>> matches;
public:
    Week();
    void add_match(shared_ptr<Match> new_match);
    void add_players(int index , vector<string> inputs);
    bool have_this_situation(shared_ptr<Player> new_player , string situation);
    float find_score_of_player(string new_name);
    void print_matches_result_league();
    float find_score_of_team(string team_name);
    void update_goals(shared_ptr<Goals> num_goals , string team_name);
    vector<shared_ptr<Player>> merge_players();
    shared_ptr<Player> find_best_player(string situ , vector<shared_ptr<Player>> players);
    shared_ptr<Player> find_second_best_player(string situ , vector<shared_ptr<Player>> players , shared_ptr<Player> new_player);
    vector<shared_ptr<Player>> find_best_players_of_week();
    void print_team_of_week();
};

class MyTeam : public Team
{
public:
    MyTeam(string _name , float _score);
    shared_ptr<MyTeam> make_copy_of_my_team();
    bool sell_player(string name);
    bool buy_player(shared_ptr<Player> new_player);
    bool is_complete();
    vector<string> find_players_name();
    void print_players();
    bool is_available_for_thist_week(shared_ptr<Player> new_player , vector<shared_ptr<Week>> weeks , int week_index , vector<shared_ptr<Player>> list_players);
    float find_scores(vector<shared_ptr<Week>> weeks , int week_index , vector<shared_ptr<Player>> list_players);
};

#endif