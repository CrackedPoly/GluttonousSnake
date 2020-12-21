#include "ui.h"
#define INTVAL 19
#define XBLOCKS 20
#define YBLOCKS 30

typedef struct node//½Úµã
{
	int x, y;
}node;

extern int hard, snakeLength, dir;
extern node food;
extern node snake[600];
extern int direct[4][2];


void PrintSnake();
bool IsCorrect();
bool PrintFood();
bool go_ahead();
bool GameStart();