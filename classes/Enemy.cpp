#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include"../src/rsdl.hpp"
#include"Enemy.hpp"
#include"Shot.hpp"



Enemy::Enemy(){
    type = "";
    x = 0;
    y = 0;
    height = CELL_SIZE;
    width= CELL_SIZE;
    befor_shot = 0;
    shape = ENEMY_SHAPE;
    is_alive = true;
}

Enemy::Enemy(int _x , int _y , std::string _type){

    type  = _type;
    x = _x;
    y = _y;
    height = CELL_SIZE;
    width= CELL_SIZE;
    befor_shot = 0;
    shape = ENEMY_SHAPE;
    is_alive = true;

}

Point Enemy::get_center(){
    return Point(x + width / 2 , y + height / 2);
}

bool Enemy::encountered(Point center , int radius){
    if(distanc(center , Point(x + width / 2 , y + height / 2))  < radius + (height / 2))
        return 1;
    return 0;    
}

Point Enemy::check_encounter_whit_shots(std::vector<Shot> &shots){
    for(int i=0 ; i < shots.size() ; i++){
        if(encountered(shots[i].get_center() , shots[i].radius)){
            Point befor_Point(x , y);
            x = -1000;
            y = -1000;
            is_alive = false;
            shots[i].set_center(NULL_POINT);
            shots[i].set_type("");
            return befor_Point;
        }
    }
    return NULL_POINT;
}


void Enemy::draw_self(Window *window){
    if(is_alive)
        window->draw_img(shape , Rectangle(Point(x ,y) , width , height));
}

void Enemy::fire(std::vector<EnemyShot> &shot_list){
    if(!is_alive)
        return;
    for(int i=0 ; i < shot_list.size() ; i++){
        if(shot_list[i].get_type() == ""){
            shot_list[i] = EnemyShot("Enemy" , SHOT_SHAPE , x + width/2 , y + height , -SHOT_VELOCITY);
            return;
        }
    }
    shot_list.push_back(EnemyShot("Enemy" , SHOT_SHAPE , x + width/2 , y + height , -SHOT_VELOCITY));
    
}

void Enemy::start_shooting(std::vector<EnemyShot>& shot_list){
    
    if(befor_shot == 0){
        if(rand() % 500  < 100){
            fire(shot_list);
            befor_shot = time(NULL);
        }
    }
}

void Enemy::update(Window *window , std::vector<EnemyShot>& shot_list){
    
}



MovingEnemy::MovingEnemy() :Enemy(){

    x_velocity = ENEMY_VELOCITY;
}

MovingEnemy::MovingEnemy(int x , int y , std::string _type) :Enemy(x , y , _type){
    x_velocity = ENEMY_VELOCITY;
    
}

void MovingEnemy::move(Window *window){
    if((x <= 0 && x_velocity < 0 )|| ( x + width > window->get_width() &&  x_velocity > 0 ))
        x_velocity *= -1;
    x = x + x_velocity;    
    
}

void MovingEnemy::update(Window *window , std::vector<EnemyShot>& shot_list){
    
    if( is_alive ){
        move(window);
        Enemy::update(window , shot_list);
    }
    
}












