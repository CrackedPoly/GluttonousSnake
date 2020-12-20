/***********************************************
*  Copyright 窝里斗
*
*  @file     ui.cpp
*  @brief    实现了GetZoomImage，读取图片并拉伸到指定大小
*  @author   刘轶博，罗鉴
*  @date     2020/12/20
*
***********************************************/
#include "ui.h"

/*
从图片文件fileName 中加载图像，图像拉伸成 width * height
*/
void GetZoomImage(PIMAGE pimg, const char* fileName, int width, int height) {
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	if ((getwidth(pimg) != width) || (getheight(pimg) != height)) {
		resize(pimg, width, height);
	}
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
	delimage(temp);
}