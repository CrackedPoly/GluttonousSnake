#include "score.h"
#include "snake.h"
#include "ui.h"
#define SCREEN_SIZE 568

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

void DrawScore() {
	int currentScore = GetCurrentScore();
	int recordScore = GetRecordScore();
	// 设置输出效果为抗锯齿（LOGFONTA是MBCS版本，LOGFONTW是UTF16版本）
	LOGFONTA f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 35;                      // 设置字体高度为 48（包含行距）
	strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	f.lfWeight = FW_BLACK;
	setcolor(EGERGB(36,33,33));				      //文字的颜色
	setfont(&f);                          // 设置字体样式
	setbkmode(TRANSPARENT);               //设置文字背景为透明
	xyprintf(455, 175, "%03d",currentScore);
	xyprintf(455, 284, "%03d", recordScore > currentScore ? recordScore : currentScore);

}

void DrawSidebar() {
	int SIDEBAR_X = 378;
	int SIDEBAR_WIDTH = SCREEN_SIZE - SIDEBAR_X;
	int SIDEBAR_HEIGHT = SCREEN_SIZE;
	PIMAGE sidebar = newimage();
	GetZoomImage(sidebar, "image/sidebar.png",SIDEBAR_WIDTH,SIDEBAR_HEIGHT);
	putimage_withalpha(NULL, sidebar,SIDEBAR_X,0);
	DrawScore();
}

void GameOver() {
	int GAMEOVER_WIDTH = 378;
	int GAMEOVER_HEIGHT = SCREEN_SIZE;
	PIMAGE gameover = newimage();
	GetZoomImage(gameover, "image/gameover.png", GAMEOVER_WIDTH, GAMEOVER_HEIGHT);
	putimage_withalpha(NULL, gameover, 0, 0);
}

/*
主函数，主要负责生成游戏窗口
*/
int main(){
	while (TRUE) {
		InitWindow();
		DrawMenu();
		getch();
		cleardevice();
		InitWindow();
		DrawMap();
		DrawSidebar();
		GameStart();
		GameOver();
		getch();
	}
	return 0;
}