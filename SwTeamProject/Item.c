#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "cloud.h"
#include "Common.h"
#include "item.h"
#include "NpcTrack.h"
#include "characters.h"

#define MAX 5      // ������ �ִ� ����


//������ �ڽ� �ʱ�ȭ
void InititemBox(int speed1, int speed2)
{
    for (int i = 0; i < MAX; i++)
    {
        it[i].flag = 1;   //�ʱ�ȭ ��� ������ ��ġ�� �������� �ȵ�
        it[i].x = rand() % (stage1X - 2) + 1;
        for (int j = 0; j < i; j++) {
            while (it[i].x == it[j].x) {
                it[i].x = rand() % (stage1X - 2) + 1;
            }
        }
        it[i].y = 1;
        it[i].itemNum = itemNum(rand() % 5);
        it[i].life = rand() % 10;   // ���ð�
        it[i].speed = rand() % (speed2 - speed1) + speed1;   //���� ���ǵ� �ο�
    }
}

//�� �ݺ������� ������ ����
int itemNum(int num)
{
    if (num == 0)   return 13;
    else if (num == 1) return 17;
    else if (num == 2) return 19;
    else if (num == 3) return 23;
    else if (num == 4) return 29;
}

//�����۰� �÷��̾� �浹 ����
int Detectitem(player* p, int i, int stage[][60])
{
    if ((p->x == it[i].x) && (p->y == it[i].y || p->y + 1 == it[i].y || p->y + 2 == it[i].y)) {

        return 1;
    }
    else return 0;
}

//�浹�� �浹�� �������� ��ǥ �ʱ�ȭ (�ʿ� �״�� �����ִ� �� �ذ�)
void InitPosition(item* item)   // ���ο� ���������� ��ȯ
{
    int speed1 = 1, speed2 = 5;
    item->flag = 1;   //�ʱ�ȭ ��� ������ ��ġ�� �������� �ȵ�
    item->x = rand() % (stage1X - 2) + 1;
    item->y = 1;
    item->itemNum = itemNum(rand() % 5);
    item->life = rand() % 10;   // ���ð�
    item->speed = rand() % (speed2 - speed1) + speed1;   //���� ���ǵ� �ο�
}

//������ ������
void Fallitem(player* p, int stage[][60], NPC* npc, cloud* cloudArr, int CloudSize, zone* z, int difficulty, int* npcNum)
{
    for (int i = 0; i < MAX; i++)
    {
        if (Detectitem(p, i, stage) == 1)
        {
            // ������ Ȱ��ȭ
            func_item(it[i].itemNum, p, stage, npc, cloudArr, CloudSize, z, difficulty, npcNum);   //itemNum �ε����� �ش��ϴ� ��� ����
            InitPosition(&it[i]);
            UpdateRecord(p);
            // printf("%d", p->life);
        }

        if (it[i].flag == 1 && --it[i].life <= 0)   //�ش� �ε����� ������ ������ ������ ����, ���� ������ �ε����� ���ð� ������ ���̸鼭 �ڽ��� ���� ��ٸ�
        {
            int posX = OriginX + it[i].x * 2;
            int posY = OriginY + it[i].y;

            int pX = OriginX + p->x * 2;
            int pY = OriginY + p->y;


            if (posY == OriginY + stage1Y - 2)   //�ִ� ���� �Ÿ� �ӽ� ����
            {    //�ִ� �Ÿ����� ���ٸ� �����ְ� flag check ����
                deleteItem(i, stage);
                InitPosition(&it[i]);
                continue;
            }

            //���ð� �������� �ڽ��� ���ǵ常ŭ 
            it[i].life = it[i].speed;    //speed��°� �ᱹ ����. ���� ���� �������� �ӵ� ������

            deleteItem(i, stage);
            it[i].y++;
            posY = OriginY + it[i].y;
            SetCurrentCursorPos(posX, posY);
            showItem(it[i].itemNum);
        }
    }
}

void showItem(int num)
{
    if (num == 13) printf("��");
    else if (num == 17) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("��");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else if (num == 19) printf("��");
    else if (num == 23) printf("��");
    else if (num == 29) printf("��");
}

void deleteItem(int i, int stage[][60]) {
    int posX = OriginX + it[i].x * 2;
    int posY = OriginY + it[i].y;
    SetCurrentCursorPos(posX, posY);
    //   printf("  ");
    //   SetCurrentCursorPos(posX, posY);
    recoverCloud(it[i].x, it[i].y, stage);
}

void func_item(int itemNum, player* p, int stage[][60], NPC* npc, cloud* CloudArr, int CloudSize, zone* z, int difficulty, int* npcNum)
{
    if (itemNum == 13)
        p->life++;   //�߰�����ο�
    else if (itemNum % 17 == 0)
    {
        respawnPlayer(p, stage, difficulty, &npc, npcNum);
        UpdateRecord(p);
        //�� �Լ����� ��� �� ������
    }
    else if (itemNum == 19)    //������Ƽ������ �����̵�
    {
        deletePlayer(p, stage);
        //p->x = (OriginX + stage1X) / 2; p->y = (OriginY + stage1Y) / 2;
        p->x = (z->x[p->stageNum] + z->x[p->stageNum] + safeX) / 2;
        p->y = (z->y[p->stageNum] + z->y[p->stageNum] + safeY) / 2;
        drawPlayer(p);
    }
    else if (itemNum == 23) {//��� �� �� �߰�???
        npc[0].npcSpeed = 100;
        npc[1].npcSpeed = 100;
        npc[0].isMoving = 0;
        npc[1].isMoving = 0;
    }
    else if (itemNum == 29) {
        changeCloudType(CloudArr, CloudSize, stage);    //���� �����ٲ���(����, �̵�)
    }
}




