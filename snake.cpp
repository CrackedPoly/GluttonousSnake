/***********************************************
*  Copyright ���ﶷ
*
*  @file     snake.cpp
*  @brief    ��Ҫ������Ϸ����ʱ�ߵ��˶��Լ��߼����ж�
*  @author   ���󲩣��޼�
*  @date     2020/12/21
*
***********************************************/
#include "snake.h"
#include "score.h"
#include <time.h>


int snakeLength = 2, dir=3;			//�ߵĳ�ʼ���Ⱥͳ�ʼ�ж�����
char ch;							//���ܼ�������
node food;							//��¼ʳ���λ��
node snake[600];					//��¼�ߵ�λ��
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };	//��Ӧ�ߵ��ж��ĸ�����,�ֱ�Ϊ��,��,��,��
PIMAGE BACKGROUND = newimage();		//����
PIMAGE FOOD = newimage();			//ʳ��
PIMAGE SNAKE_BODY = newimage();		//����
PIMAGE SNAKE_HEAD = newimage();		//��ͷ

/*
��ӡ��
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
������Ϸʱ��ʼ����
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
�ж����Ƿ�ײǽ������ײ
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
�����ӡʳ��
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
�ߵ�ǰ��
*/
bool go_ahead()
{ 
	node temp = snake[snakeLength - 1];;
	bool e = false;
	for (int i = snakeLength - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += INTVAL*direct[dir][0];
	snake[0].y += INTVAL*direct[dir][1];
	//����Ե���ʳ��
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		snakeLength++;
		e = true;
		SetCurrentScore(GetCurrentScore() + 1);
		RefreshScore();
		snake[snakeLength - 1] = temp;
		PrintFood();
	}
	//�����ײ����ײǽ
	if (!IsCorrect())
	{
		return false;
	}
	return true;
}

/*
��Ϸ��ʼ
*/
bool GameStart()
{	//����ͼ��
	getimage(BACKGROUND, "image/background.png");
	GetZoomImage(FOOD, "image/food.png", 17, 17);
	GetZoomImage(SNAKE_BODY, "image/body.png", 17, 17);
	GetZoomImage(SNAKE_HEAD, "image/head.png", 17, 17);
	InitSnake();
	PrintFood();
	while (true)
	{
		PrintSnake();
		delay_ms(150 + 1000 / snakeLength);		//��ʱ����,�ﵽˢ����Ļ��Ч��
		putimage_withalpha(NULL,BACKGROUND,17,17,17,17,18 * 17 + 19 * 2,28 * 17 + 29 * 2);
		putimage_withalpha(NULL, FOOD, food.x, food.y);
		if (kbhit())							//���¼��̲Ż�����if������,�ı�dir��ֵ�Ӷ��ı䷽��
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