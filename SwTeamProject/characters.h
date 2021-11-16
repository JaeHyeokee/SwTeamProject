#pragma once

typedef struct Player
{
	int x, y; //y�� player�� �Ӹ� ��ǥ
	int life;
	int totalBalls;
	int balls;
	int stageNum;
	int targetBall[3];
}player;

typedef struct NPC
{
	int x, y;
	int homeX, homeY;
	int haveBall;
	int distance[8];   //8���� ����
	int minDistance;  //ĳ���Ϳ��� �ּҰŸ�
	int cnt;
	int npcSpeed;
}NPC;

