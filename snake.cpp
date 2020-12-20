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
	food.img = newimage();
	GetZoomImage(food.img, "./image/food.png", 17, 17);
	putimage_withalpha(NULL,food.img,food.x, food.y);
	return true;
}

/*** 蛇的前进 ***/
bool go_ahead()//！ 前进这里他是用的一个新node temp 这个节点保存最后一个位置 。然后每个原来蛇身体的节点让它等于他们分别前面的一个节点 
{              //!   再通过蛇头这个节点加上 direct 就是向前移动了一个位置 
	node temp;
	bool e = false;
	temp = snake[snakeLength - 1];
	for (int i = snakeLength - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += INTVAL*direct[dir][0];//dir就是方向参数 
	snake[0].y += INTVAL*direct[dir][1];
	cleardevice(snake[1].img);//清除蛇头
	GetZoomImage(snake[1].img, "./image/body.png", 17, 17);
	putimage_withalpha(NULL,snake[1].img,snake[1].x, snake[1].y);  //!这个是为了把原来蛇头位置的变成非蛇头节点的
	/*** 吃到了食物 ***/
	if (snake[0].x == food.x && snake[0].y == food.y)//!假如吃到了食物，就让它的尾巴重新加上去，所有前面要保留尾巴节点 
	{
		snakeLength++;
		e = true;
		snake[snakeLength - 1] = temp;
	}
	/*** 输出此时蛇状态 ***/
	if (!e) //!这里是假如e=false，就是蛇没有吃到食物时就把最后一个尾巴节点给去掉，如果你不去掉的话，它就留着那了。 
	{
		cleardevice(temp.img);
	}
	else//！如果e=true，就是蛇吃到了食物，就再生成一个食物 
		PrintFood();
	snake[0].img = newimage();
	GetZoomImage(snake[0].img, "./image/head.png", 17, 17);
	putimage_withalpha(NULL,snake[0].img,snake[0].x, snake[0].y);
	/*** 如果自撞 ***/
	if (!IsCorrect())//! 假如蛇头撞了，就游戏结束 
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
		/*** 难度随长度增加而提高 ***/
		hardLevel = (int)((double)snakeLength / (double)(XBLOCKS * YBLOCKS)); //!这个就是前面讲的，snake_length原来是个int，
		/*** 调节时间，单位是ms ***/
		delay((long)(400 - 30 * hard) * (1 - sqrt(hardLevel)));
		/*** 接受键盘输入的上下左右，并以此改变方向 ***/
		if (kbhit()) //!等敲键盘下才会运行if里的语句
		{
			ch = getch();  //!读一个你输入的上下左右
			if (ch == -32) //!在c++里上下左右在输入的时候，会在缓存区里生成两个字符，第一个字符的ASCii码就是 -32
			{              //!先用一个getch（）把第一个字符给清除，再根据上下左右在缓存区的第二个字符的不同来区别。
				ch = getch();
				switch (ch)                   //! 72表示上移 80表示 75表示左移 77表示右移
				{                             //! dir=0左 dir=1右 dir=2上 dir=3下
				case 72:                      //!ch=72时 ,上移
					if (dir == 2 || dir == 3) //！假如dir≠2/3就表示 蛇原来在左右移，就不用改方向
						dir = 0;              //! 反之，dir=2/3就表示，蛇原来在上下移，就得把dir改成0,表示向左走   后面类似
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
		/*** 前进 ***/
		if (!go_ahead())
			break; //!判断蛇有没有撞，撞了就游戏结束
		return false;
	}
}