// player

typedef struct _state 
{
	int Turn;
	int TurnDuration;	// time.Duration
	char *name;		// string
	int X, Y, LastX, LastY;       
	int Bombs, MaxBomb, MaxRadius;
	bool Alive;
	SBoard board;

//	Alive                     bool
//	Board                     [][]*cell.Exported
//	GameObject                cell.GameObject
//	Message                   string
}state;

enum moveTypes
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	BOMB
}

void playerLogin(char *name)
{
}

void playeMove(moveTypes move)
{
	switch(move)
	{
		case UP:
		break;
		case DOWN:
		break;
		case LEFT:
		break;
		case RIGHT:
		break;
		case BOMB:
		break;
	}
}

void playerUpdate(void)
{
}
