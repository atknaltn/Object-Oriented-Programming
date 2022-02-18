Game:	game 
game:	play_game.cpp ai.cpp ai.h game_control_unit.cpp game_control_unit.h game_board.cpp game_board.h interface.cpp interface.h
	g++ -std=c++11 -c play_game.cpp
	g++ -std=c++11 -c game_board.cpp
	g++ -std=c++11 -c game_control_unit.cpp
	g++ -std=c++11 -c ai.cpp
	g++ -std=c++11 -c interface.cpp
	g++ -std=c++11 -o play_game play_game.o game_board.o game_control_unit.o interface.o ai.o
	./play_game