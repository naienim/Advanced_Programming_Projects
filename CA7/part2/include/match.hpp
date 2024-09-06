#ifndef __MATCH__
#define __MATCH__

#include "manual.hpp"
#include "team.hpp"

vector<string> make_apart(string line_of_file, char separator);

struct Goals
{
    int goals_for;
    int goals_against;
};

class Match
{
private:
    pair<shared_ptr<Team>, Goals> team1;
    pair<shared_ptr<Team>, Goals> team2;
    vector<shared_ptr<Player>> composition_of_team1;
    vector<shared_ptr<Player>> composition_of_team2;
    vector<shared_ptr<Player>> injuredes;
    vector<shared_ptr<Player>> yellow_cards;
    vector<shared_ptr<Player>> red_cards;
    vector<shared_ptr<Player>> players;
    void calculate_team_scores(pair<shared_ptr<Team>, Goals> _team1, pair<shared_ptr<Team>, Goals> _team2,
                          vector<shared_ptr<Player>> &_composition_of_team1, vector<shared_ptr<Player>> _composition_of_team2);

public:
    Match(shared_ptr<Team> t1, int gf1, int ga1, shared_ptr<Team> t2, int gf2, int ga2);
    shared_ptr<Player> find_player_by_name(string name);
    shared_ptr<Player> find_player_from_list(string name);
    vector<shared_ptr<Player>> add_players_to_each_list(vector<string> names, vector<shared_ptr<Player>> list);
    void find_goals(vector<string> inputs);
    void merge_all_players();
    void add_players(vector<string> inputs);
    bool have_this_situation(shared_ptr<Player> new_player, string situ);
    void print_match_result_league();
    string make_team_name(string name);
    bool have_this_team(string team_name);
    float find_score_of_this_team(string team_name);
    void update_num_of_goals(shared_ptr<Goals> num_goals, string team_name);
    void calculate_both_teams_scores();
    vector<shared_ptr<Player>> get_players();
};

#endif