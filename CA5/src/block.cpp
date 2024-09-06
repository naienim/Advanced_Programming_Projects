#include <../include/block.hpp>

Block::Block(int _x, int _y ,string image) : x(_x), y(_y)
{
    if (!texture.loadFromFile(image))
        abort();
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    draw_or_not = true;
}

void Block::set_position(int _x ,int _y)
{
    sprite.setPosition(_x,_y);
}

void Block::draw(RenderWindow &window)
{
    if (draw_or_not)
        window.draw(sprite);
}

FloatRect Block::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

Vector2u Block::get_size()
{
    return texture.getSize();
}

Vector2f Block::get_position()
{
    return sprite.getPosition();
}

bool Block::is_draw()
{
    return draw_or_not;
}

void Block::make_draw_or_not(bool mode)
{
    draw_or_not = mode;
}