#include "../include/match.hpp"

vector<string> make_apart(string line_of_file, char separator)
{
    string file_element;
    vector<string> inputs;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
        inputs.push_back(file_element);
    return inputs;
}

Match::Match(shared_ptr<Team> t1, int gf1, int ga1, shared_ptr<Team> t2, int gf2, int ga2)
{
    team1.first = t1;
    team1.second.goals_for = gf1;
    team1.second.goals_against = ga1;
    team2.first = t2;
    team2.second.goals_for = gf2;
    team2.second.goals_against = ga2;
    composition_of_team1.clear();
    composition_of_team2.clear();
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
        if (name == players[i]->get_name())
            return players[i];
    return NULL;
}

vector<shared_ptr<Player>> Match::add_players_to_each_list(vector<string> names, vector<shared_ptr<Player>> list)
{
    for (int i = 0; i < names.size(); i++)
        list.push_back(find_player_from_list(names[i]));
    return list;
}

void Match::find_goals(vector<string> inputs)
{
    vector<string> goals_information = make_apart(inputs[5], SEPARATOR2);
    shared_ptr<Player> temp;
    vector<string> peersons;
    for (int i = 0; i < goals_information.size(); i++)
    {
        peersons = make_apart(goals_information[i], SEPARATOR3);
        if (peersons[1] == OWN_GOAL_STR)
        {
            temp = find_player_from_list(peersons[0]);
            temp->increase_num_of_element(name_of_elements[OWN_GOAL]);
        }
        else
        {
            temp = find_player_from_list(peersons[0]);
            temp->increase_num_of_element(name_of_elements[GOALS_TO]);
            temp = find_player_from_list(peersons[1]);
            temp->increase_num_of_element(name_of_elements[ASSIST]);
        }
    }
}

void Match::merge_all_players()
{
    players.clear();
    for (int i = 0; i < composition_of_team1.size(); i++)
        players.push_back(composition_of_team1[i]);
    for (int i = 0; i < composition_of_team2.size(); i++)
        players.push_back(composition_of_team2[i]);
}

void Match::add_players(vector<string> inputs)
{
    shared_ptr<Player> temp;
    vector<string> name_of_players_team1 = make_apart(inputs[6], SEPARATOR2);
    vector<string> name_of_players_team2 = make_apart(inputs[7], SEPARATOR2);
    for (int i = 0; i < name_of_players_team2.size(); i++)
    {
        temp = find_player_by_name(name_of_players_team1[i]);
        composition_of_team1.push_back(temp->make_copy());
        temp = find_player_by_name(name_of_players_team2[i]);
        composition_of_team2.push_back(temp->make_copy());
    }
    merge_all_players();
    find_goals(inputs);
    injuredes = add_players_to_each_list(make_apart(inputs[2], SEPARATOR2), injuredes);
    yellow_cards = add_players_to_each_list(make_apart(inputs[3], SEPARATOR2), yellow_cards);
    red_cards = add_players_to_each_list(make_apart(inputs[4], SEPARATOR2), red_cards);
}

bool Match::have_this_situation(shared_ptr<Player> new_player, string situ)
{
    if (situ == situation[RED])
    {
        for (int i = 0; i < red_cards.size(); i++)
            if (new_player->get_name() == red_cards[i]->get_name())
                return true;
        return false;
    }
    else if (situ == situation[YELLOW])
    {
        for (int i = 0; i < yellow_cards.size(); i++)
            if (new_player->get_name() == yellow_cards[i]->get_name())
                return true;
        return false;
    }
    else if (situ == situation[INJURED])
    {
        for (int i = 0; i < injuredes.size(); i++)
            if (new_player->get_name() == injuredes[i]->get_name())
                return true;
        return false;
    }
    return false;
}

string Match::make_team_name(string name)
{
    string new_name = "";
    vector<string> names = make_apart(name, SEPARATOR4);
    for (int i = 0; i < names.size(); i++)
    {
        new_name = new_name + names[i];
        if (i != names.size() - 1)
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
    if (team1.first->get_name() == team_name)
        return true;
    else if (team2.first->get_name() == team_name)
        return true;
    return false;
}

float Match::find_score_of_this_team(string team_name)
{
    if (team1.first->get_name() == team_name)
        if (team1.second.goals_for > team1.second.goals_against)
            return 3;
        else if (team1.second.goals_for == team1.second.goals_against)
            return 1;
        else
            return 0;
    else if (team2.first->get_name() == team_name)
        if (team2.second.goals_for > team2.second.goals_against)
            return 3;
        else if (team2.second.goals_for == team2.second.goals_against)
            return 1;
        else
            return 0;
    return 0;
}

void Match::update_num_of_goals(shared_ptr<Goals> num_goals, string team_name)
{
    if (team1.first->get_name() == team_name)
    {
        num_goals->goals_for += team1.second.goals_for;
        num_goals->goals_against += team1.second.goals_against;
    }
    else if (team2.first->get_name() == team_name)
    {
        num_goals->goals_for += team2.second.goals_for;
        num_goals->goals_against += team2.second.goals_against;
    }
}

void Match::calculate_both_teams_scores()
{
    calculate_team_scores(team1, team2, composition_of_team1, composition_of_team2);
    calculate_team_scores(team2, team1, composition_of_team2, composition_of_team1);
}

void Match::calculate_team_scores(pair<shared_ptr<Team>, Goals> _team1, pair<shared_ptr<Team>, Goals> _team2,
                                  vector<shared_ptr<Player>> &_composition_of_team1, vector<shared_ptr<Player>> _composition_of_team2)
{
    goals_taken_from t1;
    roles_in_playground _left[2] = {DF_LEFT, FW_LEFT};
    roles_in_playground _right[2] = {DF_RIGHT, FW_RIGHT};
    t1.left = 0;
    t1.right = 0;
    for (int i = 0; i < 2; i++)
    {
        t1.left += _composition_of_team2[_left[i]]->get_goals();
        t1.right += _composition_of_team2[_right[i]]->get_goals();
        _composition_of_team1[_left[i]]->set_role_in_match(_left[i]);
        _composition_of_team1[_right[i]]->set_role_in_match(_right[i]);
    }
    roles_in_playground _mid[3] = {FW_MIDDLE, DF_MIDDLE_1, DF_MIDDLE_2};
    roles_in_playground _mds[3] = {MD_MIDDLE_1, MD_MIDDLE_2, MD_MIDDLE_3};
    t1.mid = 0;
    t1.mds = 0;
    for (int i = 0; i < 3; i++)
    {
        t1.mid += _composition_of_team2[_mid[i]]->get_goals();
        t1.mds += _composition_of_team2[_mds[i]]->get_goals();
        _composition_of_team1[_mid[i]]->set_role_in_match(_mid[i]);
        _composition_of_team1[_mds[i]]->set_role_in_match(_mds[i]);
    }
    _composition_of_team1[GK_ORIGINAL]->set_role_in_match(GK_ORIGINAL);
    t1.total = t1.left + t1.right + t1.mid + t1.mds + _composition_of_team1[GK_ORIGINAL]->get_goals();
    for (auto &player : _composition_of_team1)
    {
        if (_team1.second.goals_for > _team1.second.goals_against)
            player->calculate_score(WON, t1);
        else if (_team1.second.goals_for < _team1.second.goals_against)
            player->calculate_score(LOST, t1);
        else if (_team1.second.goals_for == _team1.second.goals_against)
            player->calculate_score(TIED, t1);
    }
}

vector<shared_ptr<Player>> Match::get_players()
{
    return players;
}
