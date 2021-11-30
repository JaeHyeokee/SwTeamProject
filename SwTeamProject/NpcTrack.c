#include "NpcTrack.h"


int getDistance(int x, int y) {
	return x * x + y * y;
}
void updateNpcPos(player* p, NPC* npc) {
	if (getArea(npc, p) > npc->detectArea) return; //Ư�� �����ȿ� ������ �� ���� ����
	if (npc->moveStyle == 0) { //���� ��� ������
		npc->directionCnt++;
		if (npc->directionCnt % 4 == 0) { //
			int tempX = 0, tempY = 0;
			tempX = p->x - npc->x;
			tempY = p->y - npc->y;
			if (tempX > 0)
				npc->dx = 1;
			else
				npc->dx = -1;


			if (tempY > 0)
				npc->dy = 1;
			else
				npc->dy = -1;

			if (npc->directionFlag == 0) {
				npc->directionFlag = 1;
				npc->dx = 0;
			}
			else {
				npc->directionFlag = 0;
				npc->dy = 0;
			}
		}
		else {
			npc->x += npc->dx;
			npc->y += npc->dy;

			if (npc->x >= stage1X - 1)
				npc->x--;
			if (npc->y <= 1)
				npc->y++;
		}
	}
	else if (npc->moveStyle == 1) {//���� ������

		if (npc->x < p->x) npc->dx = 1;
		else if (npc->x > p->x) npc->dx = -1;

		if (npc->y < p->y) npc->dy = 1;
		else if (npc->y > p->y) npc->dy = -1;

		npc->x += npc->dx;
		npc->y += npc->dy;
	}
}
void addNpcCnt(NPC *npc) {
	npc->cnt++;
}
void deleteNpc(NPC* npc, int stage[][60]) {
	int posX = OriginX + (npc->x * 2);
	int posY = OriginY + npc->y;
	SetCurrentCursorPos(posX, posY);
	recoverCloud(npc->x, npc->y, stage);
	SetCurrentCursorPos(posX, posY+1);
	recoverCloud(npc->x, npc->y+1, stage);
}

void drawNpc(NPC* npc) {
	int posX = OriginX + (npc->x * 2);
	int posY = OriginY + npc->y;
	SetCurrentCursorPos(posX, posY);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);	//�����
	SetCurrentCursorPos(posX, posY);
	printf("��");  //�ӽ� npc
	SetCurrentCursorPos(posX, posY+1);
	printf("��");  //�ӽ� npc
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// ���}
}

int getArea(NPC* npc, player* p) {
	int x  = npc->x - p->x;
	int y = npc->y - p->y;
	return x * y < 0 ? x * y * (-1) : x * y;
}

void initNPC(NPC* npcArr, int diff, int stageNum, int *npcNum)
//npc ���̵� ������ ���� ���̵��� �������� �ѹ� �Ű������� �޾ƿ��� 
//npcNum -> �ʿ��� ���ƴٴϴ� npc ����
{

	if (diff == E) {
		*npcNum = 2;
		if (stageNum == 0) {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
		else if (stageNum == 1) {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
		else {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
	}

	if (diff == H) {
		*npcNum = 2;
		if (stageNum == 0) {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
		else if (stageNum == 1) {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
		else {
			npcArr[0].homeX = 10; npcArr[0].homeY = 10;
			npcArr[1].homeX = 50; npcArr[1].homeY = 20;
		}
	}

	for (int i = 0; i < *npcNum; i++) {
		npcArr[i].x =npcArr[i].homeX;
		npcArr[i].y = npcArr[i].homeY;
		npcArr[i].haveBall = 1;

		npcArr[i].moveStyle = 0;
		npcArr[i].cnt = 0; //npc ������ �ֱ� ī��Ʈ�� ����
		npcArr[i].npcSpeed = 4; //npc ������ �ֱ�

		npcArr[i].dx = 1;
		npcArr[i].dy = 0;
		npcArr[i].directionCnt = 0;
		npcArr[i].directionFlag = 0;
		npcArr[i].detectArea = 40;
	}

	//�ӽ÷� �����ֱ� ���� ����
	npcArr[0].moveStyle = 1;
	npcArr[0].npcSpeed = 6;
}