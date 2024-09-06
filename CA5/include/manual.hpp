#if !defined(__MANUAL__)
#define __MANUAL__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace sf;
using namespace std;

enum SoundList {START_S , PAUSE_S , JUMP_S , SCORE_S , HIT_S , DIE_S , FREE_S , GAME_OVER_S , WIN_S};
const vector<string> sound_name = {"start","pause","jump1","score","hit1","die","free","game_over","win"};
enum Status {START , GAMING , PAUSE , LOOSE , WIN , BUILD_MAP};
enum Direction {LEFT , RIGHT , UP};
const int delta_x[3] = {-1 , 1 , 0};
const vector<string> player_images = {"player1","player1","player2","player3","player4","player5","player6","player7","player8","player9",
                                "player10","player11","player12","player13","player14","player15","player16","player17","player18"};
const vector<string> turtle_images = {"imprisoned_turtle","turtle1","turtle2","turtle3","turtle4","turtle5","turtle6","turtle7","turtle8",
                                "turtle9","turtle10","turtle11","turtle12","turtle13","turtle14","turtle15","turtle16"};
const vector<string> weak_enemy_images = {"weak_enemy1" , "weak_enemy1" , "weak_enemy2", "weak_enemy3" , "weak_enemy4", "weak_enemy5" , "weak_enemy6"};
const vector<string> strong_enemy_images = {"strong_enemy1" , "strong_enemy1" , "strong_enemy2", "strong_enemy3" , "strong_enemy4", "strong_enemy5" , "strong_enemy6"};
const vector<string> start_images = {"play_button"};
const vector<string> pause_images = {"continue_button","home_button"};
const vector<string> end_game_images = {"retry_button","home_button"};
const string MAP_OF_GAME = "./map/map1.csv";
const int GAP = 10;
const int STEP_SIZE = 6;
const int PLAYER_SPEED = 6;
const int BASE_ENEMY_SPEED = 2;
const int TURTLE_SPEED = 3;
const int WINDOW_WIDTH = 1800;
const int WINDOW_HEIGHT = 950;
const int PLAYER_POSITION_X = 3865;
const int PLAYER_POSITION_Y = 710;
const int ENEMY_CHANGE_MODE_TIME = 3;
const int CHANGE_MODE_TIME = 50;
const int SCORE_FONT_SIZE = 70;
const int NUMBER_OF_HEARTS = 3;
const int GEM_SCORE = 20;
const int STAR_SCORE = 10;
const int game_timing = 90;
const float GRAVITY = 0.2;
const float JUMP_FIRST_AMOUNT = -11;
const float JUMP_HIT_AMOUNT = -7;


#endif
