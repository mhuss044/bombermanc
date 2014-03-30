// connect to server, send commands u/d/l/r/b

#include <apr/apr.h>
#include <apr/apr_general.h>
#include <apr/apr_network_io.h>
#include <apr/apr_strings.h>

#include <stdlib.h>
#include <iostream>
#include "draw.h"

#define REMOTEHOST "localhost"
#define REMOTEPORT 9000

#define SOCKETTIMEOUT (APR_USEC_PER_SEC * 30)

using namespace std;

int main(void)
{
	apr_status_t rv;
	apr_pool_t *mp;
	apr_socket_t *s;
	apr_sockaddr_t *sa;

	apr_initialize();
    	apr_pool_create(&mp, NULL);

	gameBoard board(100, 100);

	genRandomBoard(0, board.getBoard());

	// make new player, allow key input
	// start new ai
	cout << "GFG fff" << endl;

	if(apr_sockaddr_info_get(&sa, REMOTEHOST, APR_INET, REMOTEPORT, 0, mp) != APR_SUCCESS)
		cout << endl << "Failed to get info on remote host";
    
   	if(apr_socket_create(&s, sa->family, SOCK_STREAM, APR_PROTO_TCP, mp) != APR_SUCCESS)
		cout << endl << "Failed to creat socket.";

	// Specify socket options; blocking-with timeout socket
    	apr_socket_opt_set(s, APR_SO_NONBLOCK, 1);	// blocking socket
	apr_socket_timeout_set(s, SOCKETTIMEOUT);	// socket has timeout

    	if(apr_socket_connect(s, sa) != APR_SUCCESS)
		cout << endl << "Failed to connect to remote host.";

	// After connect, respecify opts;
    	apr_socket_opt_set(s, APR_SO_NONBLOCK, 0);
	apr_socket_timeout_set(s, SOCKETTIMEOUT);

    	apr_socket_close(s);
	apr_terminate();

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
	
