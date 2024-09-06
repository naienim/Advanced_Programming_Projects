#if !defined(__PLAYER__)
#define __PLAYER__

#include "manual.hpp"

class Player
{
public:
    Player(int _x, int _y , int new_speed , vector<string> images , bool new_flag);
    void change_picture(Texture &texture);
    void draw(RenderWindow &window);
    void move(Direction direction);
    FloatRect getGlobalBounds();
    void set_gravity(float number);
    void change_jump_mode(float number);
    Vector2u get_size();
    Vector2f get_position();
    bool is_draw();
    void make_draw_or_not(bool mode);
    bool is_free();
    void make_free_or_not(bool mode);
    void change_my_direction(Direction new_direction);
    Direction get_my_direction();
    void change_position(int _x , int _y);
    int get_lives();
    int get_speed();
    void change_num_of_lives(int number);
    void decrease_num_of_lives(int number);
    int get_num_of_stars();
    int get_num_of_gems();
    void increase_stars();
    void increase_gems();
    void make_scores_zero();
    void increase_step();
private:
    vector<Texture*> textures;
    Sprite sprite;
    Direction my_direction;
    int x;
    int y;
    int speed;
    int lives;
    int stars;
    int gems;
    float dy;
    bool draw_or_not;
    bool free;
    bool animation;
    int step;
};

#endif