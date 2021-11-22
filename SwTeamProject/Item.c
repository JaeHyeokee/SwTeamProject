
#include <stdio.h>
#include <time.h>
#include <windows.h>


#include "Common.h"
#include "item.h"
#include "NpcTrack.h"
#include "characters.h"

#define MAX 50      // ������ �ִ� ����

//������ �ڽ� �ʱ�ȭ
void InititemBox(item* item)   
{
	for (int i = 0; i < MAX; i++)
	{
		item[i].flag = 0;   //�ʱ�ȭ ��� ������ ��ġ�� �������� �ȵ�
		item[i].check = 0;
	}
}

//�� �ݺ������� ������ ���� (�� 50���� ��)
void CreateItem(item* item, int speed1, int speed2)
{
	srand(time(NULL));   //��ġ ���� ���� ���ؼ�
	for (int i = 0; i < MAX; i++)   //MAX_X ������ ���� ���� ����
	{
		if (item[i].flag == 0)  //���� �ش� �ε����� �������� ������
		{
			item[i].x = (rand() % (stage1X-OriginX)*2) + OriginX*2;   //x��ǥ�� �������� �� 0~40
			item[i].y = OriginY + 1;
			item[i].itemNum = rand() % 5;   //�ϴ� 0~4�� �� �ο� ������ �� ���� �����ؾ���
			item[i].life = rand() % 10;   // ���ð�
			item[i].speed = rand() % (speed2 - speed1) + speed1;   //���� ���ǵ� �ο�
			item[i].flag = 1;
			return;
		}
	}
}

//�����۰� �÷��̾� �浹 ����
int Detectitem(item *item, player* p)    
{
	for (int i = 0; i < MAX; i++)
	{
		int posX = OriginX + p->x * 2;
		int posY = OriginY + p->y;
		int itemX = OriginX + item[i].x * 2;
		int itemY = OriginY + item[i].y;
		//int dis = getDistance(p->x - item[i].x, p->y - item[i].y);
		int dis = getDistance(posX - itemX, posY - itemY);
		if (dis < 4)
		{
			return 1;
		}
		else return 0;
	}
}

//������ ������
void Fallitem(item* item, player* p)
{
	for (int i = 0; i < MAX; i++)
	{
		if (item[i].flag == 1 && item[i].check == 0)   //�ش� �ε����� ������ ������ ������ ����
		{
			if (--item[i].life == 0 && item[i].check == 0)    //���� ������ �ε����� ���ð� ������ ���̸鼭 �ڽ��� ���� ��ٸ�
			{
				int detect = Detectitem(item, p);
				if (detect == 1)  //�浹
				{    //�� �浹 Ž���� ������?
					//�����۸����� ��� ���� �Լ� ���߿� �߰�
					item[i].flag = 0;
					SetCurrentCursorPos(item[i].x, item[i].y);
					printf("  ");
					item[i].check = 1;
					return;
				}



				//���ð� �������� �ڽ��� ���ǵ常ŭ 
				item[i].life = item[i].speed;    //speed��°� �ᱹ ����. ���� ���� �������� �ӵ� ������

				SetCurrentCursorPos(item[i].x, item[i].y);
				printf("  ");   //���� �����ְ�

				
				SetCurrentCursorPos(item[i].x, ++item[i].y); //��ĭ �̵� �� ���
				showItem(item[i].itemNum);
				
				if (item[i].y >= OriginY + stage1Y - 2)   //�ִ� ���� �Ÿ� �ӽ� ����
				{    //�ִ� �Ÿ����� ���ٸ� �����ְ� flag check ����
					SetCurrentCursorPos(item[i].x, item[i].y);
					printf("  ");
					item[i].flag = 0;  //�ٽ� ȭ��ǥ��x�� ����
					item[i].check = 1;
				}
			}
		}
	}
}





void showItem(int num)
{
	if (num == 0)
	{
		printf("��");
	}
	else if (num == 1)
	{
		printf("��");
	}
	else if (num == 2)
	{
		printf("��");
	}
	else if (num == 3)
	{
		printf("��");
	}
	else if (num == 4)
	{
		printf("��");
	}
}





