#include<stdio.h>
#include<math.h>
#include<ctime>
#include <random>
#include "chess.h"


int STFPS = 5000;          //ģ�����



void putr(bool& red, Chess ce[2][6], int map[5][5], bool& MO)     //�ڷź췽����
{
	red = true;
	MO = !MO;
	for (int j = 0; j <= 5; j++)
	{
		chess[0][j].num = j + 1;
		chess[0][j].color = 0;
		chess[0][j].Pro = 1.0 / 6.0;
		chess[0][j].move = 0;
		chess[0][j].bl = 1;
	}
	chess[0][5].P.x = 0;
	chess[0][5].P.y = 0;
	map[0][0] = 6;
	chess[0][1].P.x = 1;
	chess[0][1].P.y = 0;
	map[1][0] = 2;
	chess[0][3].P.x = 2;
	chess[0][3].P.y = 0;
	map[2][0] = 4;
	chess[0][0].P.x = 0;
	chess[0][0].P.y = 1;
	map[0][1] = 1;
	chess[0][4].P.x = 1;
	chess[0][4].P.y = 1;
	map[1][1] = 5;
	chess[0][2].P.x = 0;
	chess[0][2].P.y = 2;
	map[0][2] = 3;
}


void putb(bool& blue, Chess ce[2][6], int map[5][5], bool& MO)     //�ڷ���������
{
	blue = true;
	MO = !MO;
	for (int j = 0; j <= 5; j++)
	{
		chess[1][j].num = j + 1;
		chess[1][j].color = 1;
		chess[1][j].Pro = 1.0 / 6.0;
		chess[1][j].move = 0;
		chess[1][j].bl = 1;
	}
	chess[1][5].P.x = 4;
	chess[1][5].P.y = 4;
	map[4][4] = -6;
	chess[1][1].P.x = 3;
	chess[1][1].P.y = 4;
	map[3][4] = -2;
	chess[1][3].P.x = 2;
	chess[1][3].P.y = 4;
	map[2][4] = -4;
	chess[1][0].P.x = 4;
	chess[1][0].P.y = 3;
	map[4][3] = -1;
	chess[1][4].P.x = 3;
	chess[1][4].P.y = 3;
	map[3][3] = -5;
	chess[1][2].P.x = 4;
	chess[1][2].P.y = 2;
	map[4][2] = -3;
}

int Win(int map0[5][5])              //�ж�ʤ��
{
	//�Խ���ʤ��
	if (map0[0][0] < 0)              //����ʤ��
	{
		return !MO;
	}
	if (map0[4][4] > 0)              //�췽ʤ��
	{
		return MO;
	}
	//ȫ��ʤ��
	int n = 0, m = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (map0[i][j] > 0)
				n++;
			if (map0[i][j] < 0)
				m++;
		}
	if (n == 0)          //����ʤ��
	{
		return !MO;
	}
	else if (m == 0)     //�췽ʤ��
	{
		return MO;
	}
	//û����ʤ��
	return -1;
}

void move(Chess ch[2][6], int map0[5][5], int num, bool Player)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 2);
	int m = 0;                                                 //��¼Ҫ�ƶ���λ���ϵ�����
	int ma[5][5] = { 0 };
	for (int n = 0; n < 5; n++)
		for (int k = 0; k < 5; k++)
			ma[n][k] = map0[n][k];
	int x = ch[Player][num].P.x, y = ch[Player][num].P.y;
	int how = dis(gen);                                        //������ƶ���Ϊ0����Ϊ1����Ϊ2б��
	// �����ƶ�λ���ϵ�����
	if(Player)                                                 //���Ϊ�����ƶ�
	{
		//printf("��");
		if(how == 0 && x > 0)                                  //����
		{
			m = ma[x - 1][y];
			map0[x - 1][y] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x - 1;
			ch[Player][num].P.y = y;
		}
		else if(how == 1 && y > 0)                              //����
		{
			m = ma[x][y - 1];
			map0[x][y - 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x;
			ch[Player][num].P.y = y - 1;
		}
		else if(how == 2 && (x > 0 && y > 0))                   //������
		{
			m = ma[x - 1][y - 1];
			map0[x - 1][y - 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x - 1;
			ch[Player][num].P.y = y - 1;
		}
		//........��ֹ����ѡ������������޷��ƶ������.......................//
		else if(x > 0)                                        //����      
		{
			m = ma[x - 1][y];
			map0[x - 1][y] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x - 1;
			ch[Player][num].P.y = y;
		}
		else if(y > 0)                                        //����
		{
			m = ma[x][y - 1];
			map0[x][y - 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x;
			ch[Player][num].P.y = y - 1;
		}
		else if(x > 0 && y > 0)                              //������
		{
			m = ma[x - 1][y - 1];
			map0[x - 1][y - 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x - 1;
			ch[Player][num].P.y = y - 1;
		}
	}
	else                                                       //���Ϊ�췽�ƶ�
	{
		//printf("��");
		if (how == 0 && x < 4)                                 //����
		{
			m = ma[x + 1][y];
			map0[x + 1][y] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x + 1;
			ch[Player][num].P.y = y;
		}
		else if (how == 1 && y < 4)                             //����
		{
			m = ma[x][y + 1];
			map0[x][y + 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x;
			ch[Player][num].P.y = y + 1;
		}
		else if (how == 2 && (x < 4 && y < 4))                  //������
		{
			m = ma[x + 1][y + 1];
			map0[x + 1][y + 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x + 1;
			ch[Player][num].P.y = y + 1;
		}
		//........��ֹ����ѡ������������޷��ƶ������.......................//
		else if (x < 4)                                         //����      
		{
			m = ma[x + 1][y];
			map0[x + 1][y] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x + 1;
			ch[Player][num].P.y = y;
		}
		else if (y < 4)                                         //����
		{
			m = ma[x][y + 1];
			map0[x][y + 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x;
			ch[Player][num].P.y = y + 1;
		}
		else if (x < 4 && y < 4)                               //������
		{
			m = ma[x + 1][y + 1];
			map0[x + 1][y + 1] = map0[x][y];
			map0[x][y] = 0;
			ch[Player][num].P.x = x + 1;
			ch[Player][num].P.y = y + 1;
		}
	}
	if (m > 0)       //����췽����
	{
		ch[0][m - 1].bl = false;
	}
	else if (m < 0)  //������������
	{
		ch[1][-m - 1].bl = false;
	}
}




void h_move(Chess ch[2][6],int map0[5][5],int num,bool Player)      //�ƶ�����
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1);
	int who = dis(gen);                                   //��˭�ƶ�
	if (ch[Player][num].bl)                               //��������Ӵ���
		move(ch, map0, num, Player);
	else                                                  //������Ӳ�����,�ֱ�Ѱ�����ߴ��ڵ�����
	{
		int t = 0, n = -1, m = -1;
		for (int i = num; i <= 5 && t == 0; i++)
			if (ch[Player][i].bl)
			{
				n = i;
				t = 1;
			}
		t = 0;
		for (int i = num; i >= 0 && t == 0; i--)
			if (ch[Player][i].bl)
			{
				m = i;
				t = 1;
			}
		if (n == -1 && m == -1)
			map0[0][0] = -1;
		else if (n == -1 && m != -1)
			move(ch, map0, m, Player);
		else if (m == -1 && n != -1)
			move(ch, map0, n, Player);
		else if (who == 0)
			move(ch, map0, n, Player);
		else if (who == 1)
			move(ch, map0, m, Player);

	}
}

double Rate(Chess ce[2][6],int map1[5][5])                           //ģ��STFPS�Σ��õ�����ʤ��
{
	int win_Sum = 0;
	int p = 0;
	for (int i = 0; i < STFPS; i++)
	{
		//��ʼ��
		int map0[5][5] = { 0 };
		Chess ch[2][6];
		for (int I = 0; I < 2; I++)
			for (int J = 0; J < 6; J++)
				ch[I][J] = ce[I][J];
		for(int n=0;n<5;n++)
			for(int m=0;m<5;m++)
		map0[n][m] = map1[n][m];
		bool Player = MO;                      //�����ƶ���������ɫ
		//����ƶ���ֱ��������Ϸ,��һ��ʤ��
		while (1)
		{
			if (Win(map0) == 1 || Win(map0) == 0)       //�ж���Ϸ�Ƿ����
			{
				win_Sum += Win(map0);
				break;
			}
			// ���������������  
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 5);

			int num = dis(gen);                         //�����0~5
     		h_move(ch, map0, num,Player);               //�ƶ�
			Player = !Player;
		}
	}
	return 1.0 * win_Sum / STFPS;
}


void GetBestRate(Chess chess[2][6], int q)
{

	if (MO == 1)                                   //�췽�ƶ�
	{
		double rate1 = 0, rate2 = 0, rate3 = 0;


		if (chess[!MO][q].P.y < 4)                //�ж��ܷ������ƶ�
		{
			Chess chess1[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess1[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map1[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map1[n][m] = map[n][m];
			if (map[i][j + 1] > 0)                  //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i][j + 1] - 1;            //��ȡ��������ֵ
				chess1[0][num].bl = 0;
				chess1[0][num].Pro = 0;
				chess1[0][num].move = 0;
			}
			if (map[i][j + 1] < 0)                 //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i][j + 1] - 1;          //��ȡ��������ֵ
				chess1[1][num].bl = 0;
				chess1[1][num].Pro = 0;
				chess1[1][num].move = 0;
			}
			map1[i][j + 1] = map1[i][j];            //�ƶ�
			map1[i][j] = 0;
			chess1[!MO][q].P.y = chess[!MO][q].P.y + 1;
			chess1[!MO][q].P.x = chess[!MO][q].P.x;
			rate1 = Rate(chess1, map1);             //����ʤ��
			printf("���µ�ʤ��=%f", rate1*100);
			cout << "%\n";
		}
		if (chess[!MO][q].P.y < 4 && chess[!MO][q].P.x < 4)//�ж��ܷ��������ƶ�
		{
			Chess chess2[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess2[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map2[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map2[n][m] = map[n][m];

			if (map[i + 1][j + 1] > 0)                //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i + 1][j + 1] - 1;          //��ȡ��������ֵ
				chess2[0][num].bl = 0;
				chess2[0][num].Pro = 0;
				chess2[0][num].move = 0;
			}
			if (map[i + 1][j + 1] < 0)               //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i + 1][j + 1] - 1;        //��ȡ��������ֵ
				chess2[1][num].bl = 0;
				chess2[1][num].Pro = 0;
				chess2[1][num].move = 0;
			}
			map2[i + 1][j + 1] = map2[i][j];         //�ƶ�
			map2[i][j] = 0;
			chess2[!MO][q].P.y = chess[!MO][q].P.y + 1;
			chess2[!MO][q].P.x = chess[!MO][q].P.x + 1;
			rate2 = Rate(chess2, map2);              //����ʤ��
			printf("�����µ�ʤ��=%f", rate2*100);
			cout << "%\n";
		}
		if (chess[!MO][q].P.x < 4)                  //�ж��ܷ������ƶ�
		{
			Chess chess3[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess3[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map3[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map3[n][m] = map[n][m];

			if (map[i + 1][j] > 0)                  //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i + 1][j] - 1;            //��ȡ��������ֵ
				chess3[0][num].bl = 0;
				chess3[0][num].Pro = 0;
				chess3[0][num].move = 0;
			}
			if (map[i + 1][j + 1] < 0)             //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i + 1][j] - 1;          //��ȡ��������ֵ
				chess3[1][num].bl = 0;
				chess3[1][num].Pro = 0;
				chess3[1][num].move = 0;
			}
			map3[i + 1][j] = map3[i][j];           //�ƶ�
			map3[i][j] = 0;
			chess3[!MO][q].P.y = chess[!MO][q].P.y;
			chess3[!MO][q].P.x = chess[!MO][q].P.x + 1;
			rate3 = Rate(chess3, map3);            //����ʤ��
			printf("���ҵ�ʤ��=%f", rate3*100);     
			cout << "%\n";
		}

		if (rate2 <= rate1 && rate3 <= rate1)//�����ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = 1;
			chess[!MO][q].rate = rate1;
		}
		if (rate2 >= rate1 && rate2 >= rate3)//�������ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = 2;
			chess[!MO][q].rate = rate2;
		}
		if (rate3 >= rate1 && rate3 >= rate2)//�����ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = 3;
			chess[!MO][q].rate = rate3;
		}

	}




	if (MO == 0) //�����ƶ�
	{
		double rate1 = 0, rate2 = 0, rate3 = 0;

		if (chess[!MO][q].P.y > 0)          //�ж��ܷ������ƶ�
		{
			Chess chess1[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess1[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map1[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map1[n][m] = map[n][m];
			if (map[i][j - 1] > 0)          //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i][j - 1] - 1;    //��ȡ��������ֵ
				chess1[0][num].bl = 0;
				chess1[0][num].Pro = 0;
				chess1[0][num].move = 0;
			}
			if (map[i][j - 1] < 0)          //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i][j - 1] - 1;   //��ȡ��������ֵ
				chess1[1][num].bl = 0;
				chess1[1][num].Pro = 0;
				chess1[1][num].move = 0;
			}
			map1[i][j - 1] = map1[i][j];    //�ƶ�
			map1[i][j] = 0;
			chess1[!MO][q].P.y = chess[!MO][q].P.y - 1;
			chess1[!MO][q].P.x = chess[!MO][q].P.x;
			rate1 = Rate(chess1, map1);     //����ʤ��
			printf("���ϵ�ʤ��=%f", rate1*100);
			cout << "%\n";
		}
		if (chess[!MO][q].P.y > 0 && chess[!MO][q].P.x > 0)//�ж��ܷ��������ƶ�
		{
			Chess chess2[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess2[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map2[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map2[n][m] = map[n][m];

			if (map[i - 1][j - 1] > 0)                   //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i - 1][j - 1] - 1;             //��ȡ��������ֵ
				chess2[0][num].bl = 0;
				chess2[0][num].Pro = 0;
				chess2[0][num].move = 0;
			}
			if (map[i - 1][j - 1] < 0)                   //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i - 1][j - 1] - 1;            //��ȡ��������ֵ
				chess2[1][num].bl = 0;
				chess2[1][num].Pro = 0;
				chess2[1][num].move = 0;
			}
			map2[i - 1][j - 1] = map2[i][j];              //�ƶ�
			map2[i][j] = 0;
			chess2[!MO][q].P.y = chess[!MO][q].P.y - 1;
			chess2[!MO][q].P.x = chess[!MO][q].P.x - 1;

			rate2 = Rate(chess2, map2);                   //����ʤ��
			printf("�����ϵ�ʤ��=%f", rate2*100);
			cout << "%\n";
		}
		if (chess[!MO][q].P.x > 0)            //�ж��ܷ������ƶ�
		{
			Chess chess3[2][6];
			for (int I = 0; I < 2; I++)
				for (int J = 0; J < 6; J++)
					chess3[I][J] = chess[I][J];
			int num = 0;
			int i = chess[!MO][q].P.x;
			int j = chess[!MO][q].P.y;
			int map3[5][5] = { 0 };
			for (int n = 0; n < 5; n++)
				for (int m = 0; m < 5; m++)
					map3[n][m] = map[n][m];

			if (map[i - 1][j] > 0)            //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = map[i - 1][j] - 1;      //��ȡ��������ֵ
				chess3[0][num].bl = 0;
				chess3[0][num].Pro = 0;
				chess3[0][num].move = 0;
			}
			if (map[i - 1][j] < 0)            //�ж���ɫΪ��ɫ������·���ϵ�����
			{
				num = -map[i - 1][j] - 1;     //��ȡ��������ֵ
				chess3[1][num].bl = 0;
				chess3[1][num].Pro = 0;
				chess3[1][num].move = 0;
			}
			map3[i - 1][j] = map3[i][j];      //�ƶ�
			map3[i][j] = 0;
			chess3[!MO][q].P.y = chess[!MO][q].P.y;
			chess3[!MO][q].P.x = chess[!MO][q].P.x - 1;
			rate3 = Rate(chess3, map3);       //����ʤ��
			printf("�����ʤ��=%f", rate3*100);
			cout << "%\n";
		}
		if (rate2 <= rate1 && rate3 <= rate1)//�����ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = -1;
			chess[!MO][q].rate = rate1;
		}
		if (rate2 >= rate1 && rate2 >= rate3)//�������ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = -2;
			chess[!MO][q].rate = rate2;
		}
		if (rate3 >= rate1 && rate3 >= rate2)//�����ƶ�value��󣬸�������rate��nextֵ
		{
			chess[!MO][q].next = -3;
			chess[!MO][q].rate = rate3;
		}


	}
          //����������ƶ����,��ֻ��Ҫ�ж�����ʤ�ʸߣ�Ȼ�󷵻���x,y,fin�Ϳ�����
}

Fin ChooseBest(Chess chess[2][6])
{
	double Rate =0;
	int fin = 0;
	Fin p;                                  //����p�洢��Ϣ
	p.x = 0;
	p.y = 0;
	p.fin = 0;
	for (int q = 0; q < 6; q++)
	{
		if (chess[!MO][q].move == 1)
		{
			printf("num=%d\n", q+1);         //����ƶ�������ֵ
			GetBestRate(chess,q);
			if (chess[!MO][q].rate > Rate)   //ͨ���Ƚϻ�������ƶ����Ӻ��ƶ�����
			{
				fin = q;
				p.fin = q;
				p.x = chess[!MO][q].P.x;
				p.y = chess[!MO][q].P.y;
				Rate = chess[!MO][q].rate;

			}
			chess[!MO][q].rate=0;            //��������
		}
	}
	if (chess[!MO][fin].next == 1)//�����ƶ�
	{
		p.x = p.x;
		p.y = p.y + 1;
	}
	if (chess[!MO][fin].next == 2)//�������ƶ�
	{
		p.x = p.x + 1;
		p.y = p.y + 1;
	}
	if (chess[!MO][fin].next == 3)//�����ƶ�
	{
		p.x = p.x + 1;
		p.y = p.y;
	}
	if (chess[!MO][fin].next == -1)//�����ƶ�
	{
		p.x = p.x;
		p.y = p.y - 1;
	}
	if (chess[!MO][fin].next == -2)//�������ƶ�
	{
		p.x = p.x - 1;
		p.y = p.y - 1;
	}
	if (chess[!MO][fin].next == -3)//�����ƶ�
	{
		p.x = p.x - 1;
		p.y = p.y;
	}
	return p;
}



void paff(Chess chess[2][6])
{
	Fin P = ChooseBest(chess);     
	chess[!MO][P.fin].MoveTo(chess[!MO][P.fin], P.x, P.y);
}