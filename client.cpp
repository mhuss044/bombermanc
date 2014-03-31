// connect to server, send commands u/d/l/r/b

#include <apr/apr.h>
#include <apr/apr_general.h>
#include <apr/apr_network_io.h>
#include <apr/apr_strings.h>

#include <stdlib.h>
#include <iostream>
#include "draw.h"

#define REMOTEHOST "localhost"
#define REMOTEPORT 40000

#define SOCKETTIMEOUT (APR_USEC_PER_SEC * 30)

using namespace std;

class data
{
public:
	int x, y, ex, ey, gx, gy;
	char lastMove, nextMove; 	// u,d,l,r,b
	char name[3], left[10], right[10], up[10], down[10];
};
data playerData;

bool moveUp();
bool moveDown();
bool moveRight();
bool moveLeft();
bool moveBomb();

void onlyUpi(int);
void onlyDowni(int);
void onlyRighti(int);
void onlyLefti(int);
void rnGi(int);
void obs(void);

//AI
void onlyUp(void);
void rnGesus(void);

void (*(logicPath[2]))(void);
void (*logic)(void);

int curLogic = 0;
apr_socket_t *s;

int main(void)
{
//	apr_status_t rv;
	apr_pool_t *mp;
	apr_sockaddr_t *sa;

	apr_initialize();
    	apr_pool_create(&mp, NULL);

	gameBoard board(100, 100);

	genRandomBoard(0, board.getBoard());

	// make new player, allow key input
	// start new ai
	cout << "GFG  fefefefff" << endl;

	if(apr_sockaddr_info_get(&sa, REMOTEHOST, APR_INET, REMOTEPORT, 0, mp) != APR_SUCCESS)
		cout << "Failed to get info on remote host: " << REMOTEHOST <<  endl;
 
    
   	if(apr_socket_create(&s, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp) != APR_SUCCESS)
		cout << "Failed to creat socket." << endl;

	// Specify socket options; blocking-with timeout socket
    	apr_socket_opt_set(s, APR_SO_NONBLOCK, 1);	// blocking socket
	apr_socket_timeout_set(s, SOCKETTIMEOUT);	// socket has timeout

    	if(apr_socket_connect(s, sa) != APR_SUCCESS)
		cout << "Failed to connect to remote host." << endl;
	else
		cout << "Connected to " << REMOTEHOST << ", at " << REMOTEPORT << endl;

	// After connect, respecify opts;
    	apr_socket_opt_set(s, APR_SO_NONBLOCK, 0);
	apr_socket_timeout_set(s, SOCKETTIMEOUT);

	logic = &rnGesus;
	// Send/recv;
	cout << "Playing.." << endl;
//	(*logic)();		
	logicPath[0] = &rnGesus;
	logicPath[1] = &onlyUp;
	//(*(logicPath+curLogic))();
	while(1)
	{
	
	rnGi(1);
	obs();
	}

// take step, rand dir
// detect
// esc?
// yes-> esc pattern
	cout << "Game over..quiting." << endl;



    	apr_socket_close(s);
	apr_terminate();

	return 0;
}

void obs(void)
{
	unsigned int ctr = 0;
	int x = -1, y = -1;
	char buf[10000];
	buf[4] = '\0';
    	apr_size_t len = sizeof(buf);
            
    	if(apr_socket_recv(s, buf, &len) == APR_EOF)
	{
		cout << "Failed to read." << endl;
		return;
	}
	
	if(strlen(buf) == 4)
		return;

	cout << "Read string of len: " << strlen(buf) << endl;

	// Get name;
	while(ctr < strlen(buf))
	{
		if(buf[ctr] == 'N' && buf[ctr+3] == 'e')
		{
			ctr+=7; 			// move past ":
			playerData.name[0] = buf[ctr];
			ctr++;
			playerData.name[1] = buf[ctr];
			playerData.name[2] = '\0';
			break;
		}
		ctr++;
	}

	// Get X;
	while(ctr < strlen(buf))
	{
		if(buf[ctr] == 'X')
		{
			ctr+=3;				// move past ":
			x = buf[ctr] - '0';
			
			// Get the rest of the digits
			while(1)
			{
				ctr++;			// move to next digit
				if(buf[ctr] != '"')
				{
					x*=10;
					x += buf[ctr] - '0';	
				}
				else
					break;
			}
			break;
		}
		ctr++;
	}

	cout << "Found an X to be: " << x << endl;

	// Get Y;
	while(ctr < strlen(buf))
	{
		if(buf[ctr] == 'Y')
		{
			ctr+=3;				// move past ":
			y = buf[ctr] - '0';
			
			// Get the rest of the digits
			while(1)
			{
				ctr++;			// move to next digit
				if(buf[ctr] != '"')
				{
					y*=10;
					y += buf[ctr] - '0';	
				}
				else
					break;
			}
			break;
		}
		ctr++;
	}

	cout << "Found an Y to be: " << y << endl;

	if(x != -1 && y != -1)
	{
		playerData.x = x;
		playerData.y = y;
	
	}
}

// AI
void rnGesus(void)
{
	bool quit = true;

	while(quit)
	{
		switch(rand()%4+1)
		{
			case 1:
				if(!moveUp())
					quit = false;
			break;
			case 2:
				if(!moveDown())
					quit = false;
			break;
			case 3:
				if(!moveRight())
					quit = false;
			break;
			case 4:
				if(!moveLeft())
					quit = false;
			break;
		}
	}
}

void onlyUp(void)
{
	bool quit = true;

	while(quit)
	{
		if(!moveUp())
			quit = false;

	}
}

void rnGi(int steps)
{
	bool quit = true;
	int cnt = 0;

	while(quit && cnt < steps)
	{
		switch(rand()%4+1)
		{
			case 1:
				if(!moveUp())
					quit = false;
			break;
			case 2:
				if(!moveDown())
					quit = false;
			break;
			case 3:
				if(!moveRight())
					quit = false;
			break;
			case 4:
				if(!moveLeft())
					quit = false;
			break;
		}
		cnt++;
	}
}

void onlyUpi(int steps)
{
	bool quit = true;
	int cnt = 0;

	while(quit && cnt < steps)
	{
		if(!moveUp())
			quit = false;
		cnt++;
	}
}
	
void onlyDowni(int steps)
{
	bool quit = true;
	int cnt = 0;

	while(quit && cnt < steps)
	{
		if(!moveDown())
			quit = false;

		cnt++;
	}
}

void onlyRighti(int steps)
{
	bool quit = true;
	int cnt = 0;

	while(quit && cnt < steps)
	{
		if(!moveRight())
			quit = false;

		cnt++;
	}
}

void onlyLefti(int steps)
{
	bool quit = true;
	int cnt = 0;

	while(quit && cnt < steps)
	{
		if(!moveLeft())
			quit = false;

		cnt++;
	}
}
	
bool moveUp()
{
	apr_size_t len;
	
	len = strlen("up\n");
	if(apr_socket_send(s, "up\n", &len) != APR_SUCCESS)
		return false;
	else 
		return true;
}


bool moveDown()
{
	apr_size_t len;
	
	len = strlen("down\n");
	if(apr_socket_send(s, "down\n", &len) != APR_SUCCESS)
		return false;
	else 
		return true;
}

bool moveLeft()
{
	apr_size_t len;
	
	len = strlen("left\n");
	if(apr_socket_send(s, "left\n", &len) != APR_SUCCESS)
		return false;
	else 
		return true;
}

bool moveRight()
{
	apr_size_t len;
	
	len = strlen("right\n");
	if(apr_socket_send(s, "right\n", &len) != APR_SUCCESS)
		return false;
	else 
		return true;
}

bool moveBomb()
{
	apr_size_t len;
	
	len = strlen("bomb\n");
	if(apr_socket_send(s, "bomb\n", &len) != APR_SUCCESS)
		return false;
	else 
		return true;
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
	
