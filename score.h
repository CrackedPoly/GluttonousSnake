/***********************************************
*  Copyright ���ﶷ
*
*  @file     score.h
*  @brief    ������һЩ��Ϸ��������Ⱦ������Ͷ�ȡ�ĺ���
*  @author   ���󲩣��޼�
*  @date     2020/12/20
*
***********************************************/

/*
���õ�ǰ��Ϸ����
*/
void SetCurrentScore(int score);

/*
��ȡ��ǰ��Ϸ����
*/
int GetCurrentScore();

/*
��ȡ�����Ϸ����
*/
int GetRecordScore();

/*
����Ϸ�����ı�ʱ��Ҫˢ����Ϸ����
*/
void RefreshScore();

/*
����Ϸ���ڵĲ������Ⱦ��Ϸ����
*/
void DrawScore();

/*
���ļ���д�������Ϸ������¼
*/
void WriteRecordScore(int score);

/*
���ļ��ж�ȡ�����Ϸ������¼
*/
void ReadRecordScore();