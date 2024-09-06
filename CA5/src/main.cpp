#include <../include/manual.hpp>
#include <../include/player.hpp>
#include <../include/block.hpp>
#include <../include/new_window.hpp>
#include <../include/game.hpp>
#include <../include/menu.hpp>


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Turtix!");
    View view(FloatRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    window.setView(view);
    Clock clock_mode;
    Clock clock;
    Status status = BUILD_MAP;
    NewWindow start_window(0,0,"./pictures/start.jpg",start_images);
    NewWindow pause_window(0,0,"./pictures/window.png",pause_images);
    NewWindow end_game_window(0,0,"./pictures/window.png",end_game_images);
    vector<SoundBuffer*> buffers;
    vector<Sound*> sounds;
    set_sounds(buffers,sounds,window);
    Game game(sounds);

    while (window.isOpen())
    {
        game.handle_events(window);
        switch (status)
        {
        case START:
            status = build_start_window(window,game,start_window,*sounds[START_S]);
            break;
        case GAMING:
            status = game.handle_game(window,view,clock,clock_mode);
            break;
        case PAUSE:
            status = build_pause_window(window,game,pause_window,view);
            break;
        case WIN:
            status = build_end_game_window(window,game,end_game_window,view,status,*sounds[START_S]);
            break;
        case LOOSE:
            status = build_end_game_window(window,game,end_game_window,view,status,*sounds[START_S]);
            break;
        case BUILD_MAP:
            game.set_map(MAP_OF_GAME);
            status = START;
            break;
        default:
            break;
        }
        window.display();
    }
    return 0;
}




