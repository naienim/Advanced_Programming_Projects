#ifndef __MANUAL__
#define __MANUAL__

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <utility>
#include <memory>
#include <set>

using namespace std;

#define print(x) cout << x << endl 

enum position {GK , DF , MD , FW};
const vector<string> roles = {"gk" , "df" , "md" , "fw"};
enum request {POST , GET , PUT , DELETE};
const vector<string> commands = {"POST" , "GET" , "PUT" , "DELETE"}; 
enum bad_situation {RED , YELLOW , INJURED};
const vector<string> situation = {"red_card" , "yellow_card" , "injured"}; 
enum elements {GOALS_TO , OWN_GOAL , ASSIST};
const vector<string> name_of_elements = {"goal_to" , "own goal" , "assist"};
enum result {WON, TIED, LOST};

enum roles_in_playground {GK_ORIGINAL , DF_LEFT , DF_MIDDLE_1 , DF_MIDDLE_2 , DF_RIGHT , 
                          MD_MIDDLE_1 , MD_MIDDLE_2 , MD_MIDDLE_3 , FW_LEFT , FW_MIDDLE , FW_RIGHT};

const char COMMAND_SEPARATOR = ' ';
const char SEPARATOR1 = ',';
const char SEPARATOR2 = ';';
const char SEPARATOR3 = ':';
const char SEPARATOR4 = '_';
const char SEPARATOR5 = '$';

const string ADMIN_NAME = "admin";
const string ADMIN_PASSWORD = "123456";

const string OK = "OK";
const string BAD_REQUEST  = "Bad Request";
const string PERMISSION_DENIED = "Permission Denied";
const string NOT_FOUND = "Not Found";
const string EMPTY = "Empty";
const string IS_NOT_AVAILABLE = "This player is not available for next week";
 
const string CLOSE_TRANSFER_WINDOW = "close_transfer_window";
const string OPEN_TRANSFER_WINDOW = "open_transfer_window";
const string PASS_WEEK = "pass_week";
const string SIGNUP = "signup";
const string LOGIN = "login";
const string REGISTER_ADMIN = "register_admin";
const string LOGOUT = "logout";
const string SELL_PLAYER = "sell_player";
const string BUY_PLAYER = "buy_player";
const string SQUAD = "squad";
const string USERS_RANKING = "users_ranking";
const string MATCHES_RESULT_LEAGUE = "matches_result_league";
const string LEAGUE_STANDINGS = "league_standings";
const string TEAM_OF_THE_WEEK = "team_of_the_week";
const string GET_PLAYERS = "players";
const string SET_CAPTAIN = "set_captain";
const string SHOW_BUDGET = "show_budget";

const string NOTHING = "nothing";
const string RANKS = "ranks";
const string OWN_GOAL_STR = "OWN_GOAL";
const string CAPTAIN_TAG = "(CAPTAIN)";

const string FOLDER_NAME_DATA = "data";
const string FILE_NAME_LEAGUE = "premier_league";
const string FILE_NAME_WEEkS = "weeks_stats/week_";

const int NUMBER_OF_WEEKS = 19;
const int MAX_NUM_OF_SELL = 2;
const int MAX_NUM_OF_BUY = 2;
const int NUM_OF_DEFENDER = 2;
const int FIRST_BUDGET = 2500;

#endif