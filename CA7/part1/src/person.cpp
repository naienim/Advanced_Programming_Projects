#include "../include/person.hpp"

Person::Person(string _user, string _pass) : user_name(_user), password(_pass) {}

Admin::Admin(string _user, string _pass) : Person(_user, _pass)
{
    login = false;
}

void Admin::change_log(bool cond)
{
    login = cond;
}

bool Admin::is_login()
{
    return login;
}

bool Admin::check_id(string name, string pass)
{
    return user_name == name && password == pass;
}

User::User(string _user, string _pass, shared_ptr<MyTeam> t) : Person(_user, _pass)
{
    num_of_sell = 0;
    num_of_buy = 0;
    start = false;
    score = 0;
    my_team = t;
}

shared_ptr<User> User::make_copy()
{
    shared_ptr<MyTeam> temp = my_team->make_copy_of_my_team();
    shared_ptr<User> copy_of_user = make_shared<User>(user_name, password, temp);
    copy_of_user->num_of_sell = num_of_sell;
    copy_of_user->num_of_buy = num_of_buy;
    copy_of_user->start = start;
    copy_of_user->score = score;
    return copy_of_user;
}

string User::get_name()
{
    return user_name;
}

float User::get_score()
{
    return score;
}

bool User::check_password(string pass)
{
    return pass == password;
}

void User::sell_player(string name)
{
    bool status;
    if (start && num_of_sell == 2)
    {
        throw Permission_Denied();
    }
    status = my_team->sell_player(name);
    if (status)
    {
        num_of_sell++;
        print(OK);
        return;
    }
    else
        throw Not_Found();
}

void User::buy_player(shared_ptr<Player> new_player)
{
    if (start && num_of_buy == 2)
    {
        throw Permission_Denied();
    }
    if (my_team->buy_player(new_player))
    {
        num_of_buy++;
        print(OK);
    }
    else
        throw Bad_Request();
    return;
}

bool User::is_my_team_complete()
{
    return my_team->is_complete();
}

void User::print_squad()
{
    cout << "fantasy_team: " << user_name << endl;
    my_team->print_players();
    cout << "Total Points: " << score << endl;
}

void User::update_user(vector<shared_ptr<Week>> weeks, int week_index, vector<shared_ptr<Player>> list_players)
{
    num_of_sell = 0;
    num_of_buy = 0;
    if (my_team->is_complete())
        start = true;
    else
        return;
    score = score + my_team->find_scores(weeks, week_index, list_players);
}
