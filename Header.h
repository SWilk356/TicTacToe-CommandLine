#pragma once
#include <string>

//simply to make indexing into argv and passing command line arguments more descriptive
enum Index {
	progName,
	gameName,
	numArgs
};

//all of the possible return cases for actions in the program, including errors for invalid user input and game end cases
enum class returnCases {
	game_won,
	game_drawn,
	game_continue,
	coords_outside_board,
	no_comma,
	coords_are_not_numbers,
	not_enough_coords_given,
	space_not_empty,
	user_quit_game,
	usage_error = 127
};

//a function for printing to the user a usage statement summarizing the purpose of the program and explaining how to properly call the program
//procced by incorrect number of command line arguments are improperly formed command line arguments
returnCases usage(char* program_name);