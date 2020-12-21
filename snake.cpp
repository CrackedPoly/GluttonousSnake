#include "snake.h"
#include "score.h"
#include <time.h>

int hard = 5, snakeLength = 2, dir=3, hardLevel;
char ch;
node food;
node snake[600];
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
PIMAGE BACKGROUND = newimage();
PIMAGE FOOD = newimage();
PIMAGE SNAKE_BODY = newimage();
PIMAGE SNAKE_HEAD = newimage();


void PrintSnake()
{
	putimage_withalpha(NULL, SNAKE_HEAD, snake[0].x, snake[0].y);
	for (int i = 1; i < snakeLength; i++)
	{
		putimage_withalpha(NULL, SNAKE_BODY,snake[i].x, snake[i].y);
	}
	return;
}

/*** 判断是否撞墙或者自撞 ***/
bool IsCorrect() //! 容易晓得，撞墙或撞到自己就输出0 
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

/*** 随机打印食物 ***/
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

/*** 蛇的前进 ***/
bool go_ahead()//！ 前进这里他是用的一个新node temp 这个节点保存最后一个位置 。然后每个原来蛇身体的节点让它等于他们分别前面的一个节点 
{              //!   再通过蛇头这个节点加上 direct 就是向前移动了一个位置 
	node temp = snake[snakeLength - 1];;
	bool e = false;
	for (int i = snakeLength - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += INTVAL*direct[dir][0];//dir就是方向参数 
	snake[0].y += INTVAL*direct[dir][1];
	/*** 吃到了食物 ***/
	if (snake[0].x == food.x && snake[0].y == food.y)//!假如吃到了食物，就让它的尾巴重新加上去，所有前面要保留尾巴节点 
	{
		snakeLength++;
		e = true;
		SetCurrentScore(GetCurrentScore() + 1);
		RefreshScore();
		snake[snakeLength - 1] = temp;
	}
	/*** 输出此时蛇状态 ***/
	if(e)
		PrintFood();
	/*** 如果自撞 ***/
	if (!IsCorrect())//! 假如蛇头撞了，就游戏结束 
	{
		return false;
	}
	return true;
}

#include <stdio.h>

int x = 0;
bool GameStart()
{
	getimage(BACKGROUND, "image/background.png");
	GetZoomImage(FOOD, "image/food.png", 17, 17);
	GetZoomImage(SNAKE_BODY, "image/body.png", 17, 17);
	GetZoomImage(SNAKE_HEAD, "image/head.png", 17, 17);
	snake[0].x = 1 * INTVAL;
	snake[0].y = 2 * INTVAL;
	snake[1].x = 1 * INTVAL;
	snake[1].y = 1 * INTVAL;
	PrintFood();
	while (true)
	{
		PrintSnake();
		delay_ms(150 + 1000 / snakeLength);
		putimage_withalpha(NULL,BACKGROUND,17,17,17,17,18 * 17 + 19 * 2,28 * 17 + 29 * 2);
		putimage_withalpha(NULL, FOOD, food.x, food.y);
		if (kbhit())//!等你敲键盘下才会运行if里的语句 
		{
			ch = getch();
			if (ch >= 'a' && ch <= 'z') ch += 'A' - 'a';
			switch (ch)
			{          
			case 'A':
				if (dir == 2 || dir == 3)//！假如dir≠2/3就表示 蛇原来在左右移，就不用改方向 
					dir = 0;             //! 反之，dir=2/3就表示，蛇原来在上下移，就得把dir改成0,表示向左走   后面类似 
				break;
			case 'D':
				if (dir == 2 || dir == 3)
					dir = 1;
				break;
			case 'W':
				if (dir == 0 || dir == 1)
					dir = 2;
				break;
			case 'S':
				if (dir == 0 || dir == 1)
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