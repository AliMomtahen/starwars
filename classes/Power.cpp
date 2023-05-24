#include"Power.hpp"




Power::Power(){
    x = 0;
    y = 0;
    width = CELL_SIZE;
    height = CELL_SIZE;
    radius = CELL_SIZE / 2;
    is_avaible = false;
    creating_time = 0;
    shape = SPEEDPOWER_SHAPE;
}


Power::Power(int _x , int _y , int _width , int _height){
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    radius = height / 2;
    is_avaible = true;
    creating_time = time(NULL);
}

void Power::draw_self(Window *window){
    if(is_avaible)
        window->draw_img(shape , Rectangle(Point(x ,y) , width , height));
}



void Power::update(Window *window){
    if(is_avaible){
        if(time(NULL) - creating_time <= REMAIN_TIME){

        }
        else
            is_avaible = false;
    }
}

ShieldPower::ShieldPower() : Power(){
    type = SHIELD;
    shape = SHIELD_SHAPE;
}

ShieldPower::ShieldPower(int _x , int _y , int _width , int _height) : Power(_x , _y , _width , _height) {
    type = SHIELD;
    shape = SHIELD_SHAPE;
}


SpeedPower::SpeedPower() : Power(){
    type = SPEED;
    shape = SPEEDPOWER_SHAPE;
}

SpeedPower::SpeedPower(int _x , int _y , int _width , int _height) : Power(_x , _y , _width , _height) {
    type = SPEED;
    shape = SPEEDPOWER_SHAPE;
}

