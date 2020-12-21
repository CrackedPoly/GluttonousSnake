/***********************************************
*  Copyright 窝里斗
*
*  @file     snake.cpp
*  @brief    主要负责游戏运行时蛇的运动以及逻辑性判断
*  @author   刘轶博，罗鉴
*  @date     2020/12/21
*
***********************************************/
#include "snake.h"
#include "score.h"
#include <time.h>


int snakeLength = 2, dir=3;			//蛇的初始长度和初始行动方向
char ch;							//接受键盘输入
node food;							//记录食物的位置
node snake[600];					//记录蛇的位置
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };	//对应蛇的行动四个方向,分别为左,右,上,下
PIMAGE BACKGROUND = newimage();		//背景
PIMAGE FOOD = newimage();			//食物
PIMAGE SNAKE_BODY = newimage();		//蛇身
PIMAGE SNAKE_HEAD = newimage();		//蛇头

/*
打印蛇
*/
void PrintSnake()
{
	putimage_withalpha(NULL, SNAKE_HEAD, snake[0].x, snake[0].y);
	for (int i = 1; i < snakeLength; i++)
	{
		putimage_withalpha(NULL, SNAKE_BODY,snake[i].x, snake[i].y);
	}
	return;
}

/*
重新游戏时初始化蛇
*/
void InitSnake()
{
	snake[0].x = 1 * INTVAL;
	snake[0].y = 2 * INTVAL;
	snake[1].x = 1 * INTVAL;
	snake[1].y = 1 * INTVAL;
	snakeLength = 2;
}

/*
判断蛇是否撞墙或者自撞
*/
bool IsCorrect()
{
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == INTVAL*(XBLOCKS-1) || snake[0].y == INTVAL*(YBLOCKS-1)) 
		return false;
	for (int i = 1; i <= snakeLength - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) 
			return false;
	}
	return true;
}

/*
随机打印食物
*/
bool PrintFood()
{
	srand((unsigned)time(0));
	bool e;
	while (1)
	{
		e = true;
		int i = INTVAL*(random(XBLOCKS-2) + 1), j = INTVAL*(random(YBLOCKS-2) + 1);
		food.x = i; 
		food.y = j;
		for (int k = 0; k <= snakeLength - 1; k++)
		{
			if (snake[k].x == food.x && snake[k].y == food.y)
			{
				e = false;
				break;
			}
		}
		if (e) 
			break;
	}
	putimage_withalpha(NULL, FOOD, food.x, food.y);
	return true;
}

/*
蛇的前进
*/
bool go_ahead()
{ 
	node temp = snake[snakeLength - 1];;
	bool e = false;
	for (int i = snakeLength - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += INTVAL*direct[dir][0];
	snake[0].y += INTVAL*direct[dir][1];
	//如果吃到了食物
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		snakeLength++;
		e = true;
		SetCurrentScore(GetCurrentScore() + 1);
		RefreshScore();
		snake[snakeLength - 1] = temp;
		PrintFood();
	}
	//如果自撞或者撞墙
	if (!IsCorrect())
	{
		return false;
	}
	return true;
}

/*
游戏开始
*/
bool GameStart()
{	//加载图像
	getimage(BACKGROUND, "image/background.png");
	GetZoomImage(FOOD, "image/food.png", 17, 17);
	GetZoomImage(SNAKE_BODY, "image/body.png", 17, 17);
	GetZoomImage(SNAKE_HEAD, "image/head.png", 17, 17);
	InitSnake();
	PrintFood();
	while (true)
	{
		PrintSnake();
		delay_ms(150 + 1000 / snakeLength);		//延时函数,达到刷新屏幕的效果
		putimage_withalpha(NULL,BACKGROUND,17,17,17,17,18 * 17 + 19 * 2,28 * 17 + 29 * 2);
		putimage_withalpha(NULL, FOOD, food.x, food.y);
		if (kbhit())							//敲下键盘才会运行if里的语句,改变dir的值从而改变方向
		{
			ch = getch();
			if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
			switch (ch)
			{          
			case 'A':
				if (dir != 1)
					dir = 0;
				break;
			case 'D':
				if (dir != 0)
					dir = 1;
				break;
			case 'W':
				if (dir != 3)
					dir = 2;
				break;
			case 'S':
				if (dir != 2)
					dir = 3;
				break;
			}
		}
		if (!go_ahead()) {
			break;
		}
	}
	return false;
}