#if !defined(__BLOCK__)
#define __BLOCK__

#include "manual.hpp"

class Block
{
public:
    Block(int _x, int _y ,string image);
    void set_position(int _x ,int _y);
    void draw(RenderWindow &window);
    FloatRect getGlobalBounds();
    Vector2u get_size();
    Vector2f get_position();
    bool is_draw();
    void make_draw_or_not(bool mode);
private:
    Texture texture;
    Sprite sprite;
    bool draw_or_not;
    int x;
    int y;
};

#endif