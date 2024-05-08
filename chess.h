#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;


bool MO = 1;                  //1该代表红方移动，0表示该蓝方移动
#define GRID_W 70    //格子的宽度
#define INTERVAL 70  //空隙大小
#define ROW 5
#define COL 5
int map[ROW][COL] = { 0 };    //地图，正代表红方，负代表蓝方
int choose = 0;    //0表示没有棋子可以移动，1表示有棋子可以移动



//棋子类
//棋子坐标
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


//棋子属性
class Chess
{
public:
	int num;     //棋子数字
	int color;   //棋子颜色，0代表红方，1代表蓝方
	bool bl;     //判断棋子是否存在
	double Pro;  //棋子能够移动的概率
	Point P;     //棋子的坐标二维数组表示
	int move;    //棋子是否能移动,1表示将要移动
	double value;//棋子分布价值信息
	int next;    //暂存棋子下一步移动信息
	double v;    //暂存棋子模拟移动后棋盘总体价值
	double rate; //暂存棋子模拟移动后胜率

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
	bool CanMove(Chess& ce, int x, int y);       //棋子是否可以移动

	void MoveTo(Chess& ce, int x, int y);
	//hess();
};

Chess chess[2][6];  //棋子是否存在，0表示红方，1表示蓝方

bool Chess::CanMove(Chess& ce, int x, int y)       //判断该棋子是否能够移动
{
	//判断棋子移动方向是否正确
	if (ce.bl && ce.color == 0 && ((x - ce.P.x == 1 && (y == ce.P.y || y - ce.P.y == 1)) || (x == ce.P.x && y - ce.P.y == 1)))    //红方棋子
	{
		return true;
	}
	else if (ce.bl && ce.color == 1 && ((ce.P.x - x == 1 && (y == ce.P.y || ce.P.y - y == 1)) || (x == ce.P.x && ce.P.y - y == 1)))  //蓝方棋子
	{
		return true;
	}
	return false;
}


void Chess::MoveTo(Chess& ce, int x, int y)         //如果满足可以移动的条件则将ce移动到x,y上
{
	//棋子的坐标移动
	if (CanMove(ce, x, y))
	{
		//处理移动位置上的棋子
		if (map[x][y] > 0)       //处理红方棋子
		{
			chess[0][map[x][y] - 1].bl = false;
			chess[0][map[x][y] - 1].Pro = 0;
		}
		else if (map[x][y] < 0)  //处理蓝方棋子
		{
			chess[1][-map[x][y] - 1].bl = false;
			chess[1][map[x][y] - 1].Pro = 0;
		}
		//处理移动的棋子
		for (int k = 0; k <= 1; k++)
			for (int i = 0; i < 6; i++)
				chess[k][i].move = 0;
		if (MO)                      //如果为红方
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



void prob(Chess ce[2][6])                             //计算移动概率
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



//判断胜利
bool winner()
{
	//对角线胜利
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
	//全吃胜利
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