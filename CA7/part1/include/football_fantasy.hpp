#ifndef __football_fantasy__
#define __football_fantasy__

#include "manual.hpp"
#include "person.hpp"
#include "errors.hpp"

class FootballFantasy
{
private:
    vector<shared_ptr<Team>> teams;
    vector<pair<shared_ptr<Team>,shared_ptr<Goals>>> result_of_teams;
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Week>> weeks;
    int week_index;
    vector<shared_ptr<User>> users;
    vector<shared_ptr<User>> pre_users;
    shared_ptr<User> current_user;
    shared_ptr<Admin> admin;
    bool transfer_condition;
    string correct_string(string str);
    string  make_address(string folder_name , string file_name);
    string make_team_name(string name , char seprator , string mach_word);
    string make_player_name(vector<string> inputs);
    void add_teams_to_result_of_teams();
    void find_players_of_team(shared_ptr<Team> new_team , vector<string> inputs);
    shared_ptr<Team> find_team_by_name(string team_name);
    shared_ptr<Player> find_player_by_name(string player_name);
    void find_maches(string folder_name , string file_name , int index);
    bool is_login();
    shared_ptr<User> find_user_by_name(string name);
    shared_ptr<User> find_from_pre_users(string name);
    void change_transfer_window(bool con);
    void pass_week();
    void signup(vector<string> inputs);
    void login(vector<string> inputs);
    void register_admin(vector<string> inputs);
    void logout();
    void sell_player(vector<string> inputs);
    bool is_available_for_next_week(shared_ptr<Player> new_player);
    void buy_player(vector<string> inputs);
    void get_squad(vector<string> inputs);
    vector<shared_ptr<User>> sort_users();
    void print_users_ranking();
    void print_matches_result_league(vector<string> inputs);
    void sort_league_teams();
    void print_league_standings();
    void print_team_of_the_week(vector<string> inputs);
    void print_players(vector<string> inputs);
public:
    FootballFantasy();
    void get_teams_from_file(string folder_name , string file_name);
    void get_weeks_from_file(string folder_name , string file_name , int num_of_weeks);
    void handle_post_commands(vector<string> inputs);
    void handle_get_commands(vector<string> inputs);
    void handle_put_commands(vector<string> inputs);
    void handle_delete_commands(vector<string> inputs);
};

#endif