#include <../include/menu.hpp>

void set_sounds(vector<SoundBuffer*> &buffers, vector<Sound*> &sounds, RenderWindow &window)
{
    window.setFramerateLimit(game_timing);
    buffers.clear();
    sounds.clear();
    for (int i = 0; i < sound_name.size() ; i++)
    {
        buffers.push_back(new SoundBuffer);
        sounds.push_back(new Sound);
        buffers[i]->loadFromFile("./sounds/" + sound_name[i] +".wav");
	    sounds[i]->setBuffer(*buffers[i]);
    }
}

Status build_start_window(RenderWindow &window, Game &game, NewWindow &start_window, Sound &sound)
{
    Vector2f position;
    position = game.get_window_position();
    start_window.set_position(position.x,position.y);
    start_window.set_icon_position(0,position.x+440,position.y+530);
    start_window.draw(window);
    if (start_window.is_clicked(0,window))
    {
        sound.play();
        return GAMING;
    }
    return START;
}

Status build_pause_window(RenderWindow &window, Game &game, NewWindow &pause_window , View &view)
{
    Vector2f position;
    position = game.get_window_position();
    pause_window.set_position(position.x+340,position.y);
    pause_window.set_icon_position(0,position.x+743,position.y+530);
    pause_window.set_icon_position(1,position.x+940,position.y+530);
    pause_window.set_message_text(position.x+710,position.y+280,"Paused");
    game.draw(window,view);
    pause_window.draw(window);
    if (pause_window.is_clicked(0,window))
        return GAMING;
    else if (pause_window.is_clicked(1,window))
        return BUILD_MAP;
    return PAUSE;
}

Status build_end_game_window(RenderWindow &window, Game &game, NewWindow &pause_window, View &view, Status status, Sound &sound)
{
    Vector2f position;
    position = game.get_window_position();
    pause_window.set_position(position.x+340,position.y);
    pause_window.set_icon_position(0,position.x+743,position.y+530);
    pause_window.set_icon_position(1,position.x+940,position.y+530);
    if (status == LOOSE)
        pause_window.set_message_text(position.x+580,position.y+300,"GAME OVER!");
    else if (status == WIN)
        pause_window.set_message_text(position.x+650,position.y+300,"YOU WIN!");
    pause_window.set_score_text(position.x+750,position.y+420,"Score: " + to_string(game.get_total_score()));
    game.draw(window,view);
    pause_window.draw(window);
    if (pause_window.is_clicked(0,window))
    {
        game.set_map(MAP_OF_GAME);
        sound.play();
        return GAMING;
    }
    else if (pause_window.is_clicked(1,window))
        return BUILD_MAP;
    return status;
}