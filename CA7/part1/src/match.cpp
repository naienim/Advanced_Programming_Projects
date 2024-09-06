#include "../include/match.hpp"

vector<string> make_apart(string line_of_file , char separator)
{
    string file_element;
    vector<string> inputs;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator)) 
    {
        inputs.push_back(file_element);
    }
    return inputs;
}

Match::Match(shared_ptr<Team> t1 , int gf1 , int ga1 , shared_ptr<Team> t2 , int gf2 , int ga2)
{
    team1.first = t1;
    team1.second.goals_for = gf1;
    team1.second.goals_against = ga1;
    team2.first = t2;
    team2.second.goals_for = gf2;
    team2.second.goals_against = ga2;
    injuredes.clear();
    yellow_cards.clear();
    red_cards.clear();
    players.clear();
}

shared_ptr<Player> Match::find_player_by_name(string name)
{
    shared_ptr<Player> temp = team1.first->find_player_by_name(name);
    if (temp == NULL)
        temp = team2.first->find_player_by_name(name);
    return temp;
}

shared_ptr<Player> Match::find_player_from_list(string name)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (name == players[i]->get_name())
            return players[i];
    }
    return NULL;
}

vector<shared_ptr<Player>> Match::add_players_to_each_list(vector<string> names , vector<shared_ptr<Player>> list)
{
    for (int i = 0; i < names.size(); i++)
        list.push_back(find_player_from_list(names[i]));
    return list;
}

void Match::add_players(vector<string> inputs)
{
    vector<string> player_and_score;
    shared_ptr<Player> temp;
    vector<string> name_of_players = make_apart(inputs[5],SEPARATOR2);
    for (int i = 0; i < name_of_players.size(); i++)
    {
        player_and_score = make_apart(name_of_players[i],SEPARATOR3);
        temp = find_player_by_name(player_and_score[0]);
        players.push_back(temp->make_copy());
        players[i]->change_score(stof(player_and_score[1]));
    }
    injuredes = add_players_to_each_list(make_apart(inputs[2],SEPARATOR2),injuredes);
    yellow_cards = add_players_to_each_list(make_apart(inputs[3],SEPARATOR2),yellow_cards);
    red_cards = add_players_to_each_list(make_apart(inputs[4],SEPARATOR2),red_cards);
    team1.first->update_players_scores(players);
    team2.first->update_players_scores(players);
}

bool Match::have_this_situation(shared_ptr<Player> new_player , string situ)
{
    if (situ == situation[RED])
    {
        for (int i = 0; i < red_cards.size(); i++)
            if(new_player->get_name() == red_cards[i]->get_name())
                return true;
        return false;
    }
    else if (situ == situation[YELLOW])
    {
        for (int i = 0; i < yellow_cards.size(); i++)
            if(new_player->get_name() == yellow_cards[i]->get_name())
                return true;
        return false;
    }
    else if (situ == situation[INJURED])
    {
        for (int i = 0; i < injuredes.size(); i++)
            if(new_player->get_name() == injuredes[i]->get_name())
                return true;
        return false;
    }
    return false;
}

string Match::make_team_name(string name)
{
    string new_name = "";
    vector<string> names = make_apart(name,SEPARATOR4);
    for (int i = 0; i < names.size(); i++)
    {
        new_name = new_name + names[i];
        if (i != names.size()-1)
            new_name = new_name + " ";
    }
    return new_name;
}

void Match::print_match_result_league()
{
    cout << make_team_name(team1.first->get_name()) << " " << team1.second.goals_for << " | ";
    cout << make_team_name(team2.first->get_name()) << " " << team2.second.goals_for << endl;
}

bool Match::have_this_team(string team_name)
{
    if(team1.first->get_name() == team_name)
        return true;
    else if(team2.first->get_name() == team_name)
        return true;
    return false;
}

float Match::find_score_of_this_team(string team_name)
{
    if(team1.first->get_name() == team_name)
    {
        if(team1.second.goals_for > team1.second.goals_against)
            return 3;
        else if(team1.second.goals_for == team1.second.goals_against)
            return 1;
        else 
            return 0;
    }
    else if(team2.first->get_name() == team_name)
    {
        if(team2.second.goals_for > team2.second.goals_against)
            return 3;
        else if(team2.second.goals_for == team2.second.goals_against)
            return 1;
        else 
            return 0;
    }
    return 0;
}

void Match::update_num_of_goals(shared_ptr<Goals> num_goals , string team_name)
{
    if(team1.first->get_name() == team_name)
    {
        num_goals->goals_for += team1.second.goals_for;
        num_goals->goals_against += team1.second.goals_against;
    }
    else if(team2.first->get_name() == team_name)
    {
        num_goals->goals_for += team2.second.goals_for;
        num_goals->goals_against += team2.second.goals_against;
    }
}

vector<shared_ptr<Player>> Match::get_players()
{
    return players;
}


