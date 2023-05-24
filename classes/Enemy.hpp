#ifndef _ENEMY_CLASS
#define _ENEMY_CLASS


#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include"../src/rsdl.hpp"
#include"Shot.hpp"
#include"../func.hpp"



const std::string ENEMY_SHAPE = "./assets/enemy.png"; 
const int ENEMY_VELOCITY = 10;
const Point NULL_POINT(-30 , -30); 

class Enemy{
protected:

    std::string type;
    std::string shape;
    int x;
    int y;
    int height;
    int width;
    time_t befor_shot;


public:
    Enemy();
    Enemy(int x , int y , std::string _type);
    bool is_alive;
    void fire(std::vector<EnemyShot>& shot_list);
    void draw_self(Window *window);
    void start_shooting(std::vector<EnemyShot>& shot_list);
    Point get_center();
    int get_radius(){ return height / 2 ;}
    int get_column(){ return x;}
    bool encountered(Point center , int radius);
    Point check_encounter_whit_shots(std::vector<Shot> &shots);
    virtual void update(Window *window , std::vector<EnemyShot>& shot_list);

    

};




class MovingEnemy : public Enemy{
private:
    int x_velocity;
    
    
public:
    MovingEnemy();
    MovingEnemy(int x , int y , std::string _type);
    virtual void update(Window *window , std::vector<EnemyShot>& shot_list);
    void move(Window *window);

};




#endif 
