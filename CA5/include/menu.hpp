#if !defined(__MENU__)
#define __MENU__

#include "manual.hpp"
#include "game.hpp"

void set_sounds(vector<SoundBuffer*> &buffers, vector<Sound*> &sounds, RenderWindow &window);

Status build_start_window(RenderWindow &window, Game &game, NewWindow &start_window, Sound &sound);

Status build_pause_window(RenderWindow &window, Game &game, NewWindow &pause_window , View &view);

Status build_end_game_window(RenderWindow &window, Game &game, NewWindow &pause_window, View &view, Status status, Sound &sound);

#endif