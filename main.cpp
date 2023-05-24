#include"./src/rsdl.hpp"
#include"./classes/Ship.hpp"
#include"./classes/Enemy.hpp"
#include"./classes/Game.hpp"
#include"./classes/Shot.hpp"
#include"func.hpp"

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>

using namespace std;


string MAP = "map.txt";

int main(){




    

    
    std::ifstream  map;
    map.open((std::string) MAP);
    int row , column;
    get_input( map , row , column);
    Game game(row * CELL_SIZE , column * CELL_SIZE , SHIP_SHAPE);
    game.run(map);

      
   
    return 0;
}