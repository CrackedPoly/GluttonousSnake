#ifndef _UI_H_
#define _UI_H_
#include "graphics.h" //����ͼ�ο�

//��ͼƬ�ļ�fileName �м���ͼ��ͼ�����ų� width * height
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