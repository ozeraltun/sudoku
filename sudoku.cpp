#include <iostream>
#include "sudoku.h"

#include "states.cpp"

sudoku::sudoku() {
	init_S_Map();
}

void sudoku::init_S_Map() {
	for (int row = 0; row <= 8; row++) {
		for (int col = 0; col <= 8; col++) {
			s_Map[row][col] = 0;
			sudoku_Val_States[row][col] = writtenStates{ not_Writen };
		}
	}
}

void sudoku::loadSudoku(int myList[9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			setIndex(row, col, myList[row][col]);

			if (myList[row][col] != 0) {
				sudoku_Val_States[row][col] = writtenStates{ std_Writen };
			}
		}
	}
}

int sudoku::getIndex(const int row, const int col) {
	return s_Map[row][col];
}

writtenStates sudoku::getWrittenState_ByIndex(const int state_Row, const int state_Col) {
	return sudoku_Val_States[state_Row][state_Col];
}

void sudoku::setWrittenState_ByIndex(const int state_Row, const int state_Col, const writtenStates state) {
	sudoku_Val_States[state_Row][state_Col] = state;
}

int sudoku::setIndexByHand(const int row, const int col, const int val) {
	if ((val >= 1) && (val <= 9) && (sudoku_Val_States[row][col] != writtenStates{ std_Writen })) {
		s_Map[row][col] = val;
		sudoku_Val_States[row][col] = writtenStates{ hand_Writen };
		return 0;
	}
	else if ((val == 0) && (sudoku_Val_States[row][col] != writtenStates{ std_Writen })) {
		s_Map[row][col] = val;
		sudoku_Val_States[row][col] = writtenStates{ not_Writen };
		return 0;
	}
	else if (sudoku_Val_States[row][col] == writtenStates{ std_Writen }) {
		//std::cout << "It is not writable" << std::endl;
		return 1; //Error
	}
	return 1; //Error
}

int sudoku::setIndex(const int row, const int col, const int val) {
	if ((val >= 0) || (val <= 9)) {
		s_Map[row][col] = val;
		return 0;
	}
	return 1; //Error
}

void sudoku::printValueByWrittenState(const int row, const int col) {
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

void sudoku::printSudoku() {
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


