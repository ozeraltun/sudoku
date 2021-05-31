#ifndef _States_
#define _States_

/// @brief sudoku values must be either of the following:
enum writtenStates { std_Writen, hand_Writen, not_Writen };

/// @brief while iterating followings will be used:
enum Iterable_States { have_Iterated, haveNot_Iteraded };

/// @brief Game states are the following:
enum States {
	unknown_State, main_Menu, load_Game, enter_As_Full, enter_As_Line, 
	sudoku_Loaded, solveByHand, solveByMachine, load_Example_Game
};
#endif
