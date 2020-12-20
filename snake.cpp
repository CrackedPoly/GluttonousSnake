#include "snake.h"
#include <ctime>
#include <math.h>

int hard = 5, snakeLength = 5, dir=3, hardLevel;
char ch;
node food;
node snake[600];
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

void PrintSnake()
{
	snake[0].img = newimage();
	GetZoomImage(snake[0].img, "./image/head.png",17, 17);
	putimage_withalpha(NULL, snake[0].img, snake[0].x, snake[0].y);
	for (int i = 1; i <= snakeLength - 1; i++)
	{
		snake[i].img = newimage();
		GetZoomImage(snake[i].img, "./image/body.png", 17, 17);
		putimage_withalpha(NULL, snake[i].img,snake[i].x, snake[i].y);
	}
	return;
}

/*** �ж��Ƿ�ײǽ������ײ ***/
bool IsCorrect() //! �������ã�ײǽ��ײ���Լ������0 
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

/*** �����ӡʳ�� ***/
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
	food.img = newimage();
	GetZoomImage(food.img, "./image/food.png", 17, 17);
	putimage_withalpha(NULL,food.img,food.x, food.y);
	return true;
}

/*** �ߵ�ǰ�� ***/
bool go_ahead()//�� ǰ�����������õ�һ����node temp ����ڵ㱣�����һ��λ�� ��Ȼ��ÿ��ԭ��������Ľڵ������������Ƿֱ�ǰ���һ���ڵ� 
{              //!   ��ͨ����ͷ����ڵ���� direct ������ǰ�ƶ���һ��λ�� 
	node temp;
	bool e = false;
	temp = snake[snakeLength - 1];
	for (int i = snakeLength - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += INTVAL*direct[dir][0];//dir���Ƿ������ 
	snake[0].y += INTVAL*direct[dir][1];
	cleardevice(snake[1].img);//�����ͷ
	GetZoomImage(snake[1].img, "./image/body.png", 17, 17);
	putimage_withalpha(NULL,snake[1].img,snake[1].x, snake[1].y);  //!�����Ϊ�˰�ԭ����ͷλ�õı�ɷ���ͷ�ڵ��
	/*** �Ե���ʳ�� ***/
	if (snake[0].x == food.x && snake[0].y == food.y)//!����Ե���ʳ���������β�����¼���ȥ������ǰ��Ҫ����β�ͽڵ� 
	{
		snakeLength++;
		e = true;
		snake[snakeLength - 1] = temp;
	}
	/*** �����ʱ��״̬ ***/
	if (!e) //!�����Ǽ���e=false��������û�гԵ�ʳ��ʱ�Ͱ����һ��β�ͽڵ��ȥ��������㲻ȥ���Ļ��������������ˡ� 
	{
		cleardevice(temp.img);
	}
	else//�����e=true�������߳Ե���ʳ���������һ��ʳ�� 
		PrintFood();
	snake[0].img = newimage();
	GetZoomImage(snake[0].img, "./image/head.png", 17, 17);
	putimage_withalpha(NULL,snake[0].img,snake[0].x, snake[0].y);
	/*** �����ײ ***/
	if (!IsCorrect())//! ������ͷײ�ˣ�����Ϸ���� 
	{
		return false;
	}
	return true;
}

bool GameStart()
{
	snake[0].x = 1 * INTVAL;
	snake[0].y = 1 * INTVAL;
	PrintSnake();
	PrintFood();
	while (true)
	{
		/*** �Ѷ��泤�����Ӷ���� ***/
		hardLevel = (int)((double)snakeLength / (double)(XBLOCKS * YBLOCKS)); //!�������ǰ�潲�ģ�snake_lengthԭ���Ǹ�int��
		/*** ����ʱ�䣬��λ��ms ***/
		delay((long)(400 - 30 * hard) * (1 - sqrt(hardLevel)));
		/*** ���ܼ���������������ң����Դ˸ı䷽�� ***/
		if (kbhit()) //!���ü����²Ż�����if������
		{
			ch = getch();  //!��һ�����������������
			if (ch == -32) //!��c++�����������������ʱ�򣬻��ڻ����������������ַ�����һ���ַ���ASCii����� -32
			{              //!����һ��getch�����ѵ�һ���ַ���������ٸ������������ڻ������ĵڶ����ַ��Ĳ�ͬ������
				ch = getch();
				switch (ch)                   //! 72��ʾ���� 80��ʾ 75��ʾ���� 77��ʾ����
				{                             //! dir=0�� dir=1�� dir=2�� dir=3��
				case 72:                      //!ch=72ʱ ,����
					if (dir == 2 || dir == 3) //������dir��2/3�ͱ�ʾ ��ԭ���������ƣ��Ͳ��øķ���
						dir = 0;              //! ��֮��dir=2/3�ͱ�ʾ����ԭ���������ƣ��͵ð�dir�ĳ�0,��ʾ������   ��������
					break;
				case 80:
					if (dir == 2 || dir == 3)
						dir = 1;
					break;
				case 75:
					if (dir == 0 || dir == 1)
						dir = 2;
					break;
				case 77:
					if (dir == 0 || dir == 1)
						dir = 3;
					break;
				}
			}
		}
		/*** ǰ�� ***/
		if (!go_ahead())
			break; //!�ж�����û��ײ��ײ�˾���Ϸ����
		return false;
	}
}