FLAGS = -std=c++11  -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer


starwars.out: main.cpp Ship.o Game.o Enemy.o Shot.o func.o
	g++ main.cpp Ship.o Power.o Game.o Enemy.o Shot.o func.o ./src/rsdl.cpp  $(FLAGS) -o starwars.out

Ship.o: ./classes/Ship.hpp ./classes/Ship.cpp Enemy.o Shot.o func.o Power.o
	g++ $(FLAGS)  -c ./classes/Ship.cpp

Game.o: ./classes/Game.hpp Ship.o ./classes/Game.cpp Enemy.o func.o Power.o
	g++ $(FLAGS) -c ./classes/Game.cpp 
	
Enemy.o: ./classes/Enemy.hpp ./classes/Enemy.cpp Shot.o  func.o
	g++ $(FLAGS) -c ./classes/Enemy.cpp

Shot.o:  ./classes/Shot.cpp ./classes/Shot.hpp func.o  
	g++ $(FLAGS) -c ./classes/Shot.cpp

func.o: func.hpp func.cpp
	g++ $(FLAGS) -c func.cpp

Power.o: ./classes/Power.hpp  ./classes/Power.cpp func.o
	g++ $(FLAGS) -c ./classes/Power.cpp  

	
