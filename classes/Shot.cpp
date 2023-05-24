
#include<iostream>
#include<vector>
#include<string>
#include"Shot.hpp"






Shot::Shot(){
    type = "for_enemy";
    shape = SHOT_SHAPE;
    x = 0; 
    y = 0;
    height = 2 * SHOT_RADIUS;
    width = 2 * SHOT_RADIUS;
    velocity = SHOT_VELOCITY;
    radius = SHOT_RADIUS;
}


Shot::Shot(std::string _type ,std::string _shape , int _x , int  _y , int _velocity){
    type = _type;
    shape = _shape;
    x = _x; 
    y = _y;
    height = 2 * SHOT_RADIUS;
    width = 2 * SHOT_RADIUS;
    velocity = _velocity;
    radius = SHOT_RADIUS;

}

void Shot::draw_self(Window *window){
        window->fill_circle(Point(x ,y) ,  radius , YELLOW);

}

void Shot::set_center(Point new_center){
    x = new_center.x;
    y = new_center.y;
}

void Shot::update(Window *window){
    y = y - velocity;
    if(y > window->get_height() || y < 0 )
        type = "";
    
}

EnemyShot::EnemyShot() : Shot(){

}

EnemyShot::EnemyShot(std::string _type ,std::string _shape , int _x , int  _y , int _velocity) 
    : Shot(_type , _shape , _x , _y , _velocity){

}


void EnemyShot::draw_self(Window *window){
    window->fill_circle(Point(x , y) , radius , BLUE);
}









