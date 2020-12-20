#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>//! 为了用函数time() 
#include <cmath>
#include <windows.h>//!这个就是为了用句柄 和一个cls（）清屏的函数 
#include "ui.h"

#define SCREEN_SIZE 569
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


/*
初始化窗口
*/
void InitWindow() {
	initgraph(SCREEN_SIZE, SCREEN_SIZE, 0); // 初始化，显示一个窗口
	setcaption(L"Gluttonous Snake Version 1.0"); // 设置窗口标题
	PIMAGE background = newimage(600, 600);
	getimage(background, "image/background.png");
	//对目标图像（这里是窗口）开启透明，这是必须的
	ege_enable_aa(true);
	//将图片生成纹理
	ege_gentexture(true, background);
	//对图片设置透明度
	ege_setalpha(0xFF, background);
	//缩放绘制纹理图到窗口上
	ege_puttexture(background, ege_rect{ 0, 0, SCREEN_SIZE, SCREEN_SIZE }, ege_rect{ 0, 0, SCREEN_SIZE, SCREEN_SIZE });
	delimage(background);
}

/*
初始化菜单页面
*/
void DrawMenu() {
	int TITLE_WIDTH = 520,TITLE_HEIGHT = 119;
	PIMAGE title = newimage();
	GetZoomImage(title, "image/title.png", 520, 119);
	putimage_withalpha(NULL, title, (SCREEN_SIZE - TITLE_WIDTH) / 2, 30);
	delimage(title);
	int LOGO_WIDTH = 200, LOGO_HEIGHT = 200;
	PIMAGE logo = newimage();
	GetZoomImage(logo, "image/logo.png", LOGO_WIDTH, LOGO_HEIGHT);
	putimage_withalpha(NULL, logo, (SCREEN_SIZE - LOGO_WIDTH) / 2, 180);
	delimage(logo);
	int START_WIDTH = 485, START_HEIGHT = 103;
	PIMAGE start = newimage();
	GetZoomImage(start, "image/start.png", START_WIDTH, START_HEIGHT);
	putimage_withalpha(NULL, start, (SCREEN_SIZE - START_WIDTH) / 2, 400);
	delimage(start);
}

void DrawMap() {
	int WALL_SIZE = 17;
	int GAP_SIZE = 2;
	int MAP_ROW = 30, MAP_COLUMN = 20;
	PIMAGE wall = newimage();
	GetZoomImage(wall, "image/wall.png",WALL_SIZE,WALL_SIZE);
	for (int i = 0; i < MAP_ROW; i++) {
		int x = (MAP_COLUMN - 1) * (WALL_SIZE + GAP_SIZE);
		int y = i * (WALL_SIZE + GAP_SIZE);
		putimage_withalpha(NULL, wall, 0, y);
		putimage_withalpha(NULL, wall, x, y);
	}
	for (int i = 0; i < MAP_COLUMN; i++) {
		int x = i * (WALL_SIZE + GAP_SIZE);
		int y = (MAP_ROW - 1) * (WALL_SIZE + GAP_SIZE);
		putimage_withalpha(NULL, wall, x, 0);
		putimage_withalpha(NULL, wall, x, y);
	}
	delimage(wall);
}

void DrawSidebar() {
	
}

/*
主函数，主要负责生成游戏窗口
*/
int main(){
	InitWindow();
	DrawMenu();
	getch();
	cleardevice();
	InitWindow();
	DrawMap();
	DrawSidebar();
	while (TRUE) {
		char move = getch();
		if(move == 'w' || move == 'W'){
			
		}
	}
	return 0;
}