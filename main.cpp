#include <iostream>
#include <stdlib.h> //for clearing the screen

#include "sudoku.h"
#include "states.cpp"

/*
* TODO LIST
* 1- Let the machine solve sudoku OK
* 2- There is not any go back mechanism
* 3- I need more complex algorithms
*/

class Game {
private:

public:
	sudoku S;
	States state;
	States nextState;
	bool finisher;
	
	/// @brief constructor
	Game() {
		nextState = States{ unknown_State };
		state = States{ unknown_State };
		finisher = false;
	}

	/// @brief initialization
	void Start() {
		state = States{ main_Menu };
		nextState = States{ unknown_State };
		finisher = false;
	}

	/// @brief finishing condition getter
	/// @return bool whether finished or not
	bool isFinished() {
		//pass
		return false;
	}

	/// @brief game object iterator. Sets the menus accordingly
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

	/// @brief loads an example game
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

	/// @brief when user decides to solve it, we are in this state
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

	/// @brief Checks the small squares
	/// @param s_Row row number that is given
	/// @param s_Col column number that is given 
	/// @param foundLocRow the row number of the square that appropriate value has been found for
	/// @param foundLocCol the column number of the square that appropriate value has been found for
	/// @return DNE?
	int CheckBySquares(const int s_Row, const int s_Col, int* foundLocRow, int* foundLocCol) {
		bool NumberList[9] = { true, true, true, true, true, true, true, true, true };
		//which squares are we in?
		int squareGroup = 0;
		int squareGroup1X[3] = { 0,1,2 };
		int squareGroup2X[3] = { 0,1,2 };
		int squareGroup3X[3] = { 0,1,2 };
		int squareGroup1Y[3] = { 0,1,2 };
		int squareGroup4Y[4] = { 0,1,2 };
		int squareGroup7Y[3] = { 0,1,2 };
		
		int squareGroup4X[3] = { 3,4,5 };
		int squareGroup5X[3] = { 3,4,5 };
		int squareGroup6X[3] = { 3,4,5 };
		int squareGroup2Y[3] = { 3,4,5 };
		int squareGroup5Y[3] = { 3,4,5 };
		int squareGroup8Y[3] = { 3,4,5 };

		int squareGroup7X[3] = { 6,7,8 };
		int squareGroup8X[3] = { 6,7,8 };
		int squareGroup9X[3] = { 6,7,8 };
		int squareGroup3Y[3] = { 6,7,8 };
		int squareGroup6Y[3] = { 6,7,8 };
		int squareGroup9Y[3] = { 6,7,8 };

		if ((s_Row == 0 || s_Row == 1 || s_Row == 2) && (s_Col == 0 || s_Col == 1 || s_Col == 2)) {
			squareGroup = 1;
		}
		else if ((s_Row == 0 || s_Row == 1 || s_Row == 2) && (s_Col == 3 || s_Col == 4 || s_Col == 5)) {
			squareGroup = 2;
		}
		else if ((s_Row == 0 || s_Row == 1 || s_Row == 2) && (s_Col == 6 || s_Col == 7 || s_Col == 8)) {
			squareGroup = 3;
		}
		else if ((s_Row == 3 || s_Row == 4 || s_Row == 5) && (s_Col == 0 || s_Col == 1 || s_Col == 2)) {
			squareGroup = 4;
		}
		else if ((s_Row == 3 || s_Row == 4 || s_Row == 5) && (s_Col == 3 || s_Col == 4 || s_Col == 5)) {
			squareGroup = 5;
		}
		else if ((s_Row == 3 || s_Row == 4 || s_Row == 5) && (s_Col == 6 || s_Col == 7 || s_Col == 8)) {
			squareGroup = 6;
		}
		else if ((s_Row == 6 || s_Row == 7 || s_Row == 8) && (s_Col == 0 || s_Col == 1 || s_Col == 2)) {
			squareGroup = 7;
		}
		else if ((s_Row == 6 || s_Row == 7 || s_Row == 8) && (s_Col == 3 || s_Col == 4 || s_Col == 5)) {
			squareGroup = 8;
		}
		else if ((s_Row == 6 || s_Row == 7 || s_Row == 8) && (s_Col == 6 || s_Col == 7 || s_Col == 8)) {
			squareGroup = 9;
		}
		else {
			//pass
		}
		

		if (squareGroup == 1) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup1X[indexF], squareGroup1Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 2) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup2X[indexF], squareGroup2Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 3) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup3X[indexF], squareGroup3Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 4) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup4X[indexF], squareGroup4Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 5) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup5X[indexF], squareGroup5Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 6) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup6X[indexF], squareGroup6Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 7) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup7X[indexF], squareGroup7Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 8) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup8X[indexF], squareGroup8Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
				}
			}
		}
		else if (squareGroup == 9) {
			int Val = 0;
			for (int indexF = 0; indexF < 3; indexF++) {
				for (int indexS = 0; indexS < 3; indexS++) {
					Val = S.getIndex(squareGroup9X[indexF], squareGroup9Y[indexS]);
					if (Val != 0) {
						NumberList[Val - 1] = false;
					}
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

	/// @brief This function tries to find a value for given row and column. However what it has found
	/// might for a different row and column which is setted by foundLoc parameters.
	/// @param empty_Row the row value that is empty 
	/// @param empty_Col the column value that is empty
	/// @param foundLocRow the row location index of the found value
	/// @param foundLocCol the column location index of the found value
	/// @return found value is returned. If it is not found returns 0.
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

		
		return 0;
	}

	/// @brief 
	/// @param iterable_row 
	/// @param iterable_col 
	/// @param Iterable_List 
	/// @return true if founds an iterable, false otherwise 
	bool findNextIterable(int* iterable_row, int* iterable_col, Iterable_States (&Iterable_List)[9][9]) {
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

	/// @brief this function will be used in order to find all of the numbers in the sudoku
	void IterateAll() {
		//I need an array which consists of iterable values!!!
		//Then, I should iterate on all of those values.

		
		//first everything is not iterated:
		//Iterable_States Iterable_List[9][9] = { haveNot_Iteraded };
	}
	void getRowValuesAsList(bool (&rowEliminationList)[9], const int rowNumber) {
		for (int indexer_Col = 0; indexer_Col < 9; indexer_Col++) {
			if (S.getIndex(rowNumber, indexer_Col) != 0) {
				//if it finds a value in the column, marks the location as false
				rowEliminationList[S.getIndex(rowNumber, indexer_Col) - 1] = true;
			}
		}
	}
	void getColValuesAsList(bool(&colEliminationList)[9], const int iterable_col) {
		for (int indexer_Row = 0; indexer_Row < 9; indexer_Row++) {
			if (S.getIndex(indexer_Row, iterable_col) != 0) {
				//if it finds a value in the column, marks the location as false
				colEliminationList[S.getIndex(indexer_Row, iterable_col) - 1] = true;
			}
		}

	}
	void callSquareArranger(int row_begin, int col_begin, bool (&smallSquareEliminationList)[9]) {
		for (int index_row = row_begin; index_row < row_begin + 3; index_row++) {
			for (int index_col = col_begin; index_col < col_begin + 3; index_col++) {
				if (S.getIndex(index_row, index_col) != 0) {
					smallSquareEliminationList[S.getIndex(index_row, index_col) - 1] = true;
				}
			}
		}
	}
	int getSmallSquareNumber(const int iterable_row, const int iterable_col) {
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
	void getSmallSquareAsList(bool (&smallSquareEliminationList)[9], const int iterable_row, const int iterable_col) {
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
	void CreateAvailableNumberList(bool (&availableNumbers)[9], const int iterable_row, const int iterable_col) {
		//eliminate row values
			//note that availableNumbers list is all false
			//so I can OR it with elimination values
		//eliminate col values
		//eliminate square values
		bool rowEliminationList[9]         = { false, false, false, false, false, false, false, false, false };
		bool colEliminationList[9]         = { false, false, false, false, false, false, false, false, false };
		bool smallSquareEliminationList[9] = { false, false, false, false, false, false, false, false, false };

		getRowValuesAsList(rowEliminationList,           iterable_row);
		getColValuesAsList(colEliminationList,           iterable_col);
		getSmallSquareAsList(smallSquareEliminationList, iterable_row, iterable_col);

		for (int index = 0; index < 9; index++) {
			availableNumbers[index] = availableNumbers[index] || rowEliminationList[index] || colEliminationList[index] || smallSquareEliminationList[index];
			availableNumbers[index] = !availableNumbers[index];
		}

	}
	
	void useFullAvailableList(bool(&fullList)[9][9][9]) {
		//if there is 1 true then we have found a value:
		
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
					S.setIndexByHand(i,j,val);
				}
			}
		}

	}


	void IterateOnceBetter() {
		//first find the first iterablebox,
		//this box must be empty and after iteration it must be marked as iterated
		
		//initializing iterable_List
		Iterable_States iterable_List[9][9];
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				iterable_List[row][col] = Iterable_States{ haveNot_Iteraded };
			}
		}
		//initialization for iterabe_List ends here

		//create available list [9][9][9] here
		bool fullList[9][9][9];
		//initializing availablefullList:
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				for (int k = 0; k < 9; k++) {
					fullList[i][j][k] = false;
				}
			}
		}



		while (true) {
			int iterable_row = 0;
			int iterable_col = 0;
			if (!findNextIterable(&iterable_row, &iterable_col, iterable_List)) {
				//Then we have not found any iterable value
				std::cout << "We could not found any iterable location!" << std::endl;
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
		//available fulllist must be finished here

		useFullAvailableList(fullList);

		/*at that square(iterablebox), we should get the available values by:
		* checking row wise
		* checking column wise
		* and checking small 3x3 square wise
		* 
		* So, for every iterablebox we must have available values array
		* 
		* Then we should start to find values:
		* First Step:
		* while looking row wise if we find an available value x only one time. then it must be written there
		* while looking column wise if we find an available value x only one time. then it must be written there
		* while looking 3x3 wise if we find an available value x only one time. then it must be written there
		* 
		* I have no idea about second step.
		*/

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
			IterateOnceBetter();
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
