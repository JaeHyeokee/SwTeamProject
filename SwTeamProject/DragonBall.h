#pragma once
#include "characters.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
//�������� �󿡼� �ѹ� 5�� ǥ��
typedef struct DragonBall {
	//�巡�ﺼ�� ��ġ ��ǥ
	int x, y;
	//�÷��̾��� �巡�ﺼ ���� ����
	int get;
}DragonBall;

void setDragonBallPos(DragonBall *dgb);
int dragonBallGet(player* p, DragonBall* dgb);
/*void checkDragonBall(void);
void stageCheck(void);
void gotoNextStage(void)*/;