#ifndef _SHIP_CLASS
#define _SHIP_CLASS

#include<iostream>
#include<string>
#include<vector>
#include"../src/rsdl.hpp"
#include"Shot.hpp"
#include"../func.hpp"
#include"Enemy.hpp"
#include"Power.hpp"

const int SHIP_VELOCITY = 17;
const std::string  SHIP_SHAPE = "./assets/ship.png";
const std::string  SHIP_SHAPE_IN_SHIELD = "./assets/ship_shield.png";
const std::string  HOSTAGE_SHAPE = "./assets/hostage.png";




class Ship{
public:
    Ship();
    Ship(std::string _name , std::string shap  , int _x ,  int _y);
    bool is_alive;
    void move(Window *window , int x_moving , int y_moving);
    void handle_key_pressing(char key_pressed);
    void handle_key_released(char key_pressed);
    void draw_self(Window *window);
    void update(Window *window , std::vector<Shot>& shots_list);
    void shoot(std::vector<Shot>& shots_list);
    void change_shape();

    bool encountered_whit_my_shots(std::vector<Shot> &enemy_shots); 
    bool encountered(Point center , int radius);
    bool encountered_shots(std::vector<EnemyShot> &enemy_shots);
    bool encountered_enemies(std::vector<Enemy*> &enemies);
    bool check_encounter_powers(std::vector< Power *>& powers);
    bool is_end_of_power();
    void eat_power(std::string type_power);
    void set_random_index(Window *window);
    Point get_center();
    int get_radius(){ return height / 2 ;}

    

protected:

    std::string shap_of_ship;


    std::string name;
    int x;
    int y;
    int x_velocity;
    int y_velocity;
    int height;
    int width;

    time_t start_power_mode;
    bool power_mode;
    bool shield_mode;
    bool speed_mode;
    bool is_shooting;
    bool permission_shooting;
    int shot_power;

};



class Hostage : public Ship{
private:

public:
    
    Hostage();
    Hostage(std::string _name , std::string shap  , int _x ,  int _y , bool life);
    void release(Window *window);
    
};








#endif
