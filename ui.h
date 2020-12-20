/***********************************************
*  Copyright 窝里斗
*
*  @file     ui.h
*  @brief    对原图型库的函数进行封装
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/

#ifndef _UI_H_ //防止重复导入头文件
#define _UI_H_
#include "graphics.h" //导入ege图形库

/*
从图片文件fileName 中加载图像，图像拉伸成 width * height
*/
void GetZoomImage(PIMAGE pimg, const char* fileName, int width, int height);

#endif