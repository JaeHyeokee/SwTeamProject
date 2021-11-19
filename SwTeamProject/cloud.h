#pragma once
#include <Windows.h>
#include <stdio.h>

#include "Common.h"
#include "characters.h"


typedef struct SPECIALCLOUD
{
	int movement;				//���� ������
	int cloudType;				//3 => ��������, 5 => ���� ����, 7 = ���� ����, 11 => ���ڱ���
	int size;					//���� ũ��
	int x, y;
	int vis;
}cloud;


int jumpHigh(int height);

void blink(int* cloudVis);

void vanishCloud(int* cloudVis);

int cloudColl(int x, int y, int size, int stage[][60]);

void printJumpCloud();

void printWeakCloud();

void printBlinkCloud();

void printNormalCloud();

void printTrapCloud();

void recoverCloud(int x, int y, int stage[][60]);

void initSpecialCloud(cloud* cloudArray, int size)
{
	int i;
	int temp;
	for (i = 0; i < size; i++)
	{
		temp = rand() % 4;
		if (temp == 0)
			cloudArray[i].cloudType = 3;		//���� ����
		else if (temp == 1)
			cloudArray[i].cloudType = 5;		//1ȸ�� ����
		else if (temp == 2)
			cloudArray[i].cloudType = 7;		//���� ����
		else if (temp == 3)
			cloudArray[i].cloudType = 11;		//���� ����

void drawSpecialCloud(cloud* cloud, int stage[][60]);

		cloudArray[i].movement = rand() % 5 - 3;		//0 ����, 1 �¿� 2 ���� (+- ����)
		cloudArray[i].size = rand() % 5 + 3;

void deleteSpecialCloud(cloud* cloud, int stage[][60]);

	return;
}

void initSpecialCloud(cloud* cloudArray, int size);

	for (i = 0; i < 5; i++)
	{
		int xS = cloudArr[i].x;
		int xE = cloudArr[i].x + cloudArr[i].size;
		int y = cloudArr[i].y;
		if (xS <= p->x && xE >= p->x && y == p->y + 3)
		{
			if (cloudArr[i].cloudType == 3)
				return jumpHigh(JUMPHEIGHT);
			else if (cloudArr[i].cloudType == 5)
			{
				vanishCloud(&(cloudArr[i].vis));
				return JUMPHEIGHT;
			}
		}
	}
	return JUMPHEIGHT;
}

int collSpecialCloud(cloud* cloudArr, player* p, int stage[][60]);

	if (cloudArr->cloudType == 7)
	{
		if (blinkCount % 2 == 0)
			blink(&(cloudArr->vis));
	}
	blinkCount++;

void moveCloud(cloud* cloudArr, int stage[][60]);

