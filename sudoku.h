#ifndef _Sudoku_H
#define _Sudoku_H

#include "states.cpp"

class sudoku {
private:
	//This array has the values that is on the sudoku indexes 
	int s_Map[9][9];
	//This array has the explanation for the written values. Which might vary as standard, hand-written or not-written(empty)
	writtenStates sudoku_Val_States[9][9];

	/// @brief initializes sudoku map with all zeros
	void init_S_Map();
	
public:
	/// @brief Constructor for sudoku object
	sudoku();

	/// @brief Loads sudoku object from given int[9][9] array
	/// @param myList is the given array which consists of all sudoku index values. It is int[9][9]
	void loadSudoku(int myList[9][9]);

	/// @brief This function is the basic getter for the sudoku map. It returns the value possessed in the sudoku map which is located by parameters 
	/// @param row Row parameter of the sudoku map
	/// @param col Column parameter of the sudoku map
	/// @return The value at the specified location
	int getIndex(const int row, const int col);

	/// @brief sets the value at the specified location
	/// @param row row parameter
	/// @param column column parameter
	/// @param val value that will be changed into
	/// @return error value
	int setIndex(const int row, const int col, const int val);

	/// @brief Sets the value at the index, also arranges its state as hand-written.
	/// @param row row value
	/// @param col column value
	/// @param val value that will be written
	/// @return error value
	int setIndexByHand(const int row, const int col, const int val);

	/// @brief Returns the written state of that specific location in the sudoku table
	/// @param row row value
	/// @param column column value
	/// @return The written state value at the location which has spesified by the input parameters.
	writtenStates getWrittenState_ByIndex(const int state_Row, const int state_Col);

	/// @brief Sets the written-state at the specific location in the state table.
	/// @param state_Col row value
	/// @param state_Row value
	/// @param state is the state that will be written
	void setWrittenState_ByIndex(const int state_Row, const int state_Col, const writtenStates state);
	/// It might be better to encapsulate this method.

	
	/// @brief This function is used while printing, it just adds some special format accourding to the state at that index. if it is hand-written or machine-found(again treated as hand-written) value then it adds paranthesis.
	/// @param row row number
	/// @param col column number
	void printValueByWrittenState(const int row, const int col);

	/// @brief Prints the sudoku table
	void printSudoku();

	
};
#endif // !_Sudoku_H

