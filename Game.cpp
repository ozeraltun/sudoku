#include "Game.h"
#include <iostream>



Game::Game() {
	nextState = States{ unknown_State };
	state = States{ unknown_State };
	finisher = false;
}

void Game::Start() {
	state = States{ main_Menu };
	nextState = States{ unknown_State };
	finisher = false;
}

bool Game::isFinished() {
	//pass
	return false;
}

void Game::Iterate() {
	switch (state) {
	case States{ main_Menu }:
		MainMenu();
		break;
	case States{ load_Game }:
		LoadAGame();
		break;
	case States{ load_Example_Game }:
		LoadExampleGame();
		break;
	case States{ enter_As_Full }:
		EnterSudokuFully();
		break;
	case States{ enter_As_Line }:
		EnterSudokuLine();
		break;
	case States{ sudoku_Loaded }:
		SolverMain();
		break;
	case States{ solveByHand }:
		SolveByHand();
		break;
	case States{ solveByMachine }:
		SolveByMachine();
		break;
	default:
		//pass
		std::cout << "No such State" << std::endl;
		break;
	}
	state = nextState;
}

void Game::LoadExampleGame() {
	/* Loads this one:
	5 3 0  0 7 0  0 0 0
	6 0 0  1 9 5  0 0 0
	0 9 8  0 0 0  0 6 0

	8 0 0  0 6 0  0 0 3
	4 0 0  8 0 3  0 0 1
	7 0 0  0 2 0  0 0 6

	0 6 0  0 0 0  2 8 0
	0 0 0  4 1 9  0 0 5
	0 0 0  0 8 0  0 7 9
	*/
	int fullset[9][9];

	//5 3 0  0 7 0  0 0 0
	fullset[0][0] = 5;
	fullset[0][1] = 3;
	fullset[0][2] = 0;

	fullset[0][3] = 0;
	fullset[0][4] = 7;
	fullset[0][5] = 0;

	fullset[0][6] = 0;
	fullset[0][7] = 0;
	fullset[0][8] = 0;

	//sec row
	//6 0 0  1 9 5  0 0 0
	fullset[1][0] = 6;
	fullset[1][1] = 0;
	fullset[1][2] = 0;

	fullset[1][3] = 1;
	fullset[1][4] = 9;
	fullset[1][5] = 5;

	fullset[1][6] = 0;
	fullset[1][7] = 0;
	fullset[1][8] = 0;

	//third row
	//0 9 8  0 0 0  0 6 0
	fullset[2][0] = 0;
	fullset[2][1] = 9;
	fullset[2][2] = 8;

	fullset[2][3] = 0;
	fullset[2][4] = 0;
	fullset[2][5] = 0;

	fullset[2][6] = 0;
	fullset[2][7] = 6;
	fullset[2][8] = 0;

	//4th row
	//8 0 0  0 6 0  0 0 3
	fullset[3][0] = 8;
	fullset[3][1] = 0;
	fullset[3][2] = 0;

	fullset[3][3] = 0;
	fullset[3][4] = 6;
	fullset[3][5] = 0;

	fullset[3][6] = 0;
	fullset[3][7] = 0;
	fullset[3][8] = 3;

	//5th row
	//4 0 0  8 0 3  0 0 1
	fullset[4][0] = 4;
	fullset[4][1] = 0;
	fullset[4][2] = 0;

	fullset[4][3] = 8;
	fullset[4][4] = 0;
	fullset[4][5] = 3;

	fullset[4][6] = 0;
	fullset[4][7] = 0;
	fullset[4][8] = 1;

	//6th row
	//7 0 0  0 2 0  0 0 6
	fullset[5][0] = 7;
	fullset[5][1] = 0;
	fullset[5][2] = 0;

	fullset[5][3] = 0;
	fullset[5][4] = 2;
	fullset[5][5] = 0;

	fullset[5][6] = 0;
	fullset[5][7] = 0;
	fullset[5][8] = 6;

	//7th row
	//0 6 0  0 0 0  2 8 0
	fullset[6][0] = 0;
	fullset[6][1] = 6;
	fullset[6][2] = 0;

	fullset[6][3] = 0;
	fullset[6][4] = 0;
	fullset[6][5] = 0;

	fullset[6][6] = 2;
	fullset[6][7] = 8;
	fullset[6][8] = 0;

	//8th row
	//0 0 0  4 1 9  0 0 5
	fullset[7][0] = 0;
	fullset[7][1] = 0;
	fullset[7][2] = 0;

	fullset[7][3] = 4;
	fullset[7][4] = 1;
	fullset[7][5] = 9;

	fullset[7][6] = 0;
	fullset[7][7] = 0;
	fullset[7][8] = 5;


	//8th row
	//0 0 0  0 8 0  0 7 9
	fullset[8][0] = 0;
	fullset[8][1] = 0;
	fullset[8][2] = 0;

	fullset[8][3] = 0;
	fullset[8][4] = 8;
	fullset[8][5] = 0;

	fullset[8][6] = 0;
	fullset[8][7] = 7;
	fullset[8][8] = 9;
	S.loadSudoku(fullset);
	nextState = States{ sudoku_Loaded };
}

void Game::SolveByHand() {
	int row;
	int col;
	int val;
	system("CLS");
	S.printSudoku();
	//std::cout << "Press -1 for go back" << std::endl;

	std::cout << "Pick an index by row number" << std::endl;
	std::cin >> row;
	std::cout << "Pick an index by column number" << std::endl;
	std::cin >> col;
	std::cout << "Pick the value at the index " << row << ", " << col << std::endl;
	std::cin >> val;

	S.setIndexByHand(row, col, val);
}

bool Game::findNextIterable(int* iterable_row, int* iterable_col, Iterable_States(&Iterable_List)[9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (Iterable_List[row][col] == Iterable_States{ haveNot_Iteraded }) {
				//we have found have_not_iterated square
				if (S.getWrittenState_ByIndex(row, col) == writtenStates{ not_Writen }) {
					//we have found an empty val
					*iterable_row = row;
					*iterable_col = col;
					Iterable_List[row][col] = Iterable_States{ have_Iterated };
					return true;
				}
			}
		}
	}
	return false;
}

void Game::getRowValuesAsList(bool(&rowEliminationList)[9], const int rowNumber) {
	for (int indexer_Col = 0; indexer_Col < 9; indexer_Col++) {
		if (S.getIndex(rowNumber, indexer_Col) != 0) {
			//if it finds a value in the column, marks the location as false
			rowEliminationList[S.getIndex(rowNumber, indexer_Col) - 1] = true;
		}
	}
}

void Game::getColValuesAsList(bool(&colEliminationList)[9], const int colNumber) {
	for (int indexer_Row = 0; indexer_Row < 9; indexer_Row++) {
		if (S.getIndex(indexer_Row, colNumber) != 0) {
			//if it finds a value in the column, marks the location as false
			colEliminationList[S.getIndex(indexer_Row, colNumber) - 1] = true;
		}
	}

}

void Game::callSquareArranger(int row_begin, int col_begin, bool(&smallSquareEliminationList)[9]) {
	for (int index_row = row_begin; index_row < row_begin + 3; index_row++) {
		for (int index_col = col_begin; index_col < col_begin + 3; index_col++) {
			if (S.getIndex(index_row, index_col) != 0) {
				smallSquareEliminationList[S.getIndex(index_row, index_col) - 1] = true;
			}
		}
	}
}

int Game::getSmallSquareNumber(const int iterable_row, const int iterable_col) {
	int smallSquareNumber = 0;
	if (iterable_row == 0 || iterable_row == 1 || iterable_row == 2) {
		if (iterable_col == 0 || iterable_col == 1 || iterable_col == 2) {
			smallSquareNumber = 1;
		}
		else if (iterable_col == 3 || iterable_col == 4 || iterable_col == 5) {
			smallSquareNumber = 2;
		}
		else if (iterable_col == 6 || iterable_col == 7 || iterable_col == 8) {
			smallSquareNumber = 3;
		}
	}
	else if (iterable_row == 3 || iterable_row == 4 || iterable_row == 5) {
		if (iterable_col == 0 || iterable_col == 1 || iterable_col == 2) {
			smallSquareNumber = 4;
		}
		else if (iterable_col == 3 || iterable_col == 4 || iterable_col == 5) {
			smallSquareNumber = 5;
		}
		else if (iterable_col == 6 || iterable_col == 7 || iterable_col == 8) {
			smallSquareNumber = 6;
		}
	}
	else if (iterable_row == 6 || iterable_row == 7 || iterable_row == 8) {
		if (iterable_col == 0 || iterable_col == 1 || iterable_col == 2) {
			smallSquareNumber = 7;
		}
		else if (iterable_col == 3 || iterable_col == 4 || iterable_col == 5) {
			smallSquareNumber = 8;
		}
		else if (iterable_col == 6 || iterable_col == 7 || iterable_col == 8) {
			smallSquareNumber = 9;
		}
	}
	else {
		//pass
	}
	return smallSquareNumber;
}

void Game::getSmallSquareAsList(bool(&smallSquareEliminationList)[9], const int iterable_row, const int iterable_col) {
	int smallSquareNumber = getSmallSquareNumber(iterable_row, iterable_col);
	//we have found which small square Number we are in

	switch (smallSquareNumber) {
	case 1:
		callSquareArranger(0, 0, smallSquareEliminationList);
		break;
	case 2:
		callSquareArranger(0, 3, smallSquareEliminationList);
		break;
	case 3:
		callSquareArranger(0, 6, smallSquareEliminationList);
		break;
	case 4:
		callSquareArranger(3, 0, smallSquareEliminationList);
		break;
	case 5:
		callSquareArranger(3, 3, smallSquareEliminationList);
		break;
	case 6:
		callSquareArranger(3, 6, smallSquareEliminationList);
		break;
	case 7:
		callSquareArranger(6, 0, smallSquareEliminationList);
		break;
	case 8:
		callSquareArranger(6, 3, smallSquareEliminationList);
		break;
	case 9:
		callSquareArranger(6, 6, smallSquareEliminationList);
		break;
	default:
		//pass
		break;
	}
}

void Game::CreateAvailableNumberList(bool(&availableNumbers)[9], const int iterable_row, const int iterable_col) {
	//1- eliminate row values
	//2- eliminate col values
	//3- eliminate square values
		
	//note that availableNumbers list is all false
	//so I can OR it with elimination values
	
	bool rowEliminationList[9]         = { false, false, false, false, false, false, false, false, false };
	bool colEliminationList[9]         = { false, false, false, false, false, false, false, false, false };
	bool smallSquareEliminationList[9] = { false, false, false, false, false, false, false, false, false };

	getRowValuesAsList(rowEliminationList, iterable_row);
	getColValuesAsList(colEliminationList, iterable_col);
	getSmallSquareAsList(smallSquareEliminationList, iterable_row, iterable_col);

	for (int index = 0; index < 9; index++) {
		availableNumbers[index] = availableNumbers[index] || rowEliminationList[index] || colEliminationList[index] || smallSquareEliminationList[index];
		availableNumbers[index] = !availableNumbers[index];
	}

}

void Game::useFullAvailableList(bool(&fullList)[9][9][9]) {
	//if there is only one "true" then we have found a value:

	int temp = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int true_counter = 0;
			for (int k = 0; k < 9; k++) {
				if (fullList[i][j][k] == true) {
					true_counter++;
					temp = k;
				}
			}
			if (true_counter == 1) {
				int val = temp + 1;
				std::cout << "We have found a value at index " << i << ", " << j << " value = " << val << std::endl;
				S.setIndexByHand(i, j, val);
			}
		}
	}
}

void Game::IterateOnceBetter() {
	//initializing iterable_List
	Iterable_States iterable_List[9][9];
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			iterable_List[row][col] = Iterable_States{ haveNot_Iteraded };
		}
	}

	//initializing availablefullList:
	bool fullList[9][9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				fullList[i][j][k] = false;
			}
		}
	}

	//Loop until every iteration has made
	while (true) {
		int iterable_row = 0;
		int iterable_col = 0;
		if (!findNextIterable(&iterable_row, &iterable_col, iterable_List)) {
			//Then we have not found any iterable value
			//std::cout << "We could not found any iterable location!" << std::endl;
			break;
		}
		std::cout << "We have found an iterable location at index  " << iterable_row << ", " << iterable_col << std::endl;

		//now we need to find the available numbers for that iterable location
		//so we initialized a list for that iterable location
		bool availableNumbers[9] = { false, false, false, false, false, false, false, false, false };
		CreateAvailableNumberList(availableNumbers, iterable_row, iterable_col);

		for (int index = 0; index < 9; index++) {
			fullList[iterable_row][iterable_col][index] = availableNumbers[index];
		}
	}
	//available fulllist is finished

	useFullAvailableList(fullList);

	/*Now we have done
	* checking row wise
	* checking column wise
	* and checking small 3x3 square wise
	*
	* So, for every iterable-square we must have an array that consists of available values 
	*
	* Then:
	* while looking row wise if we find an available value x only one time. then it must be written there
	* while looking column wise if we find an available value x only one time. then it must be written there
	* while looking 3x3 wise if we find an available value x only one time. then it must be written there
	*
	* I have no idea about second step.
	*/

}

void Game::SolveByMachine() {
	//pass
	//system("CLS");
	S.printSudoku();
	int input_Num;
	std::cout << "1- Iterate one by one " << std::endl;
	std::cin >> input_Num;

	switch (input_Num) {
	case 1:
		//Change to IterateAll, which consists of IterateOnces
		IterateOnceBetter();
		break;

	default:
		break;
	}

}

void Game::SolverMain() {
	system("CLS");
	int givenInput;
	std::cout << "You have entered to the solver.." << std::endl;
	std::cout << "Here is the sudoku you want to solve:" << std::endl;
	S.printSudoku();
	std::cout << "Please choose one:" << std::endl;
	std::cout << "1- Enter values by hand" << std::endl;
	std::cout << "2- Solve by using machine" << std::endl;

	std::cin >> givenInput;
	if (givenInput != 1 && givenInput != 2) {
		std::cout << "Error! you can only choose 1 or 2" << std::endl;
		return;
	}
	else if (givenInput == 1) {
		nextState = States{ solveByHand };
		return;
	}
	else if (givenInput == 2) {
		nextState = States{ solveByMachine };
		return;
	}
	else {
		std::cout << "No else statement!" << std::endl;
	}

}

void Game::EnterSudokuLine() {
	bool errorVal = false;
	int fullset[9][9];

	char given_Input[10];
	std::cout << "Enter sudoku line " << std::endl;
	for (int row = 0; row < 9; row++) {
		int fullrow[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		std::cout << "Enter row=" << row << std::endl;
		std::cin >> given_Input;

		//split giveninput without spaces:
		for (int index = 0; index < 9; index++) {

			fullrow[index] = (given_Input[index]) - '0';
			if (!(fullrow[index] >= 1 && fullrow[index] <= 9)) {
				std::cout << "ERROR! pls enter 1-9 " << std::endl;
				errorVal = true;
				nextState = States{ unknown_State };
				return;
			}
			fullset[row][index] = fullrow[index];
		}
	}
	std::cout << "sudoku entered fully " << std::endl;
	S.loadSudoku(fullset);
	nextState = States{ sudoku_Loaded };
}

void Game::EnterSudokuFully() {
	//States enterSudokuFullState;
	bool errorVal = false;
	int fullset[9][9];
	int given_Input;
	std::cout << "Enter sudoku fully " << std::endl;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			std::cout << "Enter row=" << row << ", col=" << col << std::endl;
			std::cin >> given_Input;
			if (given_Input >= 1 && given_Input <= 9) {
				fullset[row][col] = given_Input;
			}
			else {
				std::cout << "ERROR! pls enter 1-9 " << std::endl;
				errorVal = true;
			}
		}
	}
	if (errorVal) {
		nextState = States{ unknown_State };
	}
	else {
		std::cout << "sudoku entered fully " << std::endl;
		S.loadSudoku(fullset);
		nextState = States{ sudoku_Loaded };
	}

}

void Game::LoadAGame() {
	States stateAtLoad;
	int selection;
	std::cout << "We will load the Game.. " << std::endl;
	std::cout << "How would you like to load the game: " << std::endl;
	std::cout << "1-Enter as full" << std::endl;
	std::cout << "2-Enter line by line" << std::endl;
	std::cout << "3-Enter index by index" << std::endl;
	std::cin >> selection;
	switch (selection) {
	case 1:
		stateAtLoad = States{ enter_As_Full };
		break;
	case 2:
		stateAtLoad = States{ enter_As_Line };
		break;
	case 3:
		stateAtLoad = States{ enter_As_Index };
		break;
	default:
		stateAtLoad = States{ unknown_State };
	}
	nextState = stateAtLoad;

}

void Game::MainMenu() {
	std::cout << "Main Menu: " << std::endl;
	int selection;
	States stateAtMain;

	std::cout << "1-Load a Game" << std::endl;
	std::cout << "2-Load an Example Game" << std::endl;
	std::cout << "Enter your selection:" << std::endl;
	std::cin >> selection;
	std::cout << "You have selected: " << selection << std::endl;


	switch (selection) {
	case 1:
		stateAtMain = States{ load_Game };
		break;
	case 2:
		stateAtMain = States{ load_Example_Game };
		break;
	default:
		std::cout << "Error! you can only choose 1-2" << std::endl;
		stateAtMain = States{ unknown_State };
	}
	nextState = stateAtMain;
}


/// @brief this function will be used in order to find all of the numbers in the sudoku
void Game::IterateAll() {
	//I need an array which consists of iterable values!!!
	//Then, I should iterate on all of those values.


	//first everything is not iterated:
	//Iterable_States Iterable_List[9][9] = { haveNot_Iteraded };
}

