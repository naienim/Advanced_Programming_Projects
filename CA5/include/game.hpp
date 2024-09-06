#if !defined(__GAME__)
#define __GAME__

#include "manual.hpp"
#include "player.hpp"
#include "block.hpp"
#include "new_window.hpp"

class Game
{
public:
    Game(vector<Sound*> new_sounds);
    vector<string> make_apart(string line_of_file , char separator);
    void set_base_details();
    void build_map(string flag , vector<string> inputs);
    void set_map(string address);
    void set_details_position(View &View);
    void set_hearts_position();
    void draw(RenderWindow &window ,View &view);
    void decrease_player_life();
    bool can_move_to_blocks(vector<Block*> &walls ,Direction direction);
    bool can_move_to_enemies(vector<Player*> &enemies ,Direction direction);
    void move_player(Direction direction);
    void handle_events(RenderWindow &window);
    bool can_jump(Player object);
    void jump(Player &object , bool flag);
    void start();
    void find_direction();
    bool is_over();
    bool is_win();
    void free_turtles();
    void move_turtles();
    void turtles_get_home();
    void touch_thorns();
    void touch_enemies(vector<Player*> &enemies);
    void kill_enemies(vector<Player*> &enemies);
    void move_enemies(vector<Player*> &enemies);
    void change_strong_enemy_mode();
    void handle_enemies();
    void get_score();
    void change_step();
    Status handle_game(RenderWindow &window, View &view, Clock &clock, Clock &clock_mode);
    Vector2f get_window_position();
    int get_total_score();
private:
    bool started;
    Player player;
    Block background;
    vector<Block*> gates;
    vector<Block*> blocks;
    vector<Block*> stars;
    vector<Block*> gems;
    vector<Block*> hearts;
    vector<Block*> thorns;
    vector<Player*> turtles;
    vector<Player*> weak_enemies;
    vector<Player*> strong_enemies;
    vector<Sound*> sounds;
    bool game_starting;
    Font font;
	Text star_text;
    Text gem_text;
    NewWindow button;
};

#endif