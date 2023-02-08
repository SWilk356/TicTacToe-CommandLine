#include "Header.h"
#include <iostream>
#include <string>

using namespace std;

//return user usage message for improper calling of program, procced by incorrect number of command line arguments or improperly formed command line arguments
returnCases usage(char* program_name) {
    cout << "This program is a TicTacToe game. Please properly enter the name of the game when calling the program." << endl;
    cout << endl;
    cout << "Usage: " << program_name << " TicTacToe" << endl;

    return returnCases::usage_error;
}