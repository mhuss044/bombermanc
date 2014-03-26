// draw the board
// playres are #$%@
// walls |-
// bombs 0
// rock *
// ground space
// flame &

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

#define NUMTILES 6	//|-0* &
#define BOARDWIDTH 100
#define BOARDHEIGHT 100  

#define TILEWALLV '|' // vertical wall
#define TILEWALLH '-'
#define TILEBOMB '0'
#define TILEROCK '*'
#define TILEGROUND ' '
#define TILEFLAME '&'

//char tiles[6]={'|','-','0','*',' ','&'}
char tiles[]="|-0* &";

class gameBoard
{
private:
	int boardWidth = 100, boardHeight = 100;
	char **tiles = NULL;
public:
	gameBoard(int width = 100, int height = 100)
	{
		boardWidth = width;
		boardHeight = height;

		tiles = new char*[boardHeight];

		for(int x = 0; x < boardHeight; x++)
			*(tiles+x) = new char[boardWidth];
	}

	~gameBoard()
	{
		if(tiles == NULL)
			return;
		// delete char array at each tiles+x
		for(int x = 0; x < boardHeight; x++)
			delete *(tiles+x);
		// delete char* arr at tiles
		delete tiles;
	}

	char **getBoard(void)
	{
		return tiles;
	}

	int getWidth(void)
	{
		return boardWidth;
	}
	
	int getHeight(void)
	{
		return boardHeight;
	}
};

void genRandomBoard(int offset, char **board)
{
	for(int x = 0; x < BOARDWIDTH; x++)
		for(int y = 0; y < BOARDHEIGHT; y++)
			board[x][y] = tiles[rand()%NUMTILES + 1];	// Random tile

	// forge paths thru the random gend board
}

void drawWallH(int x, int y, char **board)
{
	board[x][y] = TILEWALLH; 	
}

void drawWallV(int x, int y, char **board)
{
	board[x][y] = TILEWALLV; 	
}

void drawGround(int x, int y, char **board)
{
	board[x][y] = TILEGROUND; 	
}

void drawRock(int x, int y, char **board)
{
	board[x][y] = TILEROCK; 	
}

void drawBomb(int x, int y, char **board)
{
	board[x][y] = TILEBOMB; 	
}

void drawFlame(int x, int y, char **board)
{
	board[x][y] = TILEFLAME; 	
}

void drawPlayer(int x, int y, char player, char **board)
{
	board[x][y] = player; 	
}

void drawBombPowerUp(int x, int y, char **board)
{
	board[x][y] = TILEWALLV; 	
}

void drawBoard(char **board,int width,int height)
{
	cout << endl;
	for(int x = 0; x < width; x++)
		cout << "0";
	cout << endl;
	for(int x = 0; x < height; x++) 
		cout << board[x] << endl;
}

