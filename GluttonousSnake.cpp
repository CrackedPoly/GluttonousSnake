/***********************************************
*  Copyright 窝里斗
*
*  @file     GluttonousSnake.cpp
*  @brief    程序运行的入口点，主要负责程序整体流程控制及窗口渲染工作
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/
#include "score.h" //主要与游戏分数有关
#include "snake.h" //主要与游戏流程有关
#include "ui.h" //包装过后的图形库
#define SCREEN_SIZE 568 //窗口的大小 568 * 568

/*
初始化窗口，绑定背景图片
并修改窗口标题
*/
void InitWindow() {
	initgraph(SCREEN_SIZE, SCREEN_SIZE, 0); // 初始化，显示一个窗口
	setbkcolor(WHITE);
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
	delimage(background); //销毁图片，防止内存泄漏
}

/*
渲染菜单页面，包括：
- 标题 GluttonousSnake
- 作者 刘轶博 & 罗鉴
- Logo
- 开始提示
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

/*
渲染游戏地图的边界
地图的大小（不包含边界）：
- 宽 18 个格子
- 高 28 个格子
*/
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

/*
渲染侧边栏，侧边栏内容包括：
- 当前分数
- 最高分
- 游戏规则
*/
void DrawSidebar() {
	int SIDEBAR_X = 378;
	int SIDEBAR_WIDTH = SCREEN_SIZE - SIDEBAR_X;
	int SIDEBAR_HEIGHT = SCREEN_SIZE;
	PIMAGE sidebar = newimage();
	GetZoomImage(sidebar, "image/sidebar.png",SIDEBAR_WIDTH,SIDEBAR_HEIGHT);
	putimage_withalpha(NULL, sidebar,SIDEBAR_X,0);
	ReadRecordScore(); //从文件中读取最高分记录
	DrawScore();
}

/*
当游戏结束后，负责渲染游戏结束页面
如果玩家当前分数超过了最高分，还需保存最高分记录
*/
void GameOver() {
	int GAMEOVER_WIDTH = 378;
	int GAMEOVER_HEIGHT = SCREEN_SIZE;
	PIMAGE gameover = newimage();
	GetZoomImage(gameover, "image/gameover.png", GAMEOVER_WIDTH, GAMEOVER_HEIGHT);
	putimage_withalpha(NULL, gameover, 0, 0);
	if (GetCurrentScore() > GetRecordScore()) {
		WriteRecordScore(GetCurrentScore());
	}
}

/*
程序主函数
主要负责：
- 生成主菜单
- 生成游戏界面
- 生成结束界面并处理游戏结果
*/
int main(){
	while (TRUE) {
		InitWindow(); //初始化窗口
		DrawMenu(); //渲染菜单
		getch(); //等待用户按键
		cleardevice(); //清屏
		InitWindow(); //再次初始化窗口
		DrawMap(); //渲染地图
		DrawSidebar(); //渲染侧边栏
		GameStart(); //进入游戏，开始执行游戏流程
		GameOver(); //游戏结束
		getch(); //等待用户按键，按键后返回主菜单
	}
	return 0;
}