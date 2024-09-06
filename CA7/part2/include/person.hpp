#ifndef __PERSON__
#define __PERSON__

#include "manual.hpp"
#include "week.hpp"
#include "errors.hpp"

class Person
{
protected:
    string user_name;
    string password;
public:
    Person(string _user , string _pass);
};

class Admin : public Person
{
private:
    bool login;
public:
    Admin(string _user , string _pass);
    void change_log(bool cond);
    bool is_login();
    bool check_id(string name , string pass);
};

class User : public Person
{
private:
    shared_ptr<MyTeam> my_team;
    shared_ptr<Player> captain;
    int num_of_sell;
    int num_of_buy;
    bool start;
    float score;
    int budget;
public:
    User(string _user , string _pass , shared_ptr<MyTeam> t);
    shared_ptr<User> make_copy();
    string get_name();
    float get_score();
    int get_budget();
    bool check_password(string pass);
    void sell_player(string name);
    void buy_player(shared_ptr<Player> new_player);
    void set_captain(string name);
    bool is_my_team_complete();
    void print_squad();
    void update_user(vector<shared_ptr<Week>> weeks , int week_index ,vector<shared_ptr<Player>> list_players);
};

#endif