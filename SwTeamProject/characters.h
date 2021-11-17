#pragma once

typedef struct Player
{
	int x, y;
	int life;
	int totalBalls;
	int balls;
	int stageNum;
}player;

typedef struct NPC
{
	int x, y;
	int homeX, homeY;
	int haveBall;
	int distance[8];   //8���� ����
	int minDistance;  //ĳ���Ϳ��� �ּҰŸ�
}NPC;