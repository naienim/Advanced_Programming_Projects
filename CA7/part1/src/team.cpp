#include "../include/team.hpp"

Team::Team(string _name, float _score) : name(_name), score(_score)
{
    total_score = 0;
    players.clear();
}

float Team::get_total_score_of_team()
{
    return total_score;
}

void Team::add_player(string _player_name, string _role, float _score)
{
    players.push_back(make_shared<Player>(_player_name, _role, _score));
}

void Team::update_total_score(float num)
{
    total_score += num;
}

string Team::get_name()
{
    return name;
}

shared_ptr<Team> Team::make_copy()
{
    shared_ptr<Team> copy_of_team = make_shared<Team>(name, score);
    for (int i = 0; i < players.size(); i++)
    {
        copy_of_team->players.push_back(players[i]->make_copy());
    }
    return copy_of_team;
}

shared_ptr<Player> Team::find_player_by_name(string name)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (name == players[i]->get_name())
            return players[i];
    }
    return NULL;
}

void Team::update_players_scores(vector<shared_ptr<Player>> list)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = 0; j < list.size(); j++)
        {
            if (players[i]->get_name() == list[j]->get_name())
                players[i]->change_score(list[j]->get_score());
        }
    }
}

shared_ptr<Player> Team::find_player_from_list(string name, vector<shared_ptr<Player>> list, string player_role)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->get_name() == name && (player_role == list[i]->get_role() || player_role == NOTHING) && list[i]->get_name().length() > 1)
            return list[i];
    }
    return NULL;
}

bool can_sort_by_score(shared_ptr<Player> first, shared_ptr<Player> second)
{
    return second->get_average_score() > first->get_average_score() ||
           (second->get_average_score() == first->get_average_score() && second->get_name() < first->get_name());
}

bool can_sort_by_name(shared_ptr<Player> first, shared_ptr<Player> second)
{
    return second->get_name() < first->get_name();
}

vector<shared_ptr<Player>> Team::sort_list_of_players(vector<shared_ptr<Player>> list, bool (*func)(shared_ptr<Player>, shared_ptr<Player>))
{
    shared_ptr<Player> temp;
    for (int i = 0; i < list.size() - 1; i++)
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            if (func(list[i], list[j]))
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return list;
}

vector<shared_ptr<Player>> Team::find_list_of_playyers_for_print(vector<shared_ptr<Player>> list, bool rank, string player_role)
{
    shared_ptr<Player> temp;
    vector<shared_ptr<Player>> new_list;
    for (int i = 0; i < players.size(); i++)
    {
        temp = find_player_from_list(players[i]->get_name(), list, player_role);
        if (temp != NULL)
            new_list.push_back(temp);
    }
    if (rank)
        new_list = sort_list_of_players(new_list, can_sort_by_score);
    else
        new_list = sort_list_of_players(new_list, can_sort_by_name);
    return new_list;
}

void Team::print_players(vector<shared_ptr<Player>> list, bool rank, string player_role)
{
    int flag = 1;
    vector<shared_ptr<Player>> new_list;
    for (int i = 0; i < roles.size(); i++)
        if (player_role == roles[i])
            flag = 0;
    if (flag && player_role != NOTHING)
    {
        throw Bad_Request();
    }
    new_list = find_list_of_playyers_for_print(list, rank, player_role);
    cout << "list of players:" << endl;
    for (int i = 0; i < new_list.size(); i++)
    {
        cout << i + 1 << ". name: " << new_list[i]->get_name() << " | role: " << new_list[i]->get_role();
        if (new_list[i]->get_average_score() != 0)
            cout << " | score: " << new_list[i]->get_average_score() << endl;
        else
            cout << " | score: "
                 << "0.0" << endl;
    }
}
