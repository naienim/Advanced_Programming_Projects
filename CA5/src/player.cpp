#include <../include/player.hpp>

Player::Player(int _x, int _y , int new_speed , vector<string> images , bool new_flag) : x(_x), y(_y), speed(new_speed) 
{
    textures.clear();
    for (int i = 0; i < images.size(); i++)
    {
        textures.push_back(new Texture);
        if (!textures[i]->loadFromFile("./pictures/"+images[i]+".png"))
            abort();
    }
    sprite.setTexture(*textures[0]);
    sprite.setPosition(x, y);
    dy = 0;
    draw_or_not = true;
    free = false;
    my_direction = LEFT;
    lives = 2;
    stars = 0;
    gems = 0;
    step = 1;
    animation = new_flag;
}

void Player::change_picture(Texture &texture)
{
    sprite.setTexture(texture);
}

void Player::draw(RenderWindow &window)
{
    if (draw_or_not)
        window.draw(sprite);
    else if (lives <= 0)
    {
        change_picture(*textures[5+my_direction]);
        sprite.setPosition(x,y+18);
    }
    else 
        return;
    window.draw(sprite);
}

void Player::move(Direction direction)
{   int index = 1;
    if (animation)
    {
        if (step > (textures.size()-1)/2)
            step = 1;
        if (direction != UP)
            change_picture(*textures[direction*(textures.size()-1)/2 + step]);
    }
    else
    {
        if (lives == 1)
            index = 3;
        else 
            (index = 1);
        if (direction != UP)
            change_picture(*textures[direction+index]);
    }
    int new_x = x + delta_x[direction] * speed;
    int new_y = y;
    if (direction == UP)
        new_y += dy;
    
    x = new_x;
    y = new_y;
    sprite.setPosition(x, y);
}

FloatRect Player::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

void Player::set_gravity(float number)
{
    dy += number;
}

void Player::change_jump_mode(float number)
{
    dy = number;
}

Vector2u Player::get_size()
{
    return textures[0]->getSize();
}

Vector2f Player::get_position()
{
    return sprite.getPosition();
}

bool Player::is_draw()
{
    if (lives <= 0)
        draw_or_not = false;
    return draw_or_not;
}

void Player::make_draw_or_not(bool mode)
{
    draw_or_not = mode;
}

bool Player::is_free()
{
    return free;
}

void Player::make_free_or_not(bool mode)
{
    free = mode;
}

void Player::change_my_direction(Direction new_direction)
{
    my_direction = new_direction;
}

Direction Player::get_my_direction()
{
    return my_direction;
}

void Player::change_position(int _x , int _y)
{
    x = _x;
    y = _y;
    sprite.setPosition(x,y);
}

int Player::get_lives()
{
    return lives;
}

int Player::get_speed()
{
    return speed;
}

void Player::change_num_of_lives(int number)
{
    lives = number;
}

void Player::decrease_num_of_lives(int number)
{
    lives -= number;
}

int Player::get_num_of_stars()
{
    return stars;
}

int Player::get_num_of_gems()
{
    return gems;
}

void Player::increase_stars()
{
    stars++;
}

void Player::increase_gems()
{
    gems++;
}

void Player::make_scores_zero()
{
    gems = 0;
    stars = 0;
}

void Player::increase_step()
{
    if (dy == 0)
        step++;
}
