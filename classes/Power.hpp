#ifndef _POWER_CLASS
#define _POWER_CLASS


#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<cmath>
#include"../func.hpp"
#include"../src/rsdl.hpp"


const time_t REMAIN_TIME = 6;
const std::string SHIELD_SHAPE = "./assets/shield.png";
const std::string SPEEDPOWER_SHAPE = "./assets/fire.png";
const std::string SPEED = "SpeedPower";
const std::string SHIELD = "ShieldPower";



class Power{
protected:
    std::string type;
    std::string shape;
    int x;
    int y;
    int height;
    int width;
    int radius;
    time_t creating_time;


public:
    Power();
    Power(int _x , int _y , int _width , int _height);
    bool is_avaible;
    void set_time_creat(){ creating_time = time(NULL) ; }
    std::string get_type(){ return type;}
    int get_radius(){ return height / 2;}
    Point get_center(){ return Point(x ,y);}
    void draw_self(Window *Window);
    void update(Window *window);

};

class SpeedPower :public Power{

private:

public:
    SpeedPower();
    SpeedPower(int _x , int _y , int _width , int _height);
};


class ShieldPower :public Power{

private:

public:
    ShieldPower();
    ShieldPower(int _x , int _y , int _width , int _height);

};









#endif
