#pragma once
#include "Header.h"
#include <iostream>
#include <string>
#include <vector>

//the types of pieces that are possible in the game
enum class pieceType{
	empty,
	x,
	o
};

//a single piece that takes up a single position on the board
class gamepiece {
private:
	//the type of piece (x, o, empty, or invalid), which is important for correctly printing the board
	pieceType type;
public:
	//initialize each piece as empty to fill out starting board with empty pieces
	gamepiece() : type(pieceType::empty) {};
	~gamepiece() {};
	//function to set this piece's type
	void setType(pieceType t);
	//function to get the type of this piece
	pieceType getType();
};

//the actual gameboard
class tictactoe {
private:
	//full array of all pieces on board
	int board_size = 9;
	//a variable to keep track of who the current player is
	pieceType player;
	//a vector to store all of the pieces on the board
	std::vector<gamepiece> pieces;
public:
	//set board size at initialization
	tictactoe();
	~tictactoe() {};
	//function to retrieve pieces from pieces vector
	std::vector<gamepiece> getPieces();
	//function to set a piece's type from this class
	void setPiece(int pos, pieceType t);
	//function to set the size of the board, for ease of changing board size later on
	void set_size(int size);
	//see declaration below for more info
	friend std::ostream& operator << (std::ostream& out, const tictactoe& ttt);
	//function to determine if pieces are in winning configuration
	bool done();
	//function to determine if the players draw a match
	bool draw();
	//prompt the user to enter proper coordinates for their next piece
	returnCases prompt(unsigned int& xpos, unsigned int& ypos);
	//determine the next player (player X or player O)
	//places the piece on the board at the given coordinates if they are valid
	//if they are not valid, it will make the player try again
	returnCases turn();
	//the main gameplay loop. Keeps the game moving to the next turn after a player has played and checks to see if win or draw conditions have been met or if the player has quit.
	returnCases play();
};

//determine the symbol by the given pieceType enum so that it will print the correct symbol for the piece type
int calcCoords(unsigned int width, unsigned int xpos, unsigned int ypos);

//this operator is overloaded so that the program knows how to get the piece types and the board will print out in the proper configuration
//currently set to print out as a 5x5 board where the outer positions are numbered and the second to last outer positions are spaces, leaving a 3x3 playing space
std::ostream& operator<<(std::ostream& s, tictactoe& g);

//a function containing the general formula for converting a cartesion coordinate pair to an array position
std::string getSymbol(pieceType t);