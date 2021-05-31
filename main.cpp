#include <iostream>

#include "sudoku.h"
#include "Game.h"

/*
* TODO LIST
* 1- There is not any go back mechanism in the menus
* 2- I need more complex algorithms for the sudoku's that have multiple solutions
*/

int main() {
	Game game;
	game.Start();
	while (!game.isFinished()) {
		game.Iterate();
	}

	std::cout << "Game has finished. Well played.." << std::endl;
	return 0;
}
