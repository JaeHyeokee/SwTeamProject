#pragma once

typedef struct Player
{
	int x, y; //y�� player�� �Ӹ� ��ǥ
	int life;
	int totalBalls;
	int balls;
	int stageNum;
	int targetBall[3];

	int spawnPos[3][2]; //3�������� (x,y)��ǥ - > 3*2 �迭
}player;

typedef struct NPC
{
	int x, y;
	int dx, dy;
	int homeX, homeY;
	int haveBall;

	int distance[8];   //8���� ����
	int minDistance;  //ĳ���Ϳ��� �ּҰŸ�
	int cnt; //npc while�� �ȿ��� �����̴� �ֱ�
	int directionCnt; //npc ���� �ٲٴ� �ֱ�
	int directionFlag;
	int npcSpeed;
	int detectArea;
}NPC;

