#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "characters.h"
#include "cursor.h"
#include "stage.h"
#include "DragonBall.h"
#include "Track.h"



#define LEFT 75
#define RIGHT 77
#define JUMPHEIGHT -7


//�ʱ� ȭ�� ����
void initCmd()
{
	RemoveCursor();
	system("mode con cols=200 lines=50");
}


void initPlayer(player* p)
{
	p->x = 56;
	p->y = 32;
	p->life = 10;
	p->totalBalls = 0;
	p->balls = 0;
	p->stageNum = 0;
	p->targetBall[0] = 2;
	p->targetBall[1] = 3;
	p->targetBall[2] = 3;
}

void initNPC(NPC* npc, int posX, int posY)
{
	npc->homeX = 1;
	npc->homeY = 1;
	npc->x = npc->homeX;
	npc->y = npc->homeY;
	npc->haveBall = 1;

	npc->cnt = 0; //npc ������ �ֱ� ī��Ʈ�� ����
	npc->npcSpeed = 7; //npc ������ �ֱ�
}


//�� �׵θ� �׷��ֱ�
void printStage()
{
	int i;

	//��,�Ʒ� - 58
	for (i = 1; i < stage1X - 1; i++)
	{
		SetCurrentCursorPos(OriginX + (i * 2), OriginY);
		printf("��");
		SetCurrentCursorPos(OriginX + (i * 2), stage1Y + OriginY - 1);
		printf("��");
	}

	//��
	for (i = 0; i < stage1Y; i++)
	{
		if (i == 0)
		{
			SetCurrentCursorPos(OriginX, i + OriginY);
			printf("��");
			SetCurrentCursorPos(OriginX + (stage1X - 1) * 2, i + OriginY);
			printf("��");
		}
		else if (i == stage1Y - 1)
		{
			SetCurrentCursorPos(OriginX, i + OriginY);
			printf("��");
			SetCurrentCursorPos(OriginX + (stage1X - 1) * 2, i + OriginY);
			printf("��");
		}
		else
		{
			SetCurrentCursorPos(OriginX, i + OriginY);
			printf("��");
			SetCurrentCursorPos(OriginX + (stage1X - 1) * 2, i + OriginY);
			printf("��");
		}
	}
}


//�� ���� �׸���
void printCloud(int stage[40][60], DragonBall dgb[])
{
	//�� �׸��� ���� ���� �ѹ� �ʱ�ȭ �����ֱ�
	//���� �������� �̵��� �ʿ�
	int i, j;
	int curX, curY;
	for (i = 1; i < stage1Y - 1; i++)
	{
		for (j = 1; j < stage1X - 1; j++)
		{
			curX = j * 2 + OriginX;
			curY = i + OriginY;
			SetCurrentCursorPos(curX, curY);
			printf("  ");
		}
	}

	//���� �׷��ֱ�
	for (i = 1; i < stage1Y - 1; i++)
	{
		for (j = 1; j < stage1X - 1; j++)
		{
			curX = j * 2 + OriginX;
			curY = i + OriginY;
			SetCurrentCursorPos(curX, curY);
			if (stage[i][j] == 2)
				printf("��");
		}
	}

	//�巡�ﺼ �׷��ֱ�
	for (int i = 0; i < 3; i++) {
		curX = dgb[i].x * 2 + OriginX;
		curY = dgb[i].y + OriginY;
		SetCurrentCursorPos(curX, curY);
		printf("��");
	}
}

void drawPlayer(player* p)
{
	/*if (p->y < 0)
		p->y = 0;*/
	int posX = OriginX + (p->x * 2);
	int posY = OriginY + p->y;
	SetCurrentCursorPos(posX, posY++);
	printf("��");
	SetCurrentCursorPos(posX, posY++);
	printf("��");
	SetCurrentCursorPos(posX, posY);
	printf("��");
}

void deletePlayer(player* p, int stage[][60])
{
	int posX = OriginX + (p->x * 2);
	int posY = OriginY + p->y;

	SetCurrentCursorPos(posX, posY++);								//�ش� �κ� �ٽ� �ʰ� ���ؼ� ����
	if (stageArr[p->stageNum][p->y][p->x] == 0)
		printf("  "); 
	else if (stageArr[p->stageNum][p->y][p->x] % 2 == 0) //���� ����
		printf("��");
	else if (stageArr[p->stageNum][p->y][p->x] % 3 == 0) //�������� ��Ż ����
		printf("��");

	SetCurrentCursorPos(posX, posY++);
	if (stageArr[p->stageNum][p->y + 1][p->x] == 0)
		printf("  ");
	else if (stageArr[p->stageNum][p->y + 1][p->x] % 2 == 0)
		printf("��");
	else if (stageArr[p->stageNum][p->y + 1][p->x] % 3 == 0)
		printf("��");

	SetCurrentCursorPos(posX, posY);
	if (stageArr[p->stageNum][p->y + 2][p->x] == 0)
		printf("  ");
	else if (stageArr[p->stageNum][p->y + 2][p->x] % 2 == 0)
		printf("��");
	else if (stageArr[p->stageNum][p->y + 2][p->x] % 3 == 0)
		printf("��");
	
}

void UpdateRecord(player* p)
{
	int curX = 135;
	int curY = 20;
	int i;
	SetCurrentCursorPos(curX, curY++);
	printf("���� ��������: %d", p->stageNum);

	SetCurrentCursorPos(curX, curY++);
	printf("���� ���: ");
	COORD pos = GetCurrentCursorPos(); //��Ʈ�� �ٽ� �׸��� ���� ��ġ ���
	for (int i = 0; i < 10; i++) //���� ��Ʈ �����
		printf("  ");
	SetCurrentCursorPos(pos.X, pos.Y);
	for (i = 0; i < p->life; i++) //���� ��Ʈ �׸���.
		printf("��");


	SetCurrentCursorPos(curX, curY++);
	printf("���� �巡�� �� �� ����: %d", p->totalBalls);
	SetCurrentCursorPos(curX, curY++);
	printf("�̹� ������������ ���� �� ����: %d", p->balls);
	SetCurrentCursorPos(curX, curY++);
	printf("�¿� �̵� <- -> ����Ű");
}

int detectColl(int x, int y, int stage[][60])
{
	if (y < 0) y = 0;
	if (stage[y][x] == -1 || stage[y + 1][x] == -1 || stage[y + 2][x] == -1) //�ٴڿ� �߶�
		return -1;
	else if (stage[y][x] == 0 && stage[y + 1][x] == 0 && stage[y + 2][x] == 0) //���ع� x
		return 0;
	else if (stage[y][x] == 2 || stage[y + 1][x] == 2 || stage[y + 2][x] == 2) //������ ������ ����
		return 1;
	else if (stage[y][x] == 1 || stage[y + 1][x] == 1 || stage[y + 2][x] == 1) //���� �浹
		return 2;
}

int jumpColl(int x, int y, int stage[][60])
{
	if (stage[y][x] != 0) //���� ����
		return 3;
	if (stage[y + 1][x] != 0) //���� ����
		return 2;
	if (stage[y + 2][x] != 0) //�Ӹ��� ����
		return 1;
	return 0;
}

int JumpVector(int y)
{
	//�������� ������ y��ǥ�� �۾�����, �ö󰡴� ��Ȳ�� ���ʹ� ����
	float temp = -(2.0 / 5.0);
	return temp * y;
}

int playerJump(player* p, int* jump, int stage[][60])
{
	//ĳ���Ͱ� ���� ������ �� ������ �� �ְ� ���ִ� ����
	static int flag = 0;

	int moveY = JumpVector(*jump);
	(*jump)++;
	if (moveY > 2)
		moveY = 2;
	else if (moveY < -2)
		moveY = -2;

	int coll = detectColl(p->x, p->y - moveY, stage);

	//õ�忡 �ε����� �ܿ�
	if (coll == 2)
	{
		*jump = -(*jump);
		moveY = -moveY;
		coll = detectColl(p->x, p->y - moveY, stage);
	}

	Sleep(50);  //�� ���ۿ� ���� ����
	if (moveY < 0 && coll == 1 && flag <= 0)		// ���� ���� �� �ִ� ���� -> col == 1�� ������ ���� ������ ���� �������� �����ִ� ��Ȳ�̱� ����
	{
		moveY = -1;
		int temp = detectColl(p->x, p->y - moveY, stage); //��ĭ ���� �̵����� ��쿡�� detectColl ����
		if (temp == 0) //���� ���� �� �ִ� ���¶��
		{
			//ĳ���� �÷��ֱ�
			deletePlayer(p, stage);
			p->y -= moveY;
			drawPlayer(p);
		}
		return 1;
	}
	else if (coll == 0 || (coll != 2 && moveY >= 0) || flag > 0)	//�Ϲ����� ���� or ������ �� �ִ� ���
	{
		deletePlayer(p, stage);
		p->y -= moveY;
		drawPlayer(p);

		flag--; //flag ���� 0���ϰ� �� ������ �� ���ǿ� ������. -> flag���� ����� ���� ������ �����ִ� ����. 

		if (coll != 0 && moveY == 0) //������ �� �ִ� ��Ȳ
			flag = jumpColl(p->x, p->y, stage);

		return 0;
	}
	else if (coll == -1)
		return -1;
	else 
		return 1;
}

void moveLeft(player* p, int stage[][60])
{
	if (detectColl(p->x - 1, p->y, stage) != 2)
	{
		deletePlayer(p,stage);
		p->x -= 1;
		drawPlayer(p);
	}
}

void moveRight(player* p, int stage[][60])
{
	if (detectColl(p->x + 1, p->y, stage) != 2)
	{
		deletePlayer(p,stage);
		p->x += 1;
		drawPlayer(p);
	}
}


void processKeyInput(player* p, int stage[][60])
{
	int i, key;

	for (i = 0; i < 5; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();
			switch (key)
			{
			case LEFT:
				moveLeft(p, stage);
				break;
			case RIGHT:
				moveRight(p, stage);
				break;
			}
		}
	}
}

void respawnPlayer(player* p, int stage[][60])
{
	deletePlayer(p, stage);
	p->x = 56;
	p->y = 32;
	p->life--;
}

int isGameOver(player* p)
{
	if (p->life <= 0)
		return 1;
	return 0;
}

int distance(int x, int y)   //ĳ���Ϳ� npc�Ÿ� �� ��
{
	return x * x + y * y;
}

//���� �˰��� ��� ����
void deleteNpc(NPC *npc, int stageNum) {
	int posX = OriginX + (npc->x * 2);
	int posY = OriginY + npc->y;
	SetCurrentCursorPos(posX, posY);

	if (stageArr[stageNum][npc->y][npc->x] == 2)
		printf("��");
	else printf("  ");
}
void drawNpc(NPC *npc) {
	int posX = OriginX + (npc->x * 2);
	int posY = OriginY + npc->y;
	SetCurrentCursorPos(posX, posY);
	printf("��");  //�ӽ� npc
}


//�������� �̵� ���� �Լ��� - ����� �ؾ� �ϱ� ������ ���� ���� ����� x
void setStageDoor(StageDoor* std) {
	std[0].x = 46; std[0].y = 4;
	stageArr[0][std[0].y][std[0].x] = 3;

	std[1].x = 46; std[1].y = 4;
	stageArr[1][std[1].y][std[1].x] = 3;

	std[2].x = 46; std[2].y = 4;
	stageArr[2][std[2].y][std[2].x] = 3;
}
void printStageDoor(StageDoor* std, int stage[][60], int stageNum) {
	int posX = std[stageNum].x * 2 + OriginX;
	int posY = std[stageNum].y + OriginY;
	SetCurrentCursorPos(posX, posY);
	printf("��");
}
void gotoNextStage(player* p, DragonBall dgball[][3], StageDoor *std) {
	p->stageNum++;
	printStage();
	printCloud(stageArr[p->stageNum], dgball[p->stageNum]);
	
	p->life++; //respawnPlayer���� life�� ��ĭ �����Ƿ� �̸� �߰��صα�
	respawnPlayer(p, stageArr[p->stageNum]); //deletePlayer �Լ� ���� ���� ������Ű�Ƿ� ���� �������� printStageDoor ����ؾ���
	printStageDoor(std, stageArr[p->stageNum], p->stageNum);

	p->balls = 0;
	UpdateRecord(p);
}
int checkStageDoor(player* p, StageDoor *std, int stageNum) {
	if(p->balls == p->targetBall[p->stageNum] && p->x == std[stageNum].x && p->y+2 == std[stageNum].y)
		return 1;
	else
		return 0;
}



int main()
{
	player p;
	NPC npc;
	DragonBall dgb[7];
	DragonBall dgball[3][3];
	StageDoor stageDoor[3];
	 

	npc.x = 1, npc.y = 1;     //�⺻ ��
	int jump = JUMPHEIGHT;
	int gameFlag = 1;
	int jumpFlag = 0;
	int posX, posY;
	int count = 0;

	//settings
	initCmd();
	initNPC(&npc, 1, 1);
	initPlayer(&p);
	setDragonBallPos(dgball);
	setStageDoor(stageDoor);

	//initial printing
	printStage();
	printCloud(stageArr[p.stageNum], dgball[p.stageNum]);
	drawPlayer(&p);
	printStageDoor(stageDoor, stageArr[p.stageNum], p.stageNum);
	UpdateRecord(&p);


	while (1)
	{	
		if (isGameOver(&p))
			break;

		jumpFlag = playerJump(&p, &jump, stageArr[p.stageNum]);
		count++;


		if (jumpFlag == 1) //
			jump = JUMPHEIGHT;
		else if (jumpFlag == -1) //�߶��� ���
		{
			//npc �������ְ� ��ġ �缳��
			deleteNpc(&npc, p.stageNum);
			npc.x = 1; npc.y = 1;

			//�÷��̾� ���� and ��ġ �缳�� and ��Ϻ���
			respawnPlayer(&p, stageArr[p.stageNum]);
			UpdateRecord(&p);
		}

		//�巡�ﺼ and �������� ���� Ȯ��
		if (dragonBallGet(&p, dgball[p.stageNum]) == 1) //�巡�ﺼ ��ġ�� �÷��̾� ��ġ �� �� ���� ������Ʈ
			UpdateRecord(&p);
		if (checkStageDoor(&p, stageDoor, p.stageNum)) { //�巡�ﺼ ���� ������ and �� �տ� �� ������ ���� ���������� �̵�
			gotoNextStage(&p, dgball, stageDoor);
		}

		processKeyInput(&p, stageArr[p.stageNum]);
	}

	SetCurrentCursorPos(0, 0);
	
	printf("GameOver");

	getchar();

	return 0;
}