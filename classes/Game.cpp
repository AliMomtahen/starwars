#include"Game.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>


Game::Game(){
    game_mode = RUN_MODE;
}

Game::Game( int height  , int width , std::string shape ){
    window = new Window(width ,height);
    
    std::string name = "Ali"; 
    Ship new_ship( "Ali",shape ,rand() % width , height - CELL_SIZE);
    height_window = height;
    width_window = width;
    column = width / CELL_SIZE;
    row = height / CELL_SIZE;
    my_ship = new_ship;
    game_mode = RUN_MODE;
}


void Game::get_map(std::ifstream& map){
    std::string input;

    for(int i=0 ; i < row ; i++){
        map >> input;
        for(int j=0 ; j < input.size() ; j++){
            switch(input[j]){
            case 'S':
                hostage_ships.push_back(Hostage("hostage" , HOSTAGE_SHAPE , j * CELL_SIZE , i * CELL_SIZE , true));
                break;    
            case 'M':
                enemies.push_back(new MovingEnemy(j * CELL_SIZE, i * CELL_SIZE , "enemy"));
                break;
            case 'E':
                enemies.push_back( new Enemy(j * CELL_SIZE, i * CELL_SIZE , "enemy"));
                break;
            case '.':
                break;    
            
            default:
                break;
            }
        }        
    }
    map >> input;
    if(input == HARD)
        game_difficulty = HARD_GAME;
    else if(input == MEDIUM)
        game_difficulty == MEDIUM_GAME;    
    else
        game_difficulty == EASY_GAME;
    
}

void Game::print_notification(std::string notification){

    window->draw_img(notification , Rectangle( Point(0 , height_window / 2 - 50) , width_window , 100 )); 
            
    window->update_screen();
}


void Game::draw_shots(){
    for(int i = 0 ; i < enemy_shots.size() ; i++){
        enemy_shots[i].draw_self(window);
    }
    for(int i = 0 ; i < my_shots.size() ; i++){
        my_shots[i].draw_self(window);
    }
}

void Game::draw_enemy(){
    for(int i = 0 ; i < enemies.size() ; i++){
        enemies[i]->draw_self(window);
    }

}


void Game::start_shooting(int &countering_loop){
    srand(time(NULL));
    if(countering_loop < MAX_LOOP_COUNTER)
        return;

    countering_loop = 0;    
    int counter = 0;
    std::vector< int> column_shot(column , 1);

    for(int i=0; i < game_difficulty ; i++){
        int index = rand() % column;
        if(column_shot[index] != 0)
            column_shot[index] = 0;
        else{
            i--;
        }    
    }

    for(int i=0; i < enemies.size() ; i++){
        if(column_shot[enemies[i]->get_column() / CELL_SIZE ] == 1  && 
                rand() % 100 < SHOT_CHANCE)
            
            enemies[i]->fire(enemy_shots);
    }
}

void Game::draw_powers(){
    for(int i=0 ;i < powers.size() ; i++){
        powers[i]->draw_self(window);

    }
}

void Game::draw(){
    my_ship.draw_self(window);
    draw_hostages();
    draw_enemy();
    draw_shots();
    draw_powers();
    window->update_screen();

}

void Game::creat_power(Point index){
    
    int chance = rand() % 100;
    if(chance < POWER_CHANCE){
        chance = rand() % 100;
        if(chance > SPEED_POWER_CHANCE){
            
            powers.push_back(new SpeedPower(index.x , index.y , CELL_SIZE  , CELL_SIZE));
        }
        else{

            powers.push_back(new ShieldPower(index.x , index.y , CELL_SIZE , CELL_SIZE));
        }
    }
}


void Game::do_my_shot_result(){
    bool all_enemies_died = true;
    for(int i=0; i < enemies.size() ; i++){
        if(enemies[i]->is_alive){
            all_enemies_died = false;
            Point enemy_point = enemies[i]->check_encounter_whit_shots(my_shots);
            if(enemy_point.x != NULL_POINT.x)
                creat_power(enemy_point);
        }

    }
    if(all_enemies_died)
        game_mode = WIN_MODE;
    else
        game_mode = RUN_MODE;    
}


void Game::draw_hostages(){
    for(int i=0 ; i < hostage_ships.size() ; i++){
        hostage_ships[i].draw_self(window);
    }
}


void Game::free_enemies(){
    for(int i=0 ; i < enemies.size() ; i++){
        delete enemies[i];
    }
}

bool Game::encounter_whit_hostages(){
    for(int i=0 ; i < hostage_ships.size() ; i++){
        if(hostage_ships[i].is_alive &&  hostage_ships[i].encountered_whit_my_shots(my_shots))
            return 1;

        if(hostage_ships[i].is_alive && 
                my_ship.encountered(hostage_ships[i].get_center() , hostage_ships[i].get_radius()))

                    return 1;    
    }


    return 0;
}


int Game::check_encounter(){
    bool game_over = false;
    game_over = my_ship.encountered_shots(enemy_shots);
    if(game_over)
        return 1;
    game_over = encounter_whit_hostages();
    if(game_over)
        return 1;    
    game_over = my_ship.encountered_enemies(enemies);
    if(game_over)
        return 1;

    my_ship.check_encounter_powers(powers);  

    do_my_shot_result();              
    return game_over; 

}

bool Game::run_round(std::ifstream &map){
        bool game_not_exit = true;
        bool game_over = false;
        game_mode = RUN_MODE;
        get_map(map);
        my_ship.set_random_index(window);
        int counter = MAX_LOOP_COUNTER - 5;
        
        while(game_not_exit){
            window->clear();
            window->draw_img(BG , Rectangle(Point(0 , 0) , Point(width_window , height_window)));
            game_not_exit = get_and_handle_events();
            if(!game_not_exit)
                break;
            
            start_shooting(counter);
                
             
            
                
            update_game_info();
            game_over = check_encounter();
            draw();
            if(game_over){
                game_mode = LOSE_MODE;
                print_notification(GAME_OVER_NOT);
                return 0;
            }
            if(game_mode == WIN_MODE)
                break;

            counter++;    
            delay(50); 
        }
        
        free_enemies();
        free_power();
        enemies.clear();
        my_shots.clear();
        enemy_shots.clear();
        hostage_ships.clear();
        window->clear();
        return 1;
}

void Game::print_next_round(int round_now){
    int counter = 0 ;
    double size = 0.01;
    std::string notification ;
    if(round_now < (rounds_game - 2))
        notification = NEXT_ROUND;
    else if(round_now == rounds_game - 2) 
        notification = FINAL_ROUND;    
    for(int i=0 ; i < 100 ; i++){
        window->clear();
        int width_image =  width_window * size;
        int height_image = height_window * size;
        window->draw_img(notification , Rectangle(Point(0 , 0) , width_image , height_image));
        window->update_screen();
        size += 0.01;
        delay(10);
    }
    window->clear();
}



void Game::run(std::ifstream &map){

    
    map >> rounds_game;
    
    
    bool not_game_over = true;
    
    window->play_music(MUSIC_OF_GAME);
    for(int i=0 ; i < rounds_game && not_game_over; i++){
        not_game_over = run_round( map );
        if(game_mode == END_GAME)
            return;
        if(game_mode == WIN_MODE && i < rounds_game - 1)
            print_next_round(i);
            
        delay(2000);
    }
    if(game_mode == WIN_MODE)
        print_notification(WIN_NOT);
    delay(2000);
}


void Game::update_hostages(){
    for(int i=0; i < hostage_ships.size() ; i++){
        hostage_ships[i].update(window , my_shots);
    }
}



bool Game::get_and_handle_events(){

    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch (event.get_type()) {
            case Event::QUIT:
                game_mode = END_GAME;
                return 0;
                break;
            case Event::KEY_PRESS:
                my_ship.handle_key_pressing(event.get_pressed_key());

                
                break;
            case Event::KEY_RELEASE:
                my_ship.handle_key_released(event.get_pressed_key());

                
                break;
            }
    }
    return 1;
}


void Game::update_shots(){
    for(int i=0 ; i < my_shots.size() ; i++ ){
        my_shots[i].update(window);
        
    }
    for(int i=0 ; i < enemy_shots.size() ; i++ ){
        enemy_shots[i].update(window);
        

    }
    
}

void Game::update_enemies(){
    for(int i=0; i < enemies.size() ; i++){
        enemies[i]->update(window , enemy_shots);
    }
}

void Game::update_game_info(){
    my_ship.update(window , my_shots);
    update_hostages();
    
    update_enemies();
    update_shots();
    update_powers();
    
}


void Game::update_powers(){
    for(int i=0 ;i < powers.size() ; i++){
        powers[i]->update(window);

    }
}



void Game::free_power(){
    for(int i=0 ;i < powers.size() ; i++){
        delete powers[i];


    }
    powers.clear();
}



