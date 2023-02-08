// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "makeGame.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != Index::numArgs || (string)argv[Index::gameName] != "TicTacToe") {
        return (int)usage(argv[Index::progName]);
    }
    else {
        tictactoe board;

        return (int)board.play();
    }  
}