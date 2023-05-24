#include<iostream>
#include<string>
#include<vector>
#include"../src/rsdl.hpp"
#include"Ship.hpp"


Ship::Ship(){
    x = 0;
    y = 0;
    shap_of_ship = SHIP_SHAPE;
    is_shooting = false;
    shot_power = SHOT_VELOCITY;
    permission_shooting = true;
    is_alive = true;
    shield_mode = false;
    speed_mode = false;
    start_power_mode = 0;
}

Ship::Ship(std::string _name , std::string shap , int _x , int _y){
        name = _name;
        shap_of_ship = shap;
        x = _x;
        y = _y;
        is_alive = true;
        x_velocity = 0;
        y_velocity = 0;
        height = CELL_SIZE;
        width  = CELL_SIZE;
        shield_mode = false;
        speed_mode = false;
        permission_shooting = true;
        is_shooting = false;
        shot_power = SHOT_VELOCITY;

}

void Ship::move(Window *window , int x_moving , int y_moving){
        x = x + x_moving;
        y = y + y_moving;
        
}

Point Ship::get_center(){
    return Point(x + width / 2 , y + height / 2);
}

bool Ship::encountered(Point center , int radius){
    if(distanc(center , Point(x + width / 2 , y + height / 2))  < radius + (height / 2))
        return 1;
    return 0;    
}

bool Ship::encountered_shots(std::vector<EnemyShot> &enemy_shots){ 
    if(!is_alive || shield_mode)
        return 0;
    for(int i=0 ; i < enemy_shots.size() ; i++){
        if(encountered(enemy_shots[i].get_center() , enemy_shots[i].radius)){
            return 1;
        }
    }
    return 0;
}

bool Ship::encountered_whit_my_shots(std::vector<Shot> &enemy_shots){ 
    if(!is_alive)
        return 0;
    for(int i=0 ; i < enemy_shots.size() ; i++){
        if(encountered(enemy_shots[i].get_center() , enemy_shots[i].radius)){
            return 1;
        }
    }
    return 0;
}

bool Ship::encountered_enemies(std::vector<Enemy*> &enemies){
    if(!is_alive)
        return 0;
    for(int i=0 ; i < enemies.size() ; i++){
        if(encountered(enemies[i]->get_center() , enemies[i]->get_radius())){
            return 1;
        }
    }
    return 0;
}

bool Ship::check_encounter_powers(std::vector< Power *>& powers){
    for(int i=0; i < powers.size() ; i++){

        if(powers[i]->is_avaible  && 
            encountered(powers[i]->get_center() , powers[i]->get_radius()) ){

                powers[i]->is_avaible = false;
                eat_power( powers[i]->get_type() );
                
                return 1;

        }
    }
    return 0;
}

void Ship::eat_power(std::string type_power){
    
    if(type_power == SPEED){
        start_power_mode = time(NULL);
        speed_mode = true;
        
        shot_power = 2 * SHOT_VELOCITY;
    }
    else if(type_power == SHIELD){
        start_power_mode = time(NULL);
        shield_mode = true;
        
        shap_of_ship = SHIP_SHAPE_IN_SHIELD;

    }
}




void Ship::handle_key_pressing(char key_pressed){
        if(key_pressed == 'd'){
            
            x_velocity = SHIP_VELOCITY;
            
            
        }
        else if(key_pressed == 'a'){
            x_velocity = -SHIP_VELOCITY;
            
        }
        else if(key_pressed == 'w'){
            
            y_velocity = -SHIP_VELOCITY;
        }
        else if(key_pressed == 's'){
            
            y_velocity = SHIP_VELOCITY;
        }
        else if(key_pressed == ' '){
            if(permission_shooting){
                is_shooting = true;
                permission_shooting  = false;
            }
            else
            is_shooting = false;    
        }
}


void Ship::handle_key_released(char key_pressed){
        if(key_pressed == 'd'){
            if(x_velocity > 0)
                x_velocity = 0;
            
        }
        else if(key_pressed == 'a'){
            if(x_velocity < 0)
                x_velocity = 0;
            
        }
        else if(key_pressed == 'w'){
            
            if(y_velocity < 0)
                y_velocity = 0;
        }
        else if(key_pressed == 's'){
            
            if(y_velocity > 0)
                y_velocity = 0;
        }
        else if(key_pressed == ' '){
            permission_shooting = true;
        }
        
}

void Ship::draw_self(Window *window){
    if(is_alive)
        window->draw_img( shap_of_ship , Rectangle(Point(x ,y) ,width , height));
}

void Ship::shoot(std::vector<Shot>& shots_list){
    for(int i=0 ; i < shots_list.size() ; i++){
        if(shots_list[i].get_type() == ""){
            shots_list[i] = Shot("my_shot" , SHOT_SHAPE , x + width/2 , y, shot_power);
            return;
        }
    }
    shots_list.push_back(Shot("my_shot" , SHOT_SHAPE , x + width/2 , y , shot_power));
    
}


void Ship::set_random_index(Window *window){
    srand(time(NULL));
    x = rand() % window->get_width();
    y = window->get_height() - CELL_SIZE ;
}


bool Ship::is_end_of_power(){
    if(shield_mode || speed_mode){
        if(time(NULL) - start_power_mode > REMAIN_TIME){
            if(speed_mode){
                speed_mode = false;
                shot_power = SHOT_VELOCITY;
            }
            if(shield_mode){
                shield_mode = false;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

void Ship::update(Window *window , std::vector<Shot>& shots_list){
        x = x + x_velocity;
        y = y + y_velocity;
        if(x + width > window->get_width())
            x = window->get_width() - width;
        if(y + height > window->get_height())
            y = window->get_height() - height; 
        if(y < 0)
            y = 0;
        if(x < 0)
            x = 0; 
        if(is_shooting){
            shoot(shots_list);
            is_shooting = false;
        }
        if(is_end_of_power()){
            change_shape();
        }          
}


void Ship::change_shape(){
    if(name == "hostage")
        shap_of_ship = HOSTAGE_SHAPE;
    else
        shap_of_ship = SHIP_SHAPE;    
}

Hostage::Hostage() : Ship(){
    
    name = "hostage";
    is_alive = false;
    
    x = -1000;
    y = -1000;
}

Hostage::Hostage(std::string _name , std::string shap  , int _x ,  int _y , bool life)
    :Ship(_name , shap , _x , _y) {
        name = "hostage";
        is_alive = life;
        
}

void Hostage::release(Window *window){
    x = -900;
    y = -900;
    is_alive = false;
    draw_self(window);
    window->update_screen();
}


