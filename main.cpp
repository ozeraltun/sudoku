#include <iostream>

#include "sudoku.h"
#include "Game.h"

/*
* TODO LIST
* 1- There is not any go back mechanism
* 2- I need more complex algorithms
* 3- cleanup in the header and cpp files of game object
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
