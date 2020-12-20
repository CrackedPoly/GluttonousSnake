#ifndef _UI_H_
#define _UI_H_
#include "graphics.h" //导入图形库

//从图片文件fileName 中加载图像，图像缩放成 width * height
void GetZoomImage(PIMAGE pimg, const char* fileName, int width, int height) {
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	if ((getwidth(pimg) != width) || (getheight(pimg) != height)) {
		resize(pimg, width, height);
	}
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
	delimage(temp);
}

#endif