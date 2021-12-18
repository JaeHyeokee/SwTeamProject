#include "Common.h"

#include "StageArr.h"
#include "DragonBall.h"
#include "NpcTrack.h"
#include "NextStage.h"
#include "StartScreen.h"
#include "cloud.h"
#include "Item.h"

void gameStart(void);

int main()
{
	int tmpStageArr[3][40][60];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 40; j++)
			for (int k = 0; k < 60; k++)
				tmpStageArr[i][j][k] = stageArr[i][j][k];
	initCmd();
	while (1) {
		system("cls");
		//?�작?�면 
		gameStart();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 40; j++)
				for (int k = 0; k < 60; k++)
					stageArr[i][j][k] = tmpStageArr[i][j][k];
	}

	return 0;
}

void gameStart(void) {
	initCmd();
	//?�작?�면 
	int difficulty = printStartScreen();
	player p;
	DragonBall dgball[3][3];
	StageDoor stageDoor[3];
	cloud sCloud[5];

	NPC *npcArr;
	npcArr = (NPC*)malloc(sizeof(NPC) * 3);
	int npcNum = 1;

	srand((unsigned int)time(NULL));

	int jump = JUMPHEIGHT;
	int gameFlag = 1;
	int jumpFlag = 0;
	int count = 0;

	initPlayer(&p);
	nextStageEffect(p.stageNum);
	printStage();
	
	initNPC(npcArr, difficulty, p.stageNum, &npcNum);
	setDragonBallPos(dgball);

	initSpecialCloud(sCloud, 5, dgball[p.stageNum]);

	printCloud(stageArr[p.stageNum], dgball[p.stageNum]);
	drawPlayer(&p);
	UpdateRecord(&p);


	setStageDoor(stageDoor);
	printStageDoor(stageDoor, stageArr[p.stageNum], p.stageNum);

	for (int i = 0; i < 5; i++)			//구름 출력
		drawSpecialCloud(&sCloud[i], stageArr[p.stageNum]);

	zone z;
	InitZone(&z);
	safeZone(&z, p.stageNum, stageArr[p.stageNum]);
	printZone(&z, p.stageNum);
	



	//?�이??관??	int speed1 = 1, speed2 = 5;

	item item[50];
	InititemBox(speed1, speed2);

	while (1)
	{
		if (isGameOver(&p))
			break;

		if (count % 5 == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				deleteSpecialCloud(&sCloud[i], stageArr[p.stageNum]);
			}

			for (int i = 0; i < 5; i++)
				moveCloud(&sCloud[i], stageArr[p.stageNum]);
			
			for (int i = 0; i < 5; i++) {
				drawSpecialCloud(&sCloud[i], stageArr[p.stageNum]);
			}
		}



		//?�레?�어 ?�동

		jumpFlag = playerJump(&p, &jump, stageArr[p.stageNum]);
		count++;


		if (jumpFlag == 1) //?�프 ?�료 ???�점??
		{
			jump = collSpecialCloud(sCloud, &p, stageArr[p.stageNum]);
		}
		else if (jumpFlag == -1) //추락??경우
		{
			//npc ??��?�주�??�치 ?�설??			//deleteNpc(&npcArr, stageArr[p.stageNum]);
			/*npc.x = 1; npc.y = 1*/;

			//?�레?�어 ??�� and ?�치 ?�설??and 기록변�?			respawnPlayer(&p, stageArr[p.stageNum]);
			UpdateRecord(&p);
		}
			respawnPlayer(&p, stageArr[p.stageNum],difficulty,&npcArr,&npcNum);
		//?�래곤볼 and ?�테?��? 종료 ?�인
		if (dragonBallGet(&p, dgball[p.stageNum], stageArr[p.stageNum]) == 1) //?�래곤볼 ?�치?� ?�레?�어 ?�치 비교 ???�보 ?�데?�트
			UpdateRecord(&p);
		if (checkStageDoor(&p, stageDoor, p.stageNum)) { //?�래곤볼 ?��? 모으�?and �??�에 ???�으�??�음 ?�테?��?�??�동
			//마�?�??�테?��? ?�과?�면 게임 ?�내�?			if (p.stageNum == 2) {
				gameClearScreen();
				return;
			}
			p.stageNum++;
			nextStageEffect(p.stageNum);
			gotoNextStage(&p, dgball, stageDoor, stageArr[p.stageNum]);
			initSpecialCloud(sCloud, 5, dgball[p.stageNum]);
			for (int i = 0; i < 5; i++)			//구름 출력
				drawSpecialCloud(&sCloud[i], stageArr[p.stageNum]);
			InititemBox(speed1, speed2);
			initNPC(npcArr, difficulty, p.stageNum, &npcNum);
			safeZone(&z, p.stageNum, stageArr[p.stageNum]);
			printZone(&z, p.stageNum);
			p.x = p.spawnPos[p.stageNum][0];
			p.y = p.spawnPos[p.stageNum][1];
			npcArr = (NPC*)realloc(npcArr, sizeof(NPC) * npcNum);
		}

		processKeyInput(&p, stageArr[p.stageNum]);


//		?�레?�어 ?�직인 ??npc?�동 ?�작
//		추적 ?�고리즘 ?�작
		for (int i = 0; i < npcNum; i++) {
			addNpcCnt(&npcArr[i]);
			int dis = min(getDistance(p.x - npcArr[i].x, p.y - npcArr[i].y), getDistance(p.x - npcArr[i].x, p.y + 1 - npcArr[i].y)); //캐릭?��? npc?�이??거리
			dis = min(dis, getDistance(p.x - npcArr[i].x, p.y + 2 - npcArr[i].y));
			if (dis == 0) {  //최소 거리 루트2 ?�하?�면 ?�내�?
				deleteNpc(&npcArr[i], stageArr[p.stageNum]);
				deletePlayer(&p, stageArr[p.stageNum]);
				respawnPlayer(&p, stageArr[p.stageNum]);
			}
			if (npcArr[i].cnt % npcArr[i].npcSpeed == 0) {
				deleteNpc(&npcArr[i], stageArr[p.stageNum]);
				respawnPlayer(&p, stageArr[p.stageNum], difficulty, &npcArr, &npcNum);
				drawNpc(&npcArr[i]);
			}
			else {
				deleteNpc(&npcArr[i], stageArr[p.stageNum]);
				drawNpc(&npcArr[i]);
			}
		}

		//캐릭?? npc ?�후 ?�이??		Fallitem(&p, stageArr[p.stageNum], npcArr, sCloud, 5, &z);
		Fallitem(&p, stageArr[p.stageNum], npcArr, sCloud, 5, &z, difficulty, &npcNum);
	}
	system("cls");
	printEndScreen();
}