#pragma once
#define JUMPHEIGHT -7

typedef struct SPECIALCLOUD
{
	int movement;				//���� ������
	int cloudType;				//3 => ��������, 5 => ���� ����, 7 = ���� ����, 11 => ���ڱ���
	int size;					//���� ũ��
	int x, y;
	int vis;
}cloud;


int jumpHigh(int height)
{
	return (int)(height * 1.5);
}

void blink(int* cloudVis)
{
	if (*cloudVis == 0)
		*cloudVis = 1;
	else
		*cloudVis = 0;
}
void vanishCloud(int* cloudVis)
{
	blink(cloudVis);
}

int cloudColl(int x, int y, int size, int stage[][60])
{
	if (x <= 1 || x + size >= 59 || y <= 1 || y >= 39)
		return 1;
	else
		return 0;
}

void printJumpCloud()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //3 ����
	printf("��");
}

void printWeakCloud()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);		//10 ���� �ʷ�
	printf("��");
}

void printBlinkCloud()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);	//8 ȸ��
	printf("��");
}

void printNormalCloud()
{
	printf("��");
}

void printTrapCloud()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 12 ���� ����
	printf("��");
}

void recoverCloud(int x, int y, int stage[][60]);


void drawSpecialCloud(cloud* cloud, int stage[][60]);


void deleteSpecialCloud(cloud* cloud, int stage[][60]);


void initSpecialCloud(cloud* cloudArray, int size);


int collSpecialCloud(cloud* cloudArr, player* p, int stage[][60]);


void moveCloud(cloud* cloudArr, int stage[][60]);

