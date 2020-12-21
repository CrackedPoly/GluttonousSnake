/***********************************************
*  Copyright 窝里斗
*
*  @file     snake.h
*  @brief    定义了坐标结构,蛇和食物的有关信息和函数
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/
#include "ui.h"
#define INTVAL 19
#define XBLOCKS 20
#define YBLOCKS 30

typedef struct node//节点
{
	int x, y;
}node;

extern int hard, snakeLength, dir;
extern node food;
extern node snake[600];
extern int direct[4][2];

/*
打印蛇
*/
void PrintSnake();

/*
重新游戏时初始化蛇
*/
void InitSnake();

/*
判断蛇是否撞墙或者自撞
*/
bool IsCorrect();

/*
随机打印食物
*/
bool PrintFood();

/*
蛇的前进
*/
bool go_ahead();

/*
游戏开始
*/
bool GameStart();
