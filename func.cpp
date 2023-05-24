#include"func.hpp"




double distanc(Point place1 , Point place2){

    return sqrt(pow(place1.x - place2.x , 2)  + pow(place1.y - place2.y , 2));
}

void get_input(std::ifstream &map , int &row , int &col){
    map >> row >> col;
}
