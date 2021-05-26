#include <iostream>
#include <stdlib.h> //for clearing the screen
/*
* TODO LIST
* 1- Let the machine solve sudoku
* 2- There is not any go back mechanism
*/

/// @brief sudoku values must be either of the following:
enum writtenStates {std_Writen, hand_Writen, not_Writen };

/// @brief while iterating followings will be used:
enum Iterable_States { have_Iterated, haveNot_Iteraded };

/// @brief Game states are the following:
enum States {
	unknown_State, main_Menu, load_Game, enter_As_Full, enter_As_Line,
	enter_As_Index, sudoku_Loaded, solveByHand, solveByMachine, load_Example_Game
};


class sudoku {
private:
	int s_Map[9][9];
	writtenStates sudoku_Val_States[9][9];
public:
	sudoku() {
		init_S_Map();
	}

	/// @brief initializes sudoku map with all zeros
	void init_S_Map() {
		for (int row = 0; row <= 8; row++) {
			for (int col = 0; col <= 8; col++) {
				s_Map[row][col] = 0;
				sudoku_Val_States[row][col] = writtenStates{not_Writen};
			}
		}
	}
	
	/// @brief loads sudoku from given array
	/// @param myList is the full sudoku values
	void loadSudoku(int myList[9][9]) {
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				setIndex(row, col, myList[row][col]);

				if (myList[row][col] != 0) {
					sudoku_Val_States[row][col] = writtenStates{ std_Writen };
				}
			}
		}
	}

	/// @brief returns the value located by parameters
	/// @param x row parameter
	/// @param y column parameter
	/// @return value at the specified location
	int getIndex(int x, int y) {
		return s_Map[x][y];
	}
	
	/// @brief Returns the written state of that specific location in the sudoku table
	/// @param x row value
	/// @param y column value
	/// @return written state value
	writtenStates getWrittenState_ByIndex(const int x, const int y) {
		return sudoku_Val_States[x][y];
	}

	/// @brief Sets the written state at the specific location in the state table
	/// @param x row value
	/// @param y column value
	/// @param state  is the state that will be written
	void setWrittenState_ByIndex(const int x, const int y, const writtenStates state) {
		sudoku_Val_States[x][y] = state;
	}

	int setIndexByHand(int x, int y, int val) {
		if ((val >= 1) && (val <= 9) && (sudoku_Val_States[x][y] != writtenStates{ std_Writen})) {
			s_Map[x][y] = val;
			sudoku_Val_States[x][y] = writtenStates{ hand_Writen };
			return 0;
		}
		else if ((val == 0) && (sudoku_Val_States[x][y] != writtenStates{ std_Writen })) {
			s_Map[x][y] = val;
			sudoku_Val_States[x][y] = writtenStates{ not_Writen };
			return 0;
		}
		else if (sudoku_Val_States[x][y] == writtenStates{ std_Writen }) {
			std::cout << "It is not writable" << std::endl;
			return 1;
		}
		return 1; //Error
	}


	

	/// @brief sets the value at the specified location
	/// @param x row parameter
	/// @param y column parameter
	/// @param val value that will be changed into
	/// @return error value
	int setIndex(int x, int y, int val) {
		if ((val >= 0) || (val <= 9)) {
			s_Map[x][y] = val;
			return 0;
		}
		return 1; //Error
	}
	
	/// @brief checking which rows are finished
	/// @param rowNumber is the row number
	/// @return bool array that includes finishing condition of that row
	bool checkRowWiseSingle(int rowNumber) {
		for (int col = 0; col <= 8; col++) {
			if (s_Map[rowNumber][col] == 0)
				return false;
		}
		return true;
	}
	bool checkRowWiseAll() {
		bool condition[9] = { false };

		for (int row = 0; row <= 8; row++) {
			if (checkRowWiseSingle(row)) {
				condition[row] = true;
			}
		}
	}
	
	void printValueByWrittenState(int row, int col) {
		if (sudoku_Val_States[row][col] == writtenStates{ std_Writen }) {
			std::cout << " " << s_Map[row][col] << " ";
		}
		else if (sudoku_Val_States[row][col] == writtenStates{ hand_Writen }) {
			std::cout << "(" << s_Map[row][col] << ")";
		}
		else {
			std::cout << " " << "0" << " ";
		}
	}
	
	/// /// @brief prints the sudoku table
	void printSudoku() {
		std::cout << std::endl;
		int indexer_3 = 1;
		int indexer_9 = 1;
		int indexer_27 = 1;
		for (int row = 0; row <= 8; row++) {
			for (int col = 0; col <= 8; col++) {
				//std::cout << s_Map[row][col];
				printValueByWrittenState(row, col);
				if (indexer_27 == 27) {
					std::cout << std::endl;
					std::cout << "===================================" << std::endl;
					indexer_27 = 1;
					indexer_9 = 1;
					indexer_3 = 1;
				}
				else if (indexer_9 == 9) {
					std::cout << std::endl;
					indexer_9 = 1;
					indexer_3 = 1;
					indexer_27++;
				}
				else if (indexer_3 == 3) {
					std::cout << " || ";
					indexer_3 = 1;
					indexer_9++;
					indexer_27++;
				}
				else {
					indexer_3++;
					indexer_9++;
					indexer_27++;
				}

			}
		}

		std::cout << "_________________________" << std::endl;
	}

	/// @brief prints specified location
	/// @param row is the row number
	/// @param col is the column number
	void printValue(int row, int col) {
		std::cout << "value at (" << row << ", " << col << ") = " << getIndex(row, col) << std::endl;
	}
}; //end of the class sudoku



class Game {
private:

public:
	sudoku S;
	States state;
	States nextState;
	bool finisher;
	
	Game() {
		nextState = States{ unknown_State };
		state = States{ unknown_State };
		finisher = false;
	}
	void Start() {
		state = States{ main_Menu };
		nextState = States{ unknown_State };
		finisher = false;
	}
	bool isFinished() {
		//pass
		return false;
	}
	void Iterate() {
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
		case States{ enter_As_Index }:
			EnterSudokuIndex();
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
	void LoadExampleGame() {
		/* Load this one:
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
		fullset[0][2] = 1;

		fullset[0][3] = 2;
		fullset[0][4] = 7;
		fullset[0][5] = 8;

		fullset[0][6] = 9;
		fullset[0][7] = 0;
		fullset[0][8] = 4;

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
		fullset[2][0] = 9;
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
		fullset[7][0] = 1;
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
		fullset[8][0] = 2;
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


	void SolveByHand() {
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

	/// @brief finds the first empty value in the sudoku
	/// @param empty_Row row index of the first empty value
	/// @param empty_Col column index of the first empty value
	void FindFirstEmpty(int* empty_Row, int* empty_Col) {
		for (int indexer_Row = 0; indexer_Row < 9; indexer_Row++) {
			for (int indexer_Col = 0; indexer_Col < 9; indexer_Col++) {
				if (S.getIndex(indexer_Row, indexer_Col) == 0) {
					*empty_Row = indexer_Row;
					*empty_Col = indexer_Col;
					return;
				}
			}
		}
	}

	int CheckByCol(const int s_Row, const int s_Col, int* foundLocRow, int* foundLocCol) {
		//initial Number list are all true
		bool colNumberList[9] = { true, true, true, true, true, true, true, true, true };
		*foundLocCol = s_Col;
		for (int indexer_Row = 0; indexer_Row < 9; indexer_Row++) {
			if (S.getIndex(indexer_Row, s_Col) != 0) {
				//if it finds a value in the column, marks the location as false
				colNumberList[S.getIndex(indexer_Row, s_Col) - 1] = false;
			}
			else {
				*foundLocRow = indexer_Row;
			}
		}

		int available_ValueCount = 0;
		int lastval = 0;
		for (int indexer_List = 0; indexer_List < 9; indexer_List++) {

			if (colNumberList[indexer_List]) {
				available_ValueCount++;
				lastval = indexer_List;
			}
		}
		if (available_ValueCount == 1) {
			return lastval + 1;
		}

		return 0;

	}


	int CheckByRow(const int s_Row, const int s_Col, int* foundLocRow, int* foundLocCol) {

		//initial Number list are all true
		bool rowNumberList[9] = { true, true, true, true, true, true, true, true, true };
		*foundLocRow = s_Row;
		for (int indexer_Col = 0; indexer_Col < 9; indexer_Col++) {
			if (S.getIndex(s_Row, indexer_Col) != 0) {
				//if it finds a value in the column, marks the location as false
				rowNumberList[S.getIndex(s_Row, indexer_Col)-1] = false;
			}
			else {
			*foundLocCol = indexer_Col;
			}
		}
		
		int available_ValueCount = 0;
		int lastval = 0;
		for (int indexer_List = 0; indexer_List < 9; indexer_List++) {
			
			if (rowNumberList[indexer_List]) {
				available_ValueCount++;
				lastval = indexer_List;
			}
		}
		if (available_ValueCount == 1) {
			return lastval+1;
		}
		
		return 0;

	}
	int FindVal(const int empty_Row, const int empty_Col, int* foundLocRow, int* foundLocCol) {
		int FoundValue = 0;

		FoundValue = CheckByRow(empty_Row, empty_Col, foundLocRow, foundLocCol);
		if (FoundValue) {
			return FoundValue;
		}

		FoundValue = CheckByCol(empty_Row, empty_Col, foundLocRow, foundLocCol);
		if (FoundValue) {
			return FoundValue;
		}

		/*
		FoundValue = CheckByCol(empty_Row, empty_Col);
		if (FoundValue) {
			return FoundValue;
		}
		*/
		return 0;
	}
	void findNextIterable(const int* iterate_Row, const int* iterate_Col, Iterable_States (&Iterable_List)[9][9]) {
		if (S.getWrittenState_ByIndex(*iterate_Row, *iterate_Col) == writtenStates{ not_Writen }) {
			
		}
	}

	/// @brief this function will be used in order to find all of the numbers in the sudoku
	void IterateAll() {
		//I need an array which consists of iterable values!!!
		//Then, I should iterate on all of those values.

		//first everything is not iterated:
		//Iterable_States Iterable_List[9][9] = { haveNot_Iteraded };
	}

	/// @brief This function will find only one number in the sudoku then return
	void IterateOnce() {
		int foundVal = 0;
		int iterate_Row;
		int iterate_Col;

		int foundLocRow;
		int foundLocCol;
		for (int index_Row = 0; index_Row < 9; index_Row++) {
			for (int index_Col = 0; index_Col < 9; index_Col++) {
				
				std::cout << "Trying index " << index_Row << ", " << index_Col << std::endl;
				
				
				foundVal = FindVal(index_Row, index_Col, &foundLocRow, &foundLocCol);

				if (foundVal != 0) {
					//Then we have found a value;
					std::cout << "Iteration found value at index " << foundLocRow << ", " << foundLocCol << std::endl;
					std::cout << "Found value is " << foundVal << std::endl;
					
					//Write the value to the sudoku
					S.setIndexByHand(foundLocRow, foundLocCol, foundVal);
					
					return;
				}
				else {
					std::cout << "Iteration found no value " << std::endl;
				}

			}
		}


		
	
	}
	void SolveByMachine() {
		//pass
		//system("CLS");
		S.printSudoku();
		int input_Num;
		std::cout << "1- Iterate one by one " << std::endl;
		std::cin >> input_Num;

		switch (input_Num) {
		case 1:
			//Change to IterateAll, which consists of IterateOnces
			IterateOnce();
			break;

		default:
			break;
		}

	}
	void SolverMain() {
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
	void EnterSudokuLine() {
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
	void EnterSudokuIndex() {
		//pass;
	}
	void EnterSudokuFully() {
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
	void LoadAGame() {
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
	void MainMenu() {
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

};
int main() {
	Game game;
	game.Start();
	while (!game.isFinished()) {
		game.Iterate();
	}
	return 0;
}
