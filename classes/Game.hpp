#ifndef _GAME_CLASS
#define _GAME_CLASS

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>

#include"../src/rsdl.hpp"
#include"Ship.hpp"
#include"../classes/Enemy.hpp"
#include"Shot.hpp"
#include"../func.hpp"
#include"Power.hpp"



const int END_GAME = 0;
const int WIN_MODE = 2;
const int LOSE_MODE = 1;
const int RUN_MODE = 3;
const int HARD_GAME = 1;
const int MEDIUM_GAME = 2;
const int EASY_GAME = 3;
const int MAX_LOOP_COUNTER = 45;
const int POWER_CHANCE = 20;
const int SPEED_POWER_CHANCE = 50;
const int SHOT_CHANCE = 80;
const std::string GAME_OVER_NOT = "./assets/GAME_OVER.png";
const std::string WIN_NOT = "./assets/WON.png";
const std::string BG = "./assets/bg.jpg";
const std::string MUSIC_OF_GAME = "./assets/music.mp3";    
const std::string FONT_USED = "OpenSans.ttf";
const std::string NEXT_ROUND = "./assets/next_round.png";
const std::string FINAL_ROUND = "./assets/FINAL.png";
const std::string HARD = "Hard";
const std::string MEDIUM = "Medium";
const std::string EASY = "Easy";



class Game{
private:
    Window *window;
    Ship my_ship;
    std::vector<Hostage> hostage_ships;
    std::vector<Enemy *> enemies;
    std::vector<Power *> powers;
    int height_window;
    int width_window;
    int column;
    int row;
    int rounds_game;
    int game_difficulty;
    std::vector<Shot> my_shots;
    std::vector<EnemyShot> enemy_shots;


    
public:
    Game();
    Game( int height  , int width , std::string shape );
    int game_mode;
    void run(std::ifstream &map);
    bool run_round(std::ifstream &map);
    void get_map(std::ifstream &map);
    bool get_and_handle_events();
    void update_game_info();
    void update_shots();
    void update_enemies();
    void update_powers();
    void update_hostages();
    void print_next_round(int round_now);
    void draw();
    void start_shooting(int &countering_loop);
    int check_encounter();
    void draw_shots();
    void draw_enemy();
    void draw_hostages();
    void draw_powers();
    void print_notification(std::string notification);
    void creat_power(Point index);
    void do_my_shot_result();
    void free_enemies();
    void free_power();
    bool encounter_whit_hostages();


};







#endif 
