#if !defined(__NEW_WINDOW__)
#define __NEW_WINDOW__

#include "manual.hpp"

class NewWindow
{
public:
    NewWindow(int _x, int _y ,string background_image , vector<string> icon_images);
    void draw(RenderWindow &window);
    void set_position(int _x , int _y);
    void set_icon_position(int index , int new_x , int new_y);
    void set_message_text(int new_x , int new_y , string my_message);
    void set_score_text(int new_x , int new_y , string my_message);
    bool is_clicked(int icon_index , RenderWindow &window);
    Vector2u get_window_size();
private:
    Texture background;
    vector<Texture*> icons;
    Sprite background_sprite;
    vector<Sprite*> icons_sprite;
    Font font;
	Text message_text;
    Text score_text;
    int x;
    int y;
};

#endif