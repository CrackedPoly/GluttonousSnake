/***********************************************
*  Copyright ���ﶷ
*
*  @file     snake.h
*  @brief    ����������ṹ,�ߺ�ʳ����й���Ϣ�ͺ���
*  @author   ���󲩣��޼�
*  @date     2020/12/20
*
***********************************************/
#include "ui.h"
#define INTVAL 19
#define XBLOCKS 20
#define YBLOCKS 30

typedef struct node//�ڵ�
{
	int x, y;
}node;

extern int hard, snakeLength, dir;
extern node food;
extern node snake[600];
extern int direct[4][2];

/*
��ӡ��
*/
void PrintSnake();

/*
������Ϸʱ��ʼ����
*/
void InitSnake();

/*
�ж����Ƿ�ײǽ������ײ
*/
bool IsCorrect();

/*
�����ӡʳ��
*/
bool PrintFood();

/*
�ߵ�ǰ��
*/
bool go_ahead();

/*
��Ϸ��ʼ
*/
bool GameStart();
