#ifndef _Game_H
#define _Game_H

#include "states.cpp"
#include "sudoku.h"

class Game {
private:
	sudoku S;
	States state;
	States nextState;
	bool finisher;
	

	/*STATES*/

	/// @brief When user is at the main-menu, we are in this state/method
	void MainMenu();

	/// @brief When user decides to load a sudoku game by entering its indexes, we are in this state/method
	void LoadAGame();

	/// @brief When user decides to load a sudoku game by entering indexes line by line, we are in this state/method
	void EnterSudokuLine();

	/// @brief When user decides to load a sudoku game by entering indexes index by index, we are in this state/method
	void EnterSudokuFully();

	/// @brief Loads an example game
	void LoadExampleGame();

	/// @brief When user decides to solve the sudoku, we are in this state/method
	void SolverMain();
	
	/// @brief When user decides to solve the sudoku, we are in this state/method
	void SolveByHand();

	/// @brief When user decides to solve the sudoku by using pc, we are in this state/method
	void SolveByMachine();


	/* METHODS RELATED WITH FINDING A SOLUTION */

	/// @brief This method uses all of the available-number lists and finds the value that can be written to the sudoku
	/// @param fullList is the list that has available numbers. fullList[iterable_row][iterable_col][index]
	void useFullAvailableList(bool(&fullList)[9][9][9]);

	/// @brief available-number-list is set in this method
	/// @param availableNumbers is the list that will be set
	/// @param iterable_row is the row value of the iteration
	/// @param iterable_col is the column value of the iteration
	void CreateAvailableNumberList(bool(&availableNumbers)[9], const int iterable_row, const int iterable_col);

	/// @brief This method arranges the row-elimination-list according to given row number
	/// @param rowEliminationList is the list we are setting
	/// @param rowNumber is the row number of the sudoku which we are in
	void getRowValuesAsList(bool(&rowEliminationList)[9], const int rowNumber);

	/// @brief This method arranges the column-elimination-list according to given column number
	/// @param colEliminationList is the list we are setting
	/// @param colNumber is the column number of the sudoku which we are in
	void getColValuesAsList(bool(&colEliminationList)[9], const int colNumber);

	/// @brief This method arranges the 3x3-elimination-list(smallSquareEliminationList) according to row-column number
	/// @param smallSquareEliminationList is the list we are setting
	/// @param iterable_row is the row number we are in
	/// @param iterable_col is the column number we are in
	void getSmallSquareAsList(bool(&smallSquareEliminationList)[9], const int iterable_row, const int iterable_col);

	/// @brief This method finds which smallSquare we are in
	/// @param iterable_row is the iterated row value
	/// @param iterable_col is the iterated column value
	/// @return smallSquareNumber we are in
	int getSmallSquareNumber(const int iterable_row, const int iterable_col);

	/// @brief This method arranges smallSquareEliminationList according to given row-begin and col-begin numbers
	/// @param row_begin is the row number where the 3x3 square begins
	/// @param col_begin is the column number where the 3x3 square begins 
	/// @param smallSquareEliminationList is the list we are setting
	void callSquareArranger(int row_begin, int col_begin, bool(&smallSquareEliminationList)[9]);

	/* METHODS RELATED WITH ITERATIONS */

	/// @brief Iterates the solution of the sudoku
	void IterateOnceBetter();

	/// @brief Finds the next iteration values as row value and column value. While checking this numbers, this method uses a list that consists of iterated or not-iteratated values 
	/// @param iterable_row is an iteration-row value
	/// @param iterable_col is an iteration-column value
	/// @param Iterable_List is a list that consists of iterated or not-iterated values
	/// @return true if founds an iterable, false otherwise 
	bool findNextIterable(int* iterable_row, int* iterable_col, Iterable_States(&Iterable_List)[9][9]);

public:

	/// @brief Constructor of the Game object
	Game();

	/// @brief Initialization of the Game object
	void Start();

	/// @brief Getter for the condition for finish
	/// @return bool, true if finished, false otherwise
	bool isFinished();

	/// @brief This method is responsible for the iteration between the menus. It calls the method of the current state 
	/// in the game (which is also a method), then current state method arranges next state. When iteration finishes,
	/// current state is setted as next state. Therefore this method can set the menu's of the game object accordingly.
	void Iterate();


	/* HAVE NOT DEFINED METHODS */

	/// @brief this function will be used in order to find all of the numbers in the sudoku
	void IterateAll();
};

#endif
