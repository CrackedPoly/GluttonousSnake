#include "ui.h"

void GetZoomImage(PIMAGE pimg, const char* fileName, int width, int height) {
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	if ((getwidth(pimg) != width) || (getheight(pimg) != height)) {
		resize(pimg, width, height);
	}
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
	delimage(temp);
}