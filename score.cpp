#include "score.h"
#include "ui.h"

int currentScore = 0;

void SetCurrentScore(int score) {
	currentScore = score;
}

int GetCurrentScore() {
	return currentScore;
}

int GetRecordScore() {
	return 100;
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
	setcolor(EGERGB(36, 33, 33));				      //文字的颜色
	setfont(&f);                          // 设置字体样式
	setbkmode(TRANSPARENT);               //设置文字背景为透明
	xyprintf(455, 175, "%03d", currentScore);
	xyprintf(455, 284, "%03d", recordScore > currentScore ? recordScore : currentScore);
}

void RefreshScore() {
	PIMAGE mask = newimage();
	GetZoomImage(mask, "image/score_mask.png", 100, 35);
	putimage_withalpha(NULL, mask, 455, 175);
	putimage_withalpha(NULL, mask, 455, 284);
	delimage(mask);
	DrawScore();
}