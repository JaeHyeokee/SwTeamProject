
#include "Common.h"


typedef struct item {
	int x;
	int y;
	int flag;       //0,1�� ���� ǥ�� ȭ�鿡 ǥ�� or ǥ��x
	int life;       //���� ���� ���ð�
	int speed;      //���� ������ �������� �ӵ�
	int itemNum;    //���ϴ� ������ �ѹ�
	int check;   //ó�� �浹�ϸ� 1�� �ٲ㼭 ���� �Ϻ��� ����������(�Ⱥ��̵���)
}item;

//������ �߻� �󵵿� �ӵ� �޶������� ��������!

void InititemBox(item* item);
void CreateItem(item* item, int speed1, int speed2);
void showItem(int num);
void Fallitem(item* item, player *p);
int Detectitem(item* item, player* p);
void useitem(player* p);


