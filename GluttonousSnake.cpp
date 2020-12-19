#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>//! 为了用函数time() 
#include <conio.h>
#include <cmath>
#include <windows.h>//!这个就是为了用句柄 和一个cls（）清屏的函数 
#pragma warning(disable: 4996)
//！就是爸爸的备注 
using namespace std;

/*** 光标定位 ***/
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);// ！ 不晓得啥，查了下，叫句柄。反正就是windows里调下光标模式的东西。 
COORD coord;

void locate(int x, int y)//!定位光标的，locate（x，y) 就是把光标移到（x,y)去 
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};

/*** 隐藏光标 ***/
void hide()          //!把光标给隐藏了，好看些 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*** 生成随机数 ***/
double random(double start, double end)        //!生成start到end之间的随机数 
{
	return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

/*** 定义地图的长宽，蛇的坐标，长度，方向，食物的位置 ***/
int m, n;//!m地图宽度，n地图长度 

struct node//!节点，用来表示蛇 
{
	int x, y;
}snake[1000];

int snake_length, dir;//!dir 是为了后面放你的上下左右而声明的 
node food;
int direct[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } }; //!direct方向 

/*** 输出墙 ***/
void print_wall()//！就是墙 
{
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
	cout << endl;
	for (int j = 0; j <= m - 1; j++)
	{
		cout << "|";
		for (int i = 1; i <= n; i++) cout << " ";
		cout << "|" << endl;
	}
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
}

/*** 首次输出蛇，其中snake[0]代表头 ***/
void print_snake()    //! 这个函数是首先把光标定位到最初蛇的位置输出个蛇头，接下来就是把身体给输出了。 
{
	locate(snake[0].x, snake[0].y);
	cout << "@";
	for (int i = 1; i <= snake_length - 1; i++)
	{
		locate(snake[i].x, snake[i].y);
		cout << "*";
	}
}

/*** 判断是否撞墙或者自撞 ***/
bool is_correct() //! 容易晓得，撞墙或撞到自己就输出0 
{
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == m + 1 || snake[0].y == n + 1) return false;
	for (int i = 1; i <= snake_length - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return false;
	}
	return true;
}

/*** 随机生成并输出食物位置 ***/
bool print_food()//! 先设置随机种子，用随机数生成食物的位置，再把食物$放在里面。而且他这里特意的不让食物生成在蛇的身体上就做了一次检测。 
{
	srand((unsigned)time(0));
	bool e;
	while (1)
	{
		e = true;
		int i = (int)random(0, m) + 1, j = (int)random(0, n) + 1;
		food.x = i; food.y = j;
		for (int k = 0; k <= snake_length - 1; k++)
		{
			if (snake[k].x == food.x && snake[k].y == food.y)
			{
				e = false; break;
			}
		}
		if (e) break;
	}
	locate(food.x, food.y);
	cout << "$";
	return true;
}

/*** 蛇的前进 ***/
bool go_ahead()//！ 前进这里他是用的一个新node temp 这个节点保存最后一个位置 。然后每个原来蛇身体的节点让它等于他们分别前面的一个节点 
{              //!   再通过蛇头这个节点加上 direct 就是向前移动了一个位置 
	node temp;
	bool e = false;
	temp = snake[snake_length - 1];
	for (int i = snake_length - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	snake[0].x += direct[dir][0];//!发现没有，dir就是你的方向参数 
	snake[0].y += direct[dir][1];
	locate(snake[1].x, snake[1].y);
	cout << "*";  //!这个是为了把原来蛇头位置的 @ 变成非蛇头节点的 *  
	/*** 吃到了食物 ***/
	if (snake[0].x == food.x && snake[0].y == food.y)//!假如吃到了食物，就让它的尾巴重新加上去，所有前面要保留尾巴节点 
	{
		snake_length++;
		e = true;
		snake[snake_length - 1] = temp;
	}
	/*** 输出此时蛇状态 ***/
	if (!e) //!这里是假如e=false，就是蛇没有吃到食物时就把最后一个尾巴节点给去掉，如果你不去掉的话，它就留着那了。 
	{
		locate(temp.x, temp.y);
		cout << " ";
	}
	else//！如果e=true，就是蛇吃到了食物，就再生成一个食物 
		print_food();
	locate(snake[0].x, snake[0].y);//!蛇头又得输出出来 
	cout << "@";
	/*** 如果自撞 ***/
	if (!is_correct())//! 假如蛇头撞了，就游戏结束 
	{
		system("cls");
		cout << "You lose!" << endl << "Length: " << snake_length << endl;
		return false;
	}
	return true;
}

/*** 主函数 ***/
int main()
{
	cout << "--------------------贪吃蛇---------------------" << endl;
	cout << "请先输入两个数,表示地图大小.要求长宽均不小于10." << endl;
	cout << "请注意窗口大小,以免发生错位.建议将窗口调为最大." << endl;
	cout << "再选择难度.请在1-10中输入1个数,1最简单,10则最难" << endl;
	cout << "然后进入游戏画面,以方向键控制方向.祝你游戏愉快!" << endl;
	cout << "-----------------------------------------------" << endl;
	cin >> m >> n;              //!最开始输入宽度和长度 
	if (m < 10 || n < 10 || m>25 || n>40)//!它这里的限制是因为食物生成函数里的食物坐标的范围就这么大，如果你要改的话，食物生成函数也得改。 
	{
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}
	int hard;
	cin >> hard;//!难度选择 
	if (hard <= 0 || hard > 100)
	{
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}
	/*** 数据全部初始化，包括蛇长，位置，方向 ***/
	snake_length = 5; //最开始蛇长为 5
	clock_t a, b; //!一种叫做clock_t的数据类型（其实就是long，你用哪个都可以）， 
				  //!  与clock（）函数对应 ,clock()函数返回程序从启动到函数调用所占CPU的时间，为了后面的难度提高使用，花样这么多 
	char ch;        //!这是为了后面读你的方向键，就是上下左右 
	double hard_len;//!这里是为了搞花样才声明的 
	for (int i = 0; i <= 4; i++)//!最开始随便把蛇搞到一个位置去 
	{
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}
	dir = 3;
	/*** 输出初始地图，蛇与食物 ***/
	system("cls");//!清屏 
	hide();//! 隐藏光标 
	print_wall();//!上墙 
	print_food();//!上食物 
	print_snake();//!上蛇 
	locate(m + 2, 0);//!为了把它的那个记录你的蛇的长度的东西搞出来 
	cout << "Now length: ";
	/*** 开始游戏 ***/
	while (1)//!循环 
	{
		/*** 难度随长度增加而提高 ***/
		hard_len = (double)snake_length / (double)(m * n);//!这个就是前面讲的，snake_length原来是个int，他还除了个游戏框的面积，高，实在是高 
		/*** 调节时间，单位是ms ***/
		a = clock();//!a的值是运行时间了，这里是游戏开始的时间 
		while (1)
		{
			b = clock();//！b的值是当次循环开始的时间
			if (b - a >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len))) break;//!这个是为了调节每一次循环在这里停留的时间，它设定好了一些标准 
																			//!当你选择的难度所对应的时间到了，他才会继续下一步，就是为了达到调节难度的目的 
		}
		/*** 接受键盘输入的上下左右，并以此改变方向 ***/
		if (kbhit())//!等你敲键盘下才会运行if里的语句 
		{
			ch = getch();//!读一个你输入的上下左右 
			if (ch == -32)//!我一开始没看懂,查了一下，好像是在c++里上下左右在输入的时候，会在缓存区里生成两个字符，第一个字符的ASCii码就是 -32 
			{            //!他先用一个getch（）把第一个字符给清除了，再根据上下左右在缓存区的第二个字符的不同来区别。 
				ch = getch();
				switch (ch)//! 72表示上移 80表示 75表示左移 77表示右移 
				{          //! dir=0左 dir=1右 dir=2上 dir=3下 
				case 72://!ch=72时 ,上移 
					if (dir == 2 || dir == 3)//！假如dir≠2/3就表示 蛇原来在左右移，就不用改方向 
						dir = 0;             //! 反之，dir=2/3就表示，蛇原来在上下移，就得把dir改成0,表示向左走   后面类似 
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
		if (!go_ahead()) break;//!判断蛇有没有撞，撞了就游戏结束 
		/*** 在最后输出此时长度 ***/
		locate(m + 2, 12);
		cout << snake_length;
	}
	system("pause");
	return 0;
}
