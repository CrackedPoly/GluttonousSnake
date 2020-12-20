/***********************************************
*  Copyright 窝里斗
*
*  @file     score.cpp
*  @brief    主要负责游戏分数的渲染、保存和读取工作
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/
#include "score.h"
#include "ui.h"
#include "stdio.h"

//保存当前分数的变量
int currentScore = 0;
//保存最高分数的变量
int recordScore = 0;

/*
设置当前游戏分数
*/
void SetCurrentScore(int score) {
	currentScore = score;
}

/*
获取当前游戏分数
*/
int GetCurrentScore() {
	return currentScore;
}

/*
获取最高游戏分数
*/
int GetRecordScore() {
	return recordScore;
}

/*
从 record.txt 文件中读取最高游戏分数记录
若文件不存在则创建文件
*/
void ReadRecordScore() {
	int score;
	FILE* recordFile = fopen("record/record.txt","r");
	if (!recordFile) {
		WriteRecordScore(0);
	}else {
		fscanf(recordFile, "%d", &recordScore);
	}
	fclose(recordFile); //关闭文件防止内存泄露
}

/*
向 record.txt 文件中写入最高游戏分数记录
*/
void WriteRecordScore(int score) {
	FILE* recordFile = fopen("record/record.txt", "w");
	fputs("0", recordFile);
	fflush(recordFile); //刷新缓存
	fclose(recordFile); //关闭文件防止内存泄露
}

/*
向游戏窗口的侧边栏渲染游戏分数
*/
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
	setcolor(EGERGB(36, 33, 33));				      //文字的颜色
	setfont(&f);                          // 设置字体样式
	setbkmode(TRANSPARENT);               //设置文字背景为透明
	xyprintf(455, 175, "%d", currentScore);
	xyprintf(455, 284, "%d", recordScore > currentScore ? recordScore : currentScore);
}

/*
当游戏分数改变时需要刷新游戏分数
*/
void RefreshScore() {
	//貌似没有找到清除文字的函数，干脆覆盖算了
	PIMAGE mask = newimage();
	GetZoomImage(mask, "image/score_mask.png", 100, 35);
	putimage_withalpha(NULL, mask, 455, 175);
	putimage_withalpha(NULL, mask, 455, 284);
	delimage(mask);
	//重新绘制分数
	DrawScore();
}