#include "../include/football_fantasy.hpp"

string FootballFantasy::correct_string(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (str[i] == '\r')
            str.erase(str.begin() + i);
    return str;
}

FootballFantasy::FootballFantasy()
{
    teams.clear();
    weeks.clear();
    users.clear();
    pre_users.clear();
    week_index = 0;
    current_user = NULL;
    transfer_condition = true;
    admin = make_shared<Admin>(ADMIN_NAME, ADMIN_PASSWORD);
}

string FootballFantasy::make_address(string folder_name, string file_name)
{
    return "./" + folder_name + "/" + file_name + ".csv";
}

string FootballFantasy::make_team_name(string name, char seprator, string mach_word)
{
    string new_name = "";
    vector<string> names = make_apart(name, seprator);
    for (int i = 0; i < names.size(); i++)
    {
        new_name = new_name + names[i];
        if (i != names.size() - 1)
            new_name = new_name + mach_word;
    }
    return new_name;
}

string FootballFantasy::make_player_name(vector<string> inputs)
{
    string new_name = "";
    for (int i = 4; i < inputs.size(); i++)
    {
        new_name = new_name + inputs[i];
        if (i != inputs.size() - 1)
            new_name = new_name + " ";
    }
    return new_name;
}

void FootballFantasy::add_teams_to_result_of_teams()
{
    pair<shared_ptr<Team>, shared_ptr<Goals>> temp;

    for (int i = 0; i < teams.size(); i++)
    {
        temp.first = teams[i]->make_copy();
        temp.second = make_shared<Goals>();
        temp.second->goals_against = 0;
        temp.second->goals_for = 0;
        result_of_teams.push_back(temp);
    }
}

void FootballFantasy::find_players_of_team(shared_ptr<Team> new_team, vector<string> inputs)
{
    vector<string> list_of_players;
    vector<string> name_and_price;
    vector<string> price_str;
    int price = 0;
    for (int i = GK + 1; i < inputs.size(); i++)
    {
        list_of_players = make_apart(inputs[i], SEPARATOR2);
        for (int j = 0; j < list_of_players.size(); j++)
        {
            name_and_price = make_apart(list_of_players[j], SEPARATOR3);
            price_str = make_apart(name_and_price[1], SEPARATOR5);
            price = stoi(correct_string(price_str[0]));
            if (list_of_players[j].length() > 1)
            {
                switch (i - 1)
                {
                case GK:
                    players.push_back(make_shared<Goal_keeper>(correct_string(name_and_price[0]), 3, price));
                    break;
                case DF:
                    players.push_back(make_shared<Defender>(correct_string(name_and_price[0]), 1, price));
                    break;
                case MD:
                    players.push_back(make_shared<Mid_fielder>(correct_string(name_and_price[0]), 0, price));
                    break;
                case FW:
                    players.push_back(make_shared<Forward>(correct_string(name_and_price[0]), 0, price));
                    break;

                default:
                    break;
                }
                new_team->add_player(players[players.size() - 1]);
            }
        }
    }
}

void FootballFantasy::get_teams_from_file(string folder_name, string file_name)
{
    int index = 0;
    vector<string> inputs;
    string address = make_address(folder_name, file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file))
    {
        inputs = make_apart(line_of_file, SEPARATOR1);
        teams.push_back(make_shared<Team>(make_team_name(inputs[0], COMMAND_SEPARATOR, "_"), 0));
        find_players_of_team(teams[index], inputs);
        index++;
    }
    add_teams_to_result_of_teams();
    input_file.close();
    return;
}

shared_ptr<Team> FootballFantasy::find_team_by_name(string team_name)
{
    for (int i = 0; i < teams.size(); i++)
        if (team_name == teams[i]->get_name())
            return teams[i];
    return NULL;
}

shared_ptr<Player> FootballFantasy::find_player_by_name(string player_name)
{
    shared_ptr<Player> found;
    for (int i = 0; i < teams.size(); i++)
    {
        found = teams[i]->find_player_by_name(player_name);
        if (found != NULL)
            return found;
    }
    return NULL;
}

void FootballFantasy::find_maches(string folder_name, string file_name, int index)
{
    int i = 0;
    vector<string> inputs, team_names, results;
    shared_ptr<Team> t1, t2;
    string address = make_address(folder_name, file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file))
    {
        inputs = make_apart(line_of_file, SEPARATOR1);
        team_names = make_apart(inputs[0], SEPARATOR3);
        results = make_apart(inputs[1], SEPARATOR3);
        t1 = find_team_by_name(make_team_name(team_names[0], COMMAND_SEPARATOR, "_"));
        t2 = find_team_by_name(make_team_name(team_names[1], COMMAND_SEPARATOR, "_"));
        weeks[index]->add_match(make_shared<Match>(t1->make_copy(), stoi(results[0]), stoi(results[1]), t2->make_copy(), stoi(results[1]), stoi(results[0])));
        weeks[index]->add_players(i, inputs);
        i++;
    }
    input_file.close();
    return;
}

void FootballFantasy::get_weeks_from_file(string folder_name, string file_name, int num_of_weeks)
{
    string new_file_name = "";
    for (int i = 0; i < num_of_weeks; i++)
    {
        new_file_name = file_name + to_string(i + 1);
        weeks.push_back(make_shared<Week>());
        find_maches(folder_name, new_file_name, i);
    }
}

void FootballFantasy::calculate_scores_from_file()
{
    for (auto &week : weeks)
        week->calculate_scores_for_matches();
}

bool FootballFantasy::is_login()
{
    return current_user != NULL || admin->is_login();
}

shared_ptr<User> FootballFantasy::find_user_by_name(string name)
{
    for (int i = 0; i < users.size(); i++)
        if (name == users[i]->get_name())
            return users[i];
    return NULL;
}

shared_ptr<User> FootballFantasy::find_from_pre_users(string name)
{
    for (int i = 0; i < pre_users.size(); i++)
        if (name == pre_users[i]->get_name())
            return pre_users[i];
    throw Not_Found();
}

void FootballFantasy::change_transfer_window(bool con)
{
    if (!admin->is_login())
        throw Permission_Denied();
    transfer_condition = con;
    print(OK);
}

void FootballFantasy::update_scores()
{
    for (int i = 0; i < players.size(); i++)
        players[i]->update_player(weeks[week_index]->find_score_of_player(players[i]->get_name()));
    for (int i = 0; i < users.size(); i++)
        users[i]->update_user(weeks, week_index, players);
    pre_users.clear();
    for (int i = 0; i < users.size(); i++)
        pre_users.push_back(users[i]->make_copy());
    for (int i = 0; i < result_of_teams.size(); i++)
    {
        result_of_teams[i].first->update_total_score(weeks[week_index]->find_score_of_team(result_of_teams[i].first->get_name()));
        weeks[week_index]->update_goals(result_of_teams[i].second, result_of_teams[i].first->get_name());
    }
}

void FootballFantasy::update_cards()
{
    if (week_index < NUMBER_OF_WEEKS - 1)
    {
        week_index++;
        for (int i = 0; i < players.size(); i++)
            if (weeks[week_index]->have_this_situation(players[i], situation[RED]))
                players[i]->empty_yelloW_cards();
            else if (weeks[week_index]->have_this_situation(players[i], situation[YELLOW]))
                players[i]->increase_yellow_cards();
    }
}

void FootballFantasy::pass_week()
{
    if (!admin->is_login())
        throw Permission_Denied();
    if (week_index == 0)
        for (int i = 0; i < players.size(); i++)
            if (weeks[week_index]->have_this_situation(players[i], situation[YELLOW]))
                players[i]->increase_yellow_cards();
    update_scores();
    update_cards();
    print(OK);
}

void FootballFantasy::signup(vector<string> inputs)
{
    shared_ptr<User> temp;
    if (inputs.size() < 7)
        throw Bad_Request();
    else if (is_login() || find_user_by_name(inputs[4]) != NULL)
        throw Bad_Request();
    temp = make_shared<User>(inputs[4], inputs[6], make_shared<MyTeam>(inputs[4], 0));
    users.push_back(temp);
    current_user = temp;
    print(OK);
}

void FootballFantasy::login(vector<string> inputs)
{
    shared_ptr<User> temp;
    if (inputs.size() < 7 || is_login())
        throw Bad_Request();
    temp = find_user_by_name(inputs[4]);
    if (temp == NULL)
        throw Not_Found();
    else if (!temp->check_password(inputs[6]))
        throw Permission_Denied();
    current_user = temp;
    print(OK);
}

void FootballFantasy::register_admin(vector<string> inputs)
{
    if (inputs.size() < 7 || is_login())
        throw Bad_Request();
    else if (!admin->check_id(inputs[4], inputs[6]))
        throw Bad_Request();
    admin->change_log(true);
    print(OK);
}

void FootballFantasy::logout()
{
    if (!is_login())
        throw Permission_Denied();
    current_user = NULL;
    admin->change_log(false);
    print(OK);
}

void FootballFantasy::sell_player(vector<string> inputs)
{
    string name;
    if (inputs.size() < 5)
        throw Bad_Request();
    else if (current_user == NULL || !transfer_condition)
        throw Permission_Denied();
    current_user->sell_player(make_player_name(inputs));
}

bool FootballFantasy::is_available_for_next_week(shared_ptr<Player> new_player)
{
    int sum = 0;
    if (weeks[week_index]->have_this_situation(new_player, situation[RED]))
        return false;
    for (int i = 0; i < players.size(); i++)
        if (players[i]->get_name() == new_player->get_name())
            if (players[i]->get_yellow_cards() >= 3)
                return false;
    for (int i = week_index; i > week_index - 3; i--)
        if (i >= 0)
            if (weeks[i]->have_this_situation(new_player, situation[INJURED]))
                return false;
    return true;
}

void FootballFantasy::buy_player(vector<string> inputs)
{
    string name;
    shared_ptr<Player> temp;
    if (inputs.size() < 5)
        throw Bad_Request();
    temp = find_player_by_name(make_player_name(inputs));
    if (temp == NULL)
        throw Not_Found();
    if (current_user == NULL || !transfer_condition)
        throw Permission_Denied();
    if (is_available_for_next_week(temp))
        current_user->buy_player(temp);
    else
        throw Is_Not_Available();
}

void FootballFantasy::set_captain(vector<string> inputs)
{
    string name;
    if (inputs.size() < 5)
        throw Bad_Request();
    else if (current_user == NULL)
        throw Permission_Denied();
    current_user->set_captain(make_player_name(inputs));
}

void FootballFantasy::handle_post_commands(vector<string> inputs)
{
    if (inputs.size() < 2)
        throw Bad_Request();
    else if (inputs[1] == CLOSE_TRANSFER_WINDOW)
        change_transfer_window(false);
    else if (inputs[1] == OPEN_TRANSFER_WINDOW)
        change_transfer_window(true);
    else if (inputs[1] == PASS_WEEK)
        pass_week();
    else if (inputs[1] == SIGNUP)
        signup(inputs);
    else if (inputs[1] == LOGIN)
        login(inputs);
    else if (inputs[1] == REGISTER_ADMIN)
        register_admin(inputs);
    else if (inputs[1] == LOGOUT)
        logout();
    else if (inputs[1] == SELL_PLAYER)
        sell_player(inputs);
    else if (inputs[1] == BUY_PLAYER)
        buy_player(inputs);
    else if (inputs[1] == SET_CAPTAIN)
        set_captain(inputs);
    else
        throw Not_Found();
}

void FootballFantasy::get_squad(vector<string> inputs)
{
    shared_ptr<User> temp;
    if (inputs.size() < 2)
        throw Bad_Request();
    else if (current_user == NULL)
        throw Permission_Denied();
    if (inputs.size() >= 5)
        temp = find_from_pre_users(inputs[4]);
    else
        temp = find_from_pre_users(current_user->get_name());
    if (!temp->is_my_team_complete())
        throw Empty();
    temp->print_squad();
}

vector<shared_ptr<User>> FootballFantasy::sort_users()
{
    if (pre_users.size() == 0)
        throw Empty();
    vector<shared_ptr<User>> new_users = pre_users;
    shared_ptr<User> temp;
    for (int i = 0; i < new_users.size() - 1; i++)
        for (int j = i + 1; j < new_users.size(); j++)
            if (new_users[j]->get_score() > new_users[i]->get_score() ||
                (new_users[j]->get_score() == new_users[i]->get_score() && new_users[j]->get_name() < new_users[i]->get_name()))
            {
                temp = new_users[i];
                new_users[i] = new_users[j];
                new_users[j] = temp;
            }
    return new_users;
}

void FootballFantasy::print_users_ranking()
{
    vector<shared_ptr<User>> new_users = sort_users();
    for (int i = 0; i < new_users.size(); i++)
        cout << i + 1 << ". team_name: " << new_users[i]->get_name() << " | point: " << new_users[i]->get_score() << endl;
}

void FootballFantasy::print_matches_result_league(vector<string> inputs)
{
    int new_index = 0;
    if (inputs.size() < 2)
        throw Bad_Request();
    if (inputs.size() >= 5)
    {
        new_index = stoi(inputs[4]) - 1;
        if (new_index > week_index - 1 || new_index < 0)
            throw Bad_Request();
    }
    else
        new_index = week_index - 1;
    if (week_index > 0)
        weeks[new_index]->print_matches_result_league();
    else
        throw Bad_Request();
}

void FootballFantasy::sort_league_teams()
{
    pair<shared_ptr<Team>, shared_ptr<Goals>> temp;
    for (int i = 0; i < result_of_teams.size() - 1; i++)
        for (int j = i + 1; j < result_of_teams.size(); j++)
            if (result_of_teams[j].first->get_total_score_of_team() > result_of_teams[i].first->get_total_score_of_team() ||
                (result_of_teams[j].first->get_total_score_of_team() == result_of_teams[i].first->get_total_score_of_team() && result_of_teams[j].second->goals_for - result_of_teams[j].second->goals_against > result_of_teams[i].second->goals_for - result_of_teams[i].second->goals_against) ||
                (result_of_teams[j].first->get_total_score_of_team() == result_of_teams[i].first->get_total_score_of_team() && result_of_teams[j].second->goals_for - result_of_teams[j].second->goals_against == result_of_teams[i].second->goals_for - result_of_teams[i].second->goals_against && result_of_teams[j].second->goals_for > result_of_teams[i].second->goals_for) ||
                (result_of_teams[j].first->get_total_score_of_team() == result_of_teams[i].first->get_total_score_of_team() && result_of_teams[j].second->goals_for - result_of_teams[j].second->goals_against == result_of_teams[i].second->goals_for - result_of_teams[i].second->goals_against && result_of_teams[j].second->goals_for == result_of_teams[i].second->goals_for && result_of_teams[j].first->get_name() < result_of_teams[i].first->get_name()))
            {
                temp = result_of_teams[i];
                result_of_teams[i] = result_of_teams[j];
                result_of_teams[j] = temp;
            }
}

void FootballFantasy::print_league_standings()
{
    cout << "league standings:" << endl;
    sort_league_teams();
    for (int i = 0; i < result_of_teams.size(); i++)
    {
        cout << i + 1 << ". " << make_team_name(result_of_teams[i].first->get_name(), SEPARATOR4, " ") << ": score: ";
        cout << result_of_teams[i].first->get_total_score_of_team() << " | GF: " << result_of_teams[i].second->goals_for;
        cout << " | GA: " << result_of_teams[i].second->goals_against << endl;
    }
}

void FootballFantasy::print_team_of_the_week(vector<string> inputs)
{
    int new_index = 0;
    if (inputs.size() < 2)
        throw Bad_Request();
    if (inputs.size() >= 5)
    {
        new_index = stoi(inputs[4]) - 1;
        if (new_index > week_index - 1 || new_index < 0)
            throw Not_Found();
    }
    else
        new_index = week_index - 1;
    if (week_index > 0)
        weeks[new_index]->print_team_of_week();
    else
        throw Bad_Request();
}

void FootballFantasy::print_players(vector<string> inputs)
{
    shared_ptr<Team> new_team;
    bool rank = false;
    string player_role = NOTHING;
    if (inputs.size() < 5)
        throw Bad_Request();
    else if (inputs.size() == 6)
        if (inputs[5] == RANKS)
            rank = true;
        else
            player_role = inputs[5];
    else if (inputs.size() == 7)
    {
        rank = true;
        player_role = inputs[5];
    }
    new_team = find_team_by_name(inputs[4]);
    if (new_team == NULL)
        throw Not_Found();
    new_team->print_players(players, rank, player_role);
}

void FootballFantasy::show_budget()
{
    if (current_user == NULL)
        throw Permission_Denied();
    print(current_user->get_budget());
}

void FootballFantasy::handle_get_commands(vector<string> inputs)
{
    if (inputs.size() < 2)
        throw Bad_Request();
    else if (inputs[1] == SQUAD)
        get_squad(inputs);
    else if (inputs[1] == USERS_RANKING)
        print_users_ranking();
    else if (inputs[1] == MATCHES_RESULT_LEAGUE)
        print_matches_result_league(inputs);
    else if (inputs[1] == LEAGUE_STANDINGS)
        print_league_standings();
    else if (inputs[1] == TEAM_OF_THE_WEEK)
        print_team_of_the_week(inputs);
    else if (inputs[1] == GET_PLAYERS)
        print_players(inputs);
    else if (inputs[1] == SHOW_BUDGET)
        show_budget();
    else
        throw Not_Found();
}

void FootballFantasy::handle_put_commands(vector<string> inputs)
{
    return;
}

void FootballFantasy::handle_delete_commands(vector<string> inputs)
{
    return;
}
