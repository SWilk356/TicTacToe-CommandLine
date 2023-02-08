#include "makeGame.h"
using namespace std;

void gamepiece::setType(pieceType t) {
	type = t;
}

pieceType gamepiece::getType() {
	return type;
}

tictactoe::tictactoe() : player(pieceType::x){
	set_size(board_size);
}

void tictactoe::setPiece(int pos, pieceType t) {
	pieces[pos].setType(t);
}

void tictactoe::set_size(int size) {
	pieces.resize(size);
}

vector<gamepiece> tictactoe::getPieces() {
	return pieces;
};

bool tictactoe::done() {
	double width = sqrt(board_size);
	bool x_vert_case;
	bool o_vert_case;
	bool x_horiz_case;
	bool o_horiz_case;
	bool x_diag_case0;
	bool o_diag_case0;
	bool x_diag_case2;
	bool o_diag_case2;

	int currPiece;

	//horizontal check
	for (currPiece = 0; currPiece < width; currPiece++) {
		x_horiz_case = tictactoe::pieces[currPiece].getType() == pieceType::x && tictactoe::pieces[currPiece + 3].getType() == pieceType::x && tictactoe::pieces[currPiece + 6].getType() == pieceType::x;
		o_horiz_case = tictactoe::pieces[currPiece].getType() == pieceType::o && tictactoe::pieces[currPiece + 3].getType() == pieceType::o && tictactoe::pieces[currPiece + 6].getType() == pieceType::o;


		//if 3 in a row horizontally, then return true
		if (x_horiz_case || o_horiz_case) {
			return true;
		}
		else if (currPiece == 0) {
			x_diag_case0 = tictactoe::pieces[currPiece].getType() == pieceType::x && tictactoe::pieces[currPiece + 4].getType() == pieceType::x && tictactoe::pieces[currPiece + 8].getType() == pieceType::x;
			o_diag_case0 = tictactoe::pieces[currPiece].getType() == pieceType::o && tictactoe::pieces[currPiece + 4].getType() == pieceType::o && tictactoe::pieces[currPiece + 8].getType() == pieceType::o;
			//diagonal case checking from bottom left corner
			if (x_diag_case0 || o_diag_case0) {
				return true;
			}
		}
		else if (currPiece == width - 1) {
			x_diag_case2 = tictactoe::pieces[currPiece].getType() == pieceType::x && tictactoe::pieces[currPiece + 2].getType() == pieceType::x && tictactoe::pieces[currPiece + 4].getType() == pieceType::x;
			o_diag_case2 = tictactoe::pieces[currPiece].getType() == pieceType::o && tictactoe::pieces[currPiece + 2].getType() == pieceType::o && tictactoe::pieces[currPiece + 4].getType() == pieceType::o;
			//diagonal case checking from top left corner
			if (x_diag_case2 || o_diag_case2) {
				return true;
			}
		}
	}

	//vertical check
	for (int currPieces = 0; currPieces <= 6; currPieces += 3) {
		x_vert_case = tictactoe::pieces[currPieces].getType() == pieceType::x && tictactoe::pieces[currPieces + 1].getType() == pieceType::x && tictactoe::pieces[currPieces + 2].getType() == pieceType::x;
		o_vert_case = tictactoe::pieces[currPieces].getType() == pieceType::o && tictactoe::pieces[currPieces + 1].getType() == pieceType::o && tictactoe::pieces[currPieces + 2].getType() == pieceType::o;
		//if 3 in a row vertically, then return true
		if (x_vert_case || o_vert_case) {
			return true;
		}
	}

	return false;
}

bool tictactoe::draw() {
	int nonEmptyPieces = 0;

	//if there are any pieces on the board that are not of type empty, then increment nonEmptyPieces.
	for (gamepiece g : pieces) {
		if (g.getType() != pieceType::empty) {
			nonEmptyPieces++;
		}
	}

	//if we have counted 9 pieces on the board that are not of type empty and no win conditions have been met, then it is a draw.
	if (nonEmptyPieces == 9 && done() == false) {
		return true;
	}
	else {
		return false;
	}
}

 returnCases tictactoe::prompt(unsigned int& xpos, unsigned int& ypos) {
	string input;

	cout << "Please enter a pair of coordinates. The x and y values must be in the range of 2-4 and be separated by a comma. ex: 2,4 or 3,3" << endl;
	cout << "Enter 'quit' to exit the program." << endl;
	cin >> input;
		
	//if player quits before making next play, don't check input. Just return user_quit_game condition.
	if (input == "quit") {
		return returnCases::user_quit_game;
	}

	//check that the input is the correct length, is a number, has a comma in between the numbers, and is within the range of the board dimensions.
	if (input.length() == 3) {
		if (isdigit(input.at(0)) && input.at(1) == ',' && isdigit(input.at(2))) {
			xpos = (unsigned int)input[0]-48;
			ypos = (unsigned int)input[2]-48;

			if ((xpos >= 2 && xpos <= 4) && (ypos >= 2 && ypos <= 4)) {
				return returnCases::game_continue;
			}
			else {
				cout << "Coordinates not within board dimensions." << endl;
				return returnCases::coords_outside_board;
			}			
		}
		else if (input.at(1) != ',') {
			cout << "No comma between the given coordinates." << endl;
			return returnCases::no_comma;
		}
		else {
			cout << "Coordinates are not numbers." << endl;
			return returnCases::coords_are_not_numbers;
		}
	}
	else {
		cout << "Improperly formed coordinates." << endl;
		return returnCases::not_enough_coords_given;
	}
}

 returnCases tictactoe::turn() {
	 unsigned int xpos;
	 unsigned int ypos;

	 cout << "Your turn, Player " + getSymbol(player) + "!" << endl;

	 returnCases getCoords = prompt(xpos, ypos);

	//while the given coords are invalid, keep prompting the user
	//if user has not quit the game, continue to calculate the coordinates
	//if user has quit the game, return result
	 while (getCoords != returnCases::game_continue) {
		 if (getCoords == returnCases::user_quit_game) {
			 return getCoords;
		 }
		 getCoords = prompt(xpos, ypos);
	 }

	int given_coords = calcCoords(3, xpos - 2, ypos - 2);

	//if the space where the user wants to put the piece is empty, set the type of the piece in the pieces vector as the given type
	//if the space is not empty, return space_not_empty case
	if (pieces[given_coords].getType() == pieceType::empty) {
		pieces[given_coords].setType(player);
	}
	else {
		cout << "That space is not empty!" << endl;
		return returnCases::space_not_empty;
	}

	//change to the next player
	if (player == pieceType::x) {
		player = pieceType::o;
	}
	else {
		player = pieceType::x;
	}

	return returnCases::game_continue;
 }

 returnCases tictactoe::play() {
	 cout << *this << endl;

	 returnCases result = turn();
	 int numPlays = 0;

	 //while the user has not quit, check if the game_continue return case has been sent back from the turn() method, indicating that valid coordinates have been given
	 //if yes, increment the number of plays and print the board
	 //check draw and win conditions
	 //determine which player (X or O) is the winner
	 while (result != returnCases::user_quit_game) {
		 if (result == returnCases::game_continue) {
			 numPlays++;
			 cout << *this << endl;
		 }

		 if (draw()) {
			 cout << "After " << numPlays << " plays, there are no more moves left, and no one has won. The game is drawn." << endl;
			 return returnCases::game_drawn;
		 }

		 result = turn();

		 if (done()) {
			 cout << *this << endl;
			 cout << "3 in a row" << endl;
			 int countX = 0;
			 int countO = 0;
			 for (gamepiece p : pieces) {
				 if (p.getType() == pieceType::x) {
					 countX++;
				 }
				 else if (p.getType() == pieceType::o) {
					 countO++;
				 }
			 }

			 if (countX > countO) {
				 cout << "Player X wins!" << endl;
			 }
			 else {
				 cout << "Player O wins!" << endl;
			 }

			 return returnCases::game_won;
		 }
	 }

	 //if the player has quit, then it will not enter the gameplay loop.
	 //return the user_quit_game return case
	 cout << "The game was quit after " << numPlays << " plays." << endl;
	 return returnCases::user_quit_game;
 }

//the board is a 5x5 square so it prints from left to right, top to bottom
//the outer coordinates contain numbers the label the axes, so the actual playing space on the board is a 3x3 square
ostream& operator<<(ostream& s, tictactoe& g) {
	vector<gamepiece> p = g.getPieces();
	unsigned int coords;

	//print out board in correct configuration according to dimensions
	for (int i = 5; i >= 0; i--) {
		for (size_t j = 0; j <= 5; j++) {
			if (i == 0) {
				s << j;
				s << " ";
			} else if (j == 0) {
				s << i;
				s << " ";
			}
			else if (i == 1 || j == 1 || i == 5 || j == 5) {
				s << "  ";
			}
			else {
				coords = calcCoords(3, j-2, i-2);
				//pass to stream object s the type of gamepiece object at position coords in p array of gameboard object g and use getSymbol method to convert streamable type string
				s << getSymbol(p[coords].getType());
				s << " ";
			}
		}
		s << std::endl;
	}

	return s;
}

//given a piece in the array, this function will determining the corresponding symbol
// N for empty positions on the board, X for x pieces, and O for o pieces, and I for invalid inputs
string getSymbol(pieceType t) {
	if (t == pieceType::x) {
		return "X";
	}
	else if (t == pieceType::o) {
		return "O";
	}
	else {
		return "N";
	}
}

int calcCoords(unsigned int width, unsigned int xpos, unsigned int ypos) {
	return width * xpos + ypos;
}