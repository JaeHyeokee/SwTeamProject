#pragma once
#include <Windows.h>
#include <stdio.h>
#include "characters.h"
#include "cursor.h"
#define OriginX 5
#define OriginY 10
#define JUMPHEIGHT -7

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


void drawSpecialCloud(cloud* cloud, int stage[][60]);


void deleteSpecialCloud(cloud* cloud, int stage[][60]);


void initSpecialCloud(cloud* cloudArray, int size);


int collSpecialCloud(cloud* cloudArr, player* p, int stage[][60]);


void moveCloud(cloud* cloudArr, int stage[][60]);

