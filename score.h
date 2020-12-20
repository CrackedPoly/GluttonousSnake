/***********************************************
*  Copyright 窝里斗
*
*  @file     score.h
*  @brief    定义了一些游戏分数的渲染、保存和读取的函数
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/

/*
设置当前游戏分数
*/
void SetCurrentScore(int score);

/*
获取当前游戏分数
*/
int GetCurrentScore();

/*
获取最高游戏分数
*/
int GetRecordScore();

/*
当游戏分数改变时需要刷新游戏分数
*/
void RefreshScore();

/*
向游戏窗口的侧边栏渲染游戏分数
*/
void DrawScore();

/*
向文件中写入最高游戏分数记录
*/
void WriteRecordScore(int score);

/*
从文件中读取最高游戏分数记录
*/
void ReadRecordScore();