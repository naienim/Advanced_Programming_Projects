#include "../include/week.hpp"

Week::Week()
{
    matches.clear();
}

void Week::add_match(shared_ptr<Match> new_match)
{
    matches.push_back(new_match);
}

void Week::add_players(int index , vector<string> inputs)
{
    matches[index]->add_players(inputs);
}

bool Week::have_this_situation(shared_ptr<Player> new_player , string situ)
{
    for (int i = 0; i < matches.size(); i++)
        if(matches[i]->have_this_situation(new_player,situ))
            return true;
    return false;
}

float Week::find_score_of_player(string new_name)
{
    shared_ptr<Player> temp;
    for (int i = 0; i < matches.size(); i++)
    {
        temp = matches[i]->find_player_from_list(new_name);
        if (temp != NULL)
            return temp->get_score();
    }
    return 0;
}

void Week::print_matches_result_league()
{
    for (int i = 0; i < matches.size(); i++)
    {
        matches[i]->print_match_result_league();
    }
}

float Week::find_score_of_team(string team_name)
{
    for (int i = 0; i < matches.size(); i++)
    {
        if(matches[i]->have_this_team(team_name))
            return matches[i]->find_score_of_this_team(team_name);
    }
    return 0;
}

void Week::update_goals(shared_ptr<Goals> num_goals , string team_name)
{
    for (int i = 0; i < matches.size(); i++)
    {
        if(matches[i]->have_this_team(team_name))
        {
            matches[i]->update_num_of_goals(num_goals,team_name);
            return;
        }
    }
}

vector<shared_ptr<Player>> Week::merge_players()
{
    int new_size = 0;
    vector<shared_ptr<Player>> temp;
    for (int i = 0; i < matches.size(); i++)
    {
        temp = matches[i]->get_players();
        new_size += temp.size();
    }
    vector<shared_ptr<Player>> merged;
    merged.reserve(new_size);
    for (int i = 0; i < matches.size(); i++)
    {
        temp = matches[i]->get_players();
        merged.insert(merged.end(), temp.begin(), temp.end());
    }
    return merged;
}   

shared_ptr<Player> Week::find_best_player(string situ , vector<shared_ptr<Player>> players)
{
    shared_ptr<Player> temp;
    float max = 0;
    string name = "";
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_role() == situ && (players[i]->get_score() > max || (players[i]->get_score() == max && players[i]->get_name() > name)))
        {
            temp = players[i];
            max = players[i]->get_score();
            name = players[i]->get_name();
        }
    }
    return temp;
}

shared_ptr<Player> Week::find_second_best_player(string situ , vector<shared_ptr<Player>> players , shared_ptr<Player> new_player)
{
    
    shared_ptr<Player> temp;
    string name = "";
    float max = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_name() == new_player->get_name())
            continue;
        else if (players[i]->get_role() == situ && (players[i]->get_score() > max || (players[i]->get_score() == max && players[i]->get_name() > name)))
        {
            temp = players[i];
            max = players[i]->get_score();
            name = players[i]->get_name();
        }
    }
    return temp;
    
}

vector<shared_ptr<Player>> Week::find_best_players_of_week()
{
    enum my_team_roles {GK_MT , DF_MT1 , DF_MT2 , MD_MT , FW_MT};
    vector<string> name_of_roles = {"gk" , "df" , "df" , "md" , "fw"};
    vector<shared_ptr<Player>> players = merge_players();
    vector<shared_ptr<Player>> best_players(5);
    shared_ptr<Player> temp;
    for (int i = 0; i < 5; i++)
    {
        if(i == DF_MT2)
            best_players[i] = find_second_best_player(name_of_roles[i],players,best_players[i-1]);
        else
            best_players[i] = find_best_player(name_of_roles[i],players);
    }
    if(best_players[DF_MT2]->get_name() < best_players[DF_MT1]->get_name())
    {
        temp = best_players[DF_MT2];
        best_players[DF_MT2] = best_players[DF_MT1];
        best_players[DF_MT1] = temp;
    }
    return best_players;
}

void Week::print_team_of_week()
{
    vector<string> name_of_roles = {"Goalkeeper" , "Defender 1" , "Defender 2" , "Midfielder" , "Forward"};
    vector<shared_ptr<Player>> best_players = find_best_players_of_week();
    for (int i = 0; i < best_players.size(); i++)
    {
        cout << name_of_roles[i] << ": " << best_players[i]->get_name() << " | score: " << best_players[i]->get_score() << endl;
    }
}

MyTeam::MyTeam(string _name , float _score) : Team(_name,_score) {}

shared_ptr<MyTeam> MyTeam::make_copy_of_my_team()
{
    shared_ptr<MyTeam> copy_of_team = make_shared<MyTeam>(name,score);
    for (int i = 0; i < players.size(); i++)
    {
        copy_of_team->players.push_back(players[i]->make_copy());
    }
    return copy_of_team;
}

bool MyTeam::sell_player(string name)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_name() == name)
        {
            players.erase(players.begin() + i);
            return true;
        }
    }
    return false;
}


bool MyTeam::buy_player(shared_ptr<Player> new_player)
{
    for (int i = 0; i < players.size(); i++)
        if (players[i]->get_name() == new_player->get_name()) 
            return false;
    int sum = 0;
    for (int i = 0; i < players.size(); i++)
        if (players[i]->get_role() == roles[DF]) 
            sum++;
    if(new_player->get_role() == roles[DF] && sum == NUM_OF_DEFENDER)
        return false;
    for (int i = 0; i < players.size(); i++)
        if (players[i]->get_role() == new_player->get_role() && players[i]->get_role() != roles[DF]) 
            return false;
    players.push_back(new_player->make_copy());
    return true;
}

bool MyTeam::is_complete()
{
    return players.size() == 5;
}

vector<string> MyTeam::find_players_name()
{
    int sum = 0;
    string temp;
    enum my_team_roles {GK_MT , DF_MT1 , DF_MT2 , MD_MT , FW_MT};
    vector<string> name_of_players(5);
    for (int i = 0; i < players.size(); i++)
    {
        if(players[i]->get_role() == roles[GK])
            name_of_players[GK_MT] == players[i]->get_name();
        else if(players[i]->get_role() == roles[DF])
        {
            name_of_players[DF_MT1+sum] == players[i]->get_name();
            sum++;
        }
        else if(players[i]->get_role() == roles[MD])
            name_of_players[MD_MT] == players[i]->get_name();
        else if(players[i]->get_role() == roles[FW])
            name_of_players[FW_MT] == players[i]->get_name();
    }
    if (name_of_players[DF_MT2] < name_of_players[DF_MT1])
    {
        temp = name_of_players[DF_MT2];
        name_of_players[DF_MT2] = name_of_players[DF_MT1];
        name_of_players[DF_MT1] = temp;
    }
    return name_of_players;
}

void MyTeam::print_players()
{
    vector<string> name_of_players = find_players_name();
    vector<string> name_of_roles = {"Goalkeeper" , "Defender1" , "Defender2" , "Midfielder" , "Striker"};
    for (int i = 0; i < 5; i++)
        cout << name_of_roles[i] << ": "  << name_of_players[i] << name<< endl;
}


bool MyTeam::is_available_for_thist_week(shared_ptr<Player> new_player , vector<shared_ptr<Week>> weeks , int week_index , vector<shared_ptr<Player>> list_players)
{
    int sum = 0;
    if (week_index < 0)
        return true;
    if(weeks[week_index]->have_this_situation(new_player,situation[RED]))
        return false;
    for (int i = 0; i < list_players.size(); i++)
        if(list_players[i]->get_name() == new_player->get_name())
            if(list_players[i]->get_yellow_cards() >= 3)
                return false;
    for (int i = week_index; i > week_index-3; i--)
    {
        if(i >= 0)
            if (weeks[i]->have_this_situation(new_player,situation[INJURED]))
                return false;
    }
    return true;
}

float MyTeam::find_scores(vector<shared_ptr<Week>> weeks , int week_index , vector<shared_ptr<Player>> list_players)
{
    float sum = 0;
    if(!is_complete())
        return sum;
    for (int i = 0; i < players.size(); i++)
    {
        if(!is_available_for_thist_week(players[i],weeks,week_index-1,list_players))
            continue;
        else
            sum = sum + weeks[week_index]->find_score_of_player(players[i]->get_name());
    }
    return sum;
}



