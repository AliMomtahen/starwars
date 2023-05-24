#ifndef _SHOT_CLASS
#define _SHOT_CLASS




#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include"../func.hpp"
#include"../src/rsdl.hpp"

const std::string SHOT_SHAPE = "";
const int SHOT_VELOCITY = 14; 
const int SHOT_RADIUS = 5;

class Shot{
protected:
    std::string type;
    std::string shape;
    int x;
    int y;
    int height;
    int width;
    int velocity;
    



public:
    int radius;
    Shot();
    Shot(std::string _type ,std::string _shape , int _x , int  _y , int _velocity);
    virtual void draw_self(Window *windoe);
    void set_center(Point new_center);
    void set_type(std::string new_type){ type = new_type;}
    void update(Window *window);
    std::string get_type(){ return type;}
    Point get_center(){ return Point(x , y);}

};


class EnemyShot : public Shot{
private:


public:
    EnemyShot();
    EnemyShot(std::string _type ,std::string _shape , int _x , int  _y , int _velocity);
    std::string get_type(){ return type;}
    virtual void draw_self(Window *Window);
};


#endif
