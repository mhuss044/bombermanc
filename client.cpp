// connect to server, send commands u/d/l/r/b

#include <iostream>
#include "draw.h"

char **board = NULL;

using namespace std;

int main(void)
{
	gameBoard board(100, 100);

	genRandomBoard(0, board.getBoard());
	
	// make new player, allow key input
	// start new ai
	cout << "GFG" << endl;
	return 0;
}

/*
	board = new char*[BOARDWIDTH];			// board points to an array of char* elements
	
	for(int x = 0; x < BOARDWIDTH; x++)
		board[x] = new char[BOARDHEIGHT];	// board + x = points to an array of characters

	
	// Delete arr at board[x];
	for(int x = 0; x < BOARDWIDTH; x++)
		if(board != NULL)
			delete board[x];
	delete board;
*/
	
