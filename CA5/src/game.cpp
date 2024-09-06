#include <../include/game.hpp>

Game::Game(vector<Sound*> new_sounds) : player(PLAYER_POSITION_X, PLAYER_POSITION_Y, PLAYER_SPEED, player_images, true) ,
               background(0,0,"./pictures/game_background.png") ,
               button(0,0,"./pictures/menu_button.png",{"menu_button"})
{
    game_starting = false;
	font.loadFromFile("font/arialbd.ttf");
	star_text.setFont(font);
	star_text.setCharacterSize(SCORE_FONT_SIZE);
	star_text.setFillColor(Color::Black);
    gem_text.setFont(font);
	gem_text.setCharacterSize(SCORE_FONT_SIZE);
	gem_text.setFillColor(Color::Black);
    sounds = new_sounds;
}

vector<string> Game::make_apart(string line_of_file , char separator)
{
    string file_element;
    vector<string> inputs;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator)) 
    {
        inputs.push_back(file_element);
    }
    return inputs;
}

void Game::set_base_details()
{
    player.change_position(PLAYER_POSITION_X,PLAYER_POSITION_Y);
    player.make_scores_zero();
    player.change_num_of_lives(NUMBER_OF_HEARTS);
    started = true;

    blocks.clear();
    thorns.clear();
    turtles.clear();
    gates.clear();
    weak_enemies.clear();
    strong_enemies.clear();
    gems.clear();
    stars.clear();
    hearts.clear();
    for (int i = 0; i < NUMBER_OF_HEARTS; i++)
        hearts.push_back(new Block(0,0,"./pictures/dead_heart.png"));
    for (int i = 0; i < NUMBER_OF_HEARTS; i++)
        hearts.push_back(new Block(0,0,"./pictures/heart.png"));
}

void Game::build_map(string flag , vector<string> inputs)
{
    if (flag == "blocks")
        blocks.push_back(new Block(stoi(inputs[0]),stoi(inputs[1]),"./pictures/" + inputs[2] + ".png")); 
    else if (flag == "thorns")
        thorns.push_back(new Block(stoi(inputs[0]),stoi(inputs[1]),"./pictures/" + inputs[2] + ".png"));
    else if (flag == "turtles")
        turtles.push_back(new Player(stoi(inputs[0]),stoi(inputs[1]),TURTLE_SPEED,turtle_images,true));
    else if (flag == "gates")
        gates.push_back(new Block(stoi(inputs[0]),stoi(inputs[1]),"./pictures/" + inputs[2] + ".png")); 
    else if (flag == "weak_enemies")
        weak_enemies.push_back(new Player(stoi(inputs[0]),stoi(inputs[1]),BASE_ENEMY_SPEED+stoi(inputs[2]),weak_enemy_images,false));
    else if (flag == "strong_enemies")
        strong_enemies.push_back(new Player(stoi(inputs[0]),stoi(inputs[1]),BASE_ENEMY_SPEED+stoi(inputs[2]),strong_enemy_images,false));
    else if (flag == "gems")
        gems.push_back(new Block(stoi(inputs[0]),stoi(inputs[1]),"./pictures/" + inputs[2] + ".png")); 
    else if (flag == "stars")
        stars.push_back(new Block(stoi(inputs[0]),stoi(inputs[1]),"./pictures/" + inputs[2] + ".png")); 
    else
        return;
}

void Game::set_map(string address)
{
    string flag;
    string line_of_file;
    vector<string> inputs;
    ifstream input_file(address);
    set_base_details();
    while (getline(input_file, line_of_file)) 
    {
        inputs = make_apart(line_of_file,',');
        if (inputs[0] == "blocks")
            flag = "blocks";
        else if (inputs[0] == "thorns")
            flag = "thorns";
        else if (inputs[0] == "turtles")
            flag = "turtles";
        else if (inputs[0] == "gates")
            flag = "gates";
        else if (inputs[0] == "weak_enemies")
            flag = "weak_enemies";
        else if (inputs[0] == "strong_enemies")
            flag = "strong_enemies";
        else if (inputs[0] == "gems")
            flag = "gems";
        else if (inputs[0] == "stars")
            flag = "stars";
        else
            build_map(flag,inputs);
    }
    input_file.close();
}

void Game::set_details_position(View &view)
{
    background.set_position(view.getCenter().x-WINDOW_WIDTH/2,view.getCenter().y-WINDOW_HEIGHT/2);
    gems[0]->set_position(background.get_position().x + 1700 , background.get_position().y + 150);
    stars[0]->set_position(background.get_position().x + 1692 , background.get_position().y + 250);
    gem_text.setPosition(background.get_position().x + 1620 , background.get_position().y + 140);
    star_text.setPosition(background.get_position().x + 1620 , background.get_position().y + 250);
    if (player.get_num_of_stars() >= 10)
        star_text.setPosition(background.get_position().x + 1580 , background.get_position().y + 250);
    gem_text.setString(to_string(player.get_num_of_gems()));
    star_text.setString(to_string(player.get_num_of_stars()));
    button.set_position(background.get_position().x+50,background.get_position().y+50);
    button.set_icon_position(0,background.get_position().x+50,background.get_position().y+50);
}

void Game::set_hearts_position()
{
    int new_x = background.get_position().x + 1700;
    int new_y = background.get_position().y + 50;
    for (int i = 0; i < NUMBER_OF_HEARTS; i++)
    {
        hearts[i]->set_position(new_x - i*100,new_y);
        hearts[i+NUMBER_OF_HEARTS]->set_position(new_x - i*100,new_y);
    }
}

void Game::draw(RenderWindow &window ,View &view)
{
    window.clear();
    set_details_position(view);
    set_hearts_position();
    
    background.draw(window);
    for (int i = 0; i < blocks.size(); i++)
        blocks[i]->draw(window);
    for (int i = 0; i < gates.size(); i++)
        gates[i]->draw(window);   
    for (int i = 0; i < thorns.size(); i++)
        thorns[i]->draw(window);
    for (int i = 0; i < turtles.size(); i++)
        turtles[i]->draw(window);
    for (int i = 0; i < weak_enemies.size(); i++)
        weak_enemies[i]->draw(window);
    for (int i = 0; i < strong_enemies.size(); i++)
        strong_enemies[i]->draw(window);
    for (int i = 0; i < stars.size(); i++)
        stars[i]->draw(window);
    for (int i = 0; i < gems.size(); i++)
        gems[i]->draw(window);
    for (int i = 0; i < NUMBER_OF_HEARTS + player.get_lives(); i++)
        hearts[i]->draw(window);
    window.draw(gem_text);
    window.draw(star_text);
    button.draw(window);
    player.draw(window);
    view.setCenter(player.get_position().x,player.get_position().y+100);
    window.setView(view);
}

void Game::decrease_player_life()
{
    player.decrease_num_of_lives(1);
    if (player.get_lives() > 0)
    {
        sounds[START_S]->play();
        player.change_position(PLAYER_POSITION_X,PLAYER_POSITION_Y);
    }
}

bool Game::can_move_to_blocks(vector<Block*> &walls ,Direction direction)
{
    for (int i = 0; i < walls.size() ; i++)
    {
        if (direction == LEFT && (i==8 || i==21))
            continue;
        if (direction == RIGHT && i==7 & player.get_position().y <= walls[i]->get_position().y)
            continue;
        if (direction == LEFT && walls[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x >= walls[i]->get_position().x + walls[i]->get_size().x - STEP_SIZE)
            return false;
        if (direction == RIGHT && walls[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x + player.get_size().x - STEP_SIZE <= walls[i]->get_position().x)
            return false;   
    }
    return true;
}

bool Game::can_move_to_enemies(vector<Player*> &enemies ,Direction direction)
{
    for (int i = 0; i < enemies.size() ; i++)
    {
        if (!enemies[i]->is_draw())
            continue;
        if (direction == LEFT && enemies[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x >= enemies[i]->get_position().x + enemies[i]->get_size().x - STEP_SIZE - enemies[i]->get_speed())
        {
            decrease_player_life();
            return false;
        }
        if (direction == RIGHT && enemies[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x + player.get_size().x - STEP_SIZE - enemies[i]->get_speed() <= enemies[i]->get_position().x)
        {
            decrease_player_life();
            return false;   
        }
    }
    return true;
}

void Game::move_player(Direction direction)
{
    if (!started)
        return;
    if (!can_move_to_blocks(blocks,direction))
        return;
    if (!can_move_to_enemies(weak_enemies,direction))
        return;
    if (!can_move_to_enemies(strong_enemies,direction))
        return;
    for (int i = 0; i < turtles.size() ; i++)
        if (direction == LEFT && turtles[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x >= turtles[i]->get_position().x && !turtles[i]->is_free())
            return;
        else if (direction == RIGHT && turtles[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && 
            player.get_position().x <= turtles[i]->get_position().x && !turtles[i]->is_free())
            return;   
    player.move(direction);
}

void Game::handle_events(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        else if (!game_starting)
            return;
        else if (event.key.code == Keyboard::Left) 
            move_player(LEFT);
        else if (event.key.code == Keyboard::Right) 
            move_player(RIGHT);
        else if (event.key.code == Keyboard::Up) 
            move_player(UP);  
        else if (event.key.code == Keyboard::Space) 
            start();
    }
}

bool Game::can_jump(Player object)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
            object.get_position().y <= blocks[i]->get_position().y &&
            object.get_position().x + object.get_size().x - GAP >= blocks[i]->get_position().x &&
            object.get_position().x <= blocks[i]->get_position().x + blocks[i]->get_size().x - GAP)
            return true;
    }
    return false;
}

void Game::jump(Player &object , bool flag)
{
    if (!started)
        return;
    else if (!can_jump(object))
        object.set_gravity(GRAVITY);
    else if (Keyboard::isKeyPressed(Keyboard::Up) && flag)
    {
        sounds[JUMP_S]->play();
        object.change_jump_mode(JUMP_FIRST_AMOUNT);
    }
    else
        object.change_jump_mode(0);

    for (int i = 0; i < blocks.size(); i++)
    {
        if (i == 1 || i == 10)
            continue;
        if (blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
            object.get_position().y >= blocks[i]->get_position().y + blocks[i]->get_size().y/2 &&
            object.get_position().x + object.get_size().x >= blocks[i]->get_position().x + PLAYER_SPEED+1 &&
            object.get_position().x + PLAYER_SPEED+1 <= blocks[i]->get_position().x + blocks[i]->get_size().x)
            object.change_jump_mode(4);
    }
    if (flag)
        move_player(UP);
    else
        object.move(UP);
}

void Game::start()
{
    started = true;
}

void Game::find_direction()
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
        move_player(LEFT);
    else if (Keyboard::isKeyPressed(Keyboard::Right))
        move_player(RIGHT);
    else if (Keyboard::isKeyPressed(Keyboard::Space))
        start();
    jump(player,true);
}

bool Game::is_over()
{
    return player.get_lives() <= 0;
}

bool Game::is_win()
{
    int count = 0;
    for (int i = 0; i < turtles.size(); i++)
        if (!turtles[i]->is_draw())
            count++;
    return (gates[0]->getGlobalBounds().intersects(player.getGlobalBounds()) && count == turtles.size());
}

void Game::free_turtles()
{
    for (int i = 0; i < turtles.size(); i++)
    {
        if(turtles[i]->is_free())
            continue;
        if (turtles[i]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y <= turtles[i]->get_position().y &&
            player.get_position().x + player.get_size().x - 5 >= turtles[i]->get_position().x &&
            player.get_position().x <= turtles[i]->get_position().x + turtles[i]->get_size().x - 5)
        {
            sounds[FREE_S]->play();
            turtles[i]->make_free_or_not(true);
            player.change_jump_mode(JUMP_HIT_AMOUNT);
            move_player(UP);
        }
    }
}

void Game::move_turtles()
{
    free_turtles();
    for (int i = 0; i < turtles.size(); i++)
    {
        Player object = *turtles[i];
        Direction direction = object.get_my_direction();
        if(!turtles[i]->is_free() || !turtles[i]->is_draw())
            continue;
        jump(*turtles[i],false);
        for (int i = 0; i < blocks.size() ; i++)
        {
            if (direction == LEFT && (i==8 || i==21))
            continue;
            if (direction == RIGHT && i==7 & object.get_position().y <= blocks[i]->get_position().y)
            continue;
            if (direction == LEFT && blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) && 
                object.get_position().x >= blocks[i]->get_position().x + blocks[i]->get_size().x - STEP_SIZE)
            {
                direction = RIGHT;
                break;
            }
            else if (direction == RIGHT && blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) && 
                object.get_position().x + object.get_size().x - STEP_SIZE <= blocks[i]->get_position().x)
            {
                direction = LEFT;
                break;
            }
        }
        turtles[i]->change_my_direction(direction);
        turtles[i]->move(direction);
    }
}

void Game::turtles_get_home()
{
    for (int i = 0; i < turtles.size(); i++)
        if (gates[0]->getGlobalBounds().intersects(turtles[i]->getGlobalBounds()))
            turtles[i]->make_draw_or_not(false);
}

void Game::touch_thorns()
{
    for (int i = 0; i < thorns.size(); i++)
    {
        if (thorns[i]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y + player.get_size().y >= thorns[i]->get_position().y + 25 &&
            player.get_position().x + player.get_size().x >= thorns[i]->get_position().x + 20 &&
            player.get_position().x + 20 <= thorns[i]->get_position().x + thorns[i]->get_size().x)
        {
            decrease_player_life();
            return;
        }
    }
}

void Game::touch_enemies(vector<Player*> &enemies)
{
    for (int i = 0; i < enemies.size() ; i++)
    {
        if (!enemies[i]->is_draw())
            continue;
        if (enemies[i]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y + player.get_size().y >= enemies[i]->get_position().y + 10  &&
            player.get_position().x + player.get_size().x >= enemies[i]->get_position().x + 30 &&
            player.get_position().x + 30 <= enemies[i]->get_position().x + enemies[i]->get_size().x)
        {
            decrease_player_life();
            return;
        }
    }
}

void Game::kill_enemies(vector<Player*> &enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if(!enemies[i]->is_draw() || !started)
            continue;
        if (enemies[i]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y + 3*player.get_size().y/4 <= enemies[i]->get_position().y &&
            player.get_position().x + player.get_size().x  >= enemies[i]->get_position().x + 11 &&
            player.get_position().x + 11 <= enemies[i]->get_position().x + enemies[i]->get_size().x )
        {
            sounds[HIT_S]->play();
            enemies[i]->decrease_num_of_lives(1);
            if (enemies[i]->get_lives() >= 1)
                player.change_jump_mode(JUMP_HIT_AMOUNT);
            else if (enemies[i]->get_lives()  == 0)
                player.change_jump_mode(-2*JUMP_HIT_AMOUNT);
            move_player(UP);
        }
    }
}

void Game::move_enemies(vector<Player*> &enemies)
{
    if (!started)
        return;
    for (int i = 0; i < enemies.size(); i++)
    {
        Player object = *enemies[i];
        Direction direction = object.get_my_direction();
        if(!enemies[i]->is_draw())
            continue;
        jump(*enemies[i],false);
        for (int i = 0; i < blocks.size() ; i++)
        {
            if (direction == LEFT && (i==8 || i==21))
            continue;
            if (direction == RIGHT && i==7 & object.get_position().y <= blocks[i]->get_position().y)
            continue;
            if (direction == LEFT && blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) && (
                object.get_position().x >= blocks[i]->get_position().x + blocks[i]->get_size().x - STEP_SIZE ||
                object.get_position().x <= blocks[i]->get_position().x))
            {
                direction = RIGHT;
                break;
            }
            else if (direction == RIGHT && blocks[i]->getGlobalBounds().intersects(object.getGlobalBounds()) && (
                object.get_position().x + object.get_size().x - STEP_SIZE <= blocks[i]->get_position().x || 
                object.get_position().x + object.get_size().x >= blocks[i]->get_position().x + blocks[i]->get_size().x))
            {
                direction = LEFT;
                break;
            }
        }
        enemies[i]->change_my_direction(direction);
        enemies[i]->move(direction);
    }
}

void Game::change_strong_enemy_mode()
{
    for (int i = 0; i < strong_enemies.size(); i++)
    {
        if (strong_enemies[i]->get_lives() == 1)
            strong_enemies[i]->change_num_of_lives(2);
        else if (strong_enemies[i]->get_lives() == 2)
            strong_enemies[i]->change_num_of_lives(1);
    }
}

void Game::handle_enemies()
{
    bool enemy_shield = false;
    touch_thorns();
    move_enemies(weak_enemies);
    kill_enemies(weak_enemies);
    touch_enemies(weak_enemies);
    move_enemies(strong_enemies);
    for (int i = 0; i < strong_enemies.size(); i++)
        if (strong_enemies[i]->get_lives() == 2)
            enemy_shield = true;
    if (!enemy_shield)
        kill_enemies(strong_enemies);
    touch_enemies(strong_enemies);
}

void Game::get_score()
{
    for (int i = 0; i < stars.size(); i++)
        if (stars[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && stars[i]->is_draw())
        {
            sounds[SCORE_S]->play();
            stars[i]->make_draw_or_not(false);
            player.increase_stars();
        }
    for (int i = 0; i < gems.size(); i++)
        if (gems[i]->getGlobalBounds().intersects(player.getGlobalBounds()) && gems[i]->is_draw())
        {
            sounds[SCORE_S]->play();
            gems[i]->make_draw_or_not(false);
            player.increase_gems();
        }
}

void Game::change_step()
{
    player.increase_step();
    for (int i = 0; i < turtles.size(); i++)
        turtles[i]->increase_step();
}

int Game::get_total_score()
{
    return GEM_SCORE*player.get_num_of_gems() + STAR_SCORE*player.get_num_of_stars();
}

Status Game::handle_game(RenderWindow &window, View &view, Clock &clock, Clock &clock_mode)
{ 
    Time elapsed_time_mode = clock_mode.getElapsedTime();
    Time elapsed_time = clock.getElapsedTime();
    find_direction();
    if (is_over())
    {
        sounds[GAME_OVER_S]->play();
        cout << "GAME OVER!" << endl;
        return LOOSE;
    }
    else if (is_win())
    {
        sounds[WIN_S]->play();
        cout << "YOU WIN!" << endl;
        return WIN;
    }
    if(elapsed_time_mode.asSeconds() >= ENEMY_CHANGE_MODE_TIME)
    {
        change_strong_enemy_mode();
        clock_mode.restart();
    }
    if(elapsed_time.asMilliseconds() >= CHANGE_MODE_TIME)
    {
        change_step();
        clock.restart();
    }
    handle_events(window);
    move_turtles();
    turtles_get_home();
    get_score();
    handle_enemies();
    draw(window,view);
    if (button.is_clicked(0,window))
    {
        sounds[PAUSE_S]->play();
        return PAUSE;
    }
    return GAMING;
}

Vector2f Game::get_window_position()
{
    return background.get_position();
}