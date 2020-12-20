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
	// �������Ч��Ϊ����ݣ�LOGFONTA��MBCS�汾��LOGFONTW��UTF16�汾��
	LOGFONTA f;
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight = 35;                      // ��������߶�Ϊ 48�������оࣩ
	strcpy(f.lfFaceName, "����");         // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	f.lfWeight = FW_BLACK;
	setcolor(EGERGB(36, 33, 33));				      //���ֵ���ɫ
	setfont(&f);                          // ����������ʽ
	setbkmode(TRANSPARENT);               //�������ֱ���Ϊ͸��
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