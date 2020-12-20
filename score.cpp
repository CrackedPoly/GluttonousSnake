/***********************************************
*  Copyright ���ﶷ
*
*  @file     score.cpp
*  @brief    ��Ҫ������Ϸ��������Ⱦ������Ͷ�ȡ����
*  @author   ���󲩣��޼�
*  @date     2020/12/20
*
***********************************************/
#include "score.h"
#include "ui.h"
#include "stdio.h"

//���浱ǰ�����ı���
int currentScore = 0;
//������߷����ı���
int recordScore = 0;

/*
���õ�ǰ��Ϸ����
*/
void SetCurrentScore(int score) {
	currentScore = score;
}

/*
��ȡ��ǰ��Ϸ����
*/
int GetCurrentScore() {
	return currentScore;
}

/*
��ȡ�����Ϸ����
*/
int GetRecordScore() {
	return recordScore;
}

/*
�� record.txt �ļ��ж�ȡ�����Ϸ������¼
���ļ��������򴴽��ļ�
*/
void ReadRecordScore() {
	int score;
	FILE* recordFile = fopen("record/record.txt","r");
	if (!recordFile) {
		WriteRecordScore(0);
	}else {
		fscanf(recordFile, "%d", &recordScore);
	}
	fclose(recordFile); //�ر��ļ���ֹ�ڴ�й¶
}

/*
�� record.txt �ļ���д�������Ϸ������¼
*/
void WriteRecordScore(int score) {
	FILE* recordFile = fopen("record/record.txt", "w");
	fputs("0", recordFile);
	fflush(recordFile); //ˢ�»���
	fclose(recordFile); //�ر��ļ���ֹ�ڴ�й¶
}

/*
����Ϸ���ڵĲ������Ⱦ��Ϸ����
*/
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
	xyprintf(455, 175, "%d", currentScore);
	xyprintf(455, 284, "%d", recordScore > currentScore ? recordScore : currentScore);
}

/*
����Ϸ�����ı�ʱ��Ҫˢ����Ϸ����
*/
void RefreshScore() {
	//ò��û���ҵ�������ֵĺ������ɴา������
	PIMAGE mask = newimage();
	GetZoomImage(mask, "image/score_mask.png", 100, 35);
	putimage_withalpha(NULL, mask, 455, 175);
	putimage_withalpha(NULL, mask, 455, 284);
	delimage(mask);
	//���»��Ʒ���
	DrawScore();
}