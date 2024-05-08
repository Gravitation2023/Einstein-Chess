#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;


bool MO = 1;                  //1�ô���췽�ƶ���0��ʾ�������ƶ�
#define GRID_W 70    //���ӵĿ��
#define INTERVAL 70  //��϶��С
#define ROW 5
#define COL 5
int map[ROW][COL] = { 0 };    //��ͼ��������췽������������
int choose = 0;    //0��ʾû�����ӿ����ƶ���1��ʾ�����ӿ����ƶ�



//������
//��������
class Point
{
public:
	int x;
	int y;
};

class Fin : public Point
{
public:
	int fin;
};


//��������
class Chess
{
public:
	int num;     //��������
	int color;   //������ɫ��0����췽��1��������
	bool bl;     //�ж������Ƿ����
	double Pro;  //�����ܹ��ƶ��ĸ���
	Point P;     //���ӵ������ά�����ʾ
	int move;    //�����Ƿ����ƶ�,1��ʾ��Ҫ�ƶ�
	double value;//���ӷֲ���ֵ��Ϣ
	int next;    //�ݴ�������һ���ƶ���Ϣ
	double v;    //�ݴ�����ģ���ƶ������������ֵ
	double rate; //�ݴ�����ģ���ƶ���ʤ��

	Chess()
	{
		this->num = 0;
		this->color = -1;
		P.x = -1;
		P.y = -1;
		bl = false;
		Pro = 0;
		move = 0;
		value = -1000;
		next = 0;
		v = 0;
		rate = 0;
	}
	bool CanMove(Chess& ce, int x, int y);       //�����Ƿ�����ƶ�

	void MoveTo(Chess& ce, int x, int y);
	//hess();
};

Chess chess[2][6];  //�����Ƿ���ڣ�0��ʾ�췽��1��ʾ����

bool Chess::CanMove(Chess& ce, int x, int y)       //�жϸ������Ƿ��ܹ��ƶ�
{
	//�ж������ƶ������Ƿ���ȷ
	if (ce.bl && ce.color == 0 && ((x - ce.P.x == 1 && (y == ce.P.y || y - ce.P.y == 1)) || (x == ce.P.x && y - ce.P.y == 1)))    //�췽����
	{
		return true;
	}
	else if (ce.bl && ce.color == 1 && ((ce.P.x - x == 1 && (y == ce.P.y || ce.P.y - y == 1)) || (x == ce.P.x && ce.P.y - y == 1)))  //��������
	{
		return true;
	}
	return false;
}


void Chess::MoveTo(Chess& ce, int x, int y)         //�����������ƶ���������ce�ƶ���x,y��
{
	//���ӵ������ƶ�
	if (CanMove(ce, x, y))
	{
		//�����ƶ�λ���ϵ�����
		if (map[x][y] > 0)       //����췽����
		{
			chess[0][map[x][y] - 1].bl = false;
			chess[0][map[x][y] - 1].Pro = 0;
		}
		else if (map[x][y] < 0)  //������������
		{
			chess[1][-map[x][y] - 1].bl = false;
			chess[1][map[x][y] - 1].Pro = 0;
		}
		//�����ƶ�������
		for (int k = 0; k <= 1; k++)
			for (int i = 0; i < 6; i++)
				chess[k][i].move = 0;
		if (MO)                      //���Ϊ�췽
			map[x][y] = ce.num;
		else
			map[x][y] = -ce.num;
		map[ce.P.x][ce.P.y] = 0;
		ce.P.x = x;
		ce.P.y = y;
		MO = !MO;
		choose = 0;
	}
}



void prob(Chess ce[2][6])                             //�����ƶ�����
{
	for (int k = 0; k <= 1; k++) {
		for (int i = 0; i < 6; i++)
		{
			if (ce[k][i].bl)
			{
				int l = 0, r = 0;
				for (int left = i - 1; !ce[k][left].bl && left >= 0; left--)
					l++;
				for (int right = i + 1; !ce[k][right].bl && right < 6; right++)
					r++;
				ce[k][i].Pro = (1 + l + r) / 6.0;
				//printf("%d %d %f\n", k, i+1, ce[k][i].Pro);
			}
		}
	}
}



//�ж�ʤ��
bool winner()
{
	//�Խ���ʤ��
	if (map[0][0] < 0)
	{
		BlueVictory();
		return true;
	}
	if (map[4][4] > 0)
	{
		RedVictory();
		return true;
	}
	//ȫ��ʤ��
	for (int i = 0; i < 6; i++)
	{
		if (chess[0][i].bl == 1)
			break;
		else if (i == 5)
		{
			BlueVictory();
			return true;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (chess[1][i].bl == 1)
			break;
		else if (i == 5)
		{
			RedVictory();
			return true;
		}
	}
	return false;
}