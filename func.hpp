#ifndef _FUNC_HEADER_FILE
#define _FUNC_HEADER_FILE 

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<cmath>
#include"./src/rsdl.hpp"


const int CELL_SIZE = 50;


double distanc(Point place1 ,  Point place2);
void get_input(std::ifstream &map , int &row , int &col);









#endif
