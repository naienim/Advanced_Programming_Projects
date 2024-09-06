#include <../include/new_window.hpp>

NewWindow::NewWindow(int _x, int _y ,string background_image , vector<string> icon_images) : x(_x), y(_y)
{
    if (!background.loadFromFile(background_image))
        abort();
    background_sprite.setTexture(background);
    background_sprite.setPosition(x,y);
    icons.clear();
    icons_sprite.clear();
    for (int i = 0; i < icon_images.size(); i++)
    {
        icons.push_back(new Texture);
        icons_sprite.push_back(new Sprite);
        if (!icons[i]->loadFromFile("./pictures/"+icon_images[i]+".png"))
            abort();
        icons_sprite[i]->setTexture(*icons[i]);
    }
    font.loadFromFile("font/arialbd.ttf");
	message_text.setFont(font);
	message_text.setCharacterSize(1.5*SCORE_FONT_SIZE);
	message_text.setFillColor(Color::Black);
    message_text.setString("");
    score_text.setFont(font);
	score_text.setCharacterSize(SCORE_FONT_SIZE);
	score_text.setFillColor(Color::Black);
    score_text.setString("");
}

void NewWindow::draw(RenderWindow &window)
{
    window.draw(background_sprite);
    for (int i = 0; i < icons_sprite.size(); i++)
        window.draw(*icons_sprite[i]);
    window.draw(message_text);
    window.draw(score_text);
}

void NewWindow::set_position(int _x , int _y)
{
    x = _x;
    y = _y;
    background_sprite.setPosition(x,y);
}

void NewWindow::set_icon_position(int index , int new_x , int new_y)
{
    icons_sprite[index]->setPosition(new_x,new_y);
}

void NewWindow::set_message_text(int new_x , int new_y , string my_message)
{
    message_text.setPosition(new_x,new_y);
    message_text.setString(my_message);
}

void NewWindow::set_score_text(int new_x , int new_y , string my_message)
{
    score_text.setPosition(new_x,new_y);
    score_text.setString(my_message);
}

bool NewWindow::is_clicked(int icon_index , RenderWindow &window)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        FloatRect bounds = icons_sprite[icon_index]->getGlobalBounds();
        if (bounds.contains(mouse))
        {
            return true;
        }
    }
    return false;
}

Vector2u NewWindow::get_window_size()
{
    return background.getSize();
}