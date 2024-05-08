#include<stdio.h>
#include<math.h>
#include "chess.h"

void putr(bool& red, Chess ce[2][6], int map[5][5],bool& MO)     //�ڷź췽����
{
	red = true;
	MO = !MO;
	for (int j = 0; j <= 5; j++)
	{
		chess[0][j].num = j + 1;
		chess[0][j].color = 0;
		chess[0][j].Pro = 1.0/  6.0;
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


void putb(bool& blue, Chess ce[2][6], int map[5][5],bool& MO)     //�ڷ���������
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

int distance(Chess ce)                           //�����ӵ����涥�����̾���
{ 
	int n = 0, x = ce.P.x, y = ce.P.y;

	if (!ce.color)
	{
		for (; x != 4 || y != 4;)
		{
			if (x != 4 && y != 4)
			{
				x++;
				y++;
				n++;
			}
			if (x == 4 && y != 4)
			{
				y++;
				n++;
			}
			if (x != 4 && y == 4)
			{
				x++;
				n++;
			}
		}
		return n;
	}

	else
	{
		for (; x != 0 || y != 0;)
		{
			if (x != 0 && y != 0)
			{
				x--;
				y--;
				n++;
			}
			if (x == 0 && y != 0)
			{
				y--;
				n++;
			}
			if (x != 0 && y == 0)
			{
				x--;
				n++;
			}
		}
		return n;
	}
}

double Thread1(Chess chess[2][6],int i,int j)            //������в��thread1
{
	double thread1 = 0;
	double thread11=0, thread12=0, thread13=0;
	if (MO == 1)  //�췽
	{
		if (i == 0 && j == 0)                //����
		{
			thread1 += 0;
		}
		if (i == 0 && j > 0)                 //�߽�
		{
			if (map[i][j - 1] > 0)
			{
				thread1 += (chess[0][map[i][j - 1] - 1].value) * (chess[0][map[i][j - 1] - 1].Pro);
			}
		}
		if (j == 0 && i > 0)                 //�߽�
		{
			if (map[i - 1][j] > 0)
			{
				thread1 += (chess[0][map[i - 1][j] - 1].value) * (chess[0][map[i - 1][j] - 1].Pro);
			}
		}
		if (i > 0 && j > 0)                  //�Ǳ߽�
		{
			if (map[i][j - 1] > 0)           //�ж��Ϸ����޺�ɫ����
			{
				thread11 += (chess[0][map[i][j - 1] - 1].value) * (chess[0][map[i][j - 1] - 1].Pro);
			}
			if (map[i - 1][j-1] > 0)         //�ж����Ϸ����޺�ɫ����
			{
				thread12 += (chess[0][map[i - 1][j - 1] - 1].value) * (chess[0][map[i - 1][j - 1] - 1].Pro);
			}
			if (map[i - 1][j] > 0)           //�ж������޺�ɫ����
			{
				thread13 += (chess[0][map[i - 1][j]-1].value)*(chess[0][map[i - 1][j] - 1].Pro);
			}
			if (thread11 >= thread12 && thread11 >=thread13)      //�Ƚ�
			{
				thread1 = thread11;
			}
			if (thread12 >= thread11 && thread12 >= thread13)     //�Ƚ�
			{
				thread1 = thread12;
			}
			if (thread13 >= thread12 && thread13 >= thread11)     //�Ƚ�
			{
				thread1 = thread13;
			}
		}
	}

	 

	if (MO == 0)          //����
	{
		if (i == 4 && j == 4)              //����
		{
			thread1 += 0;
		}
		if (i == 4 && j < 4)               //�߽�
		{
			if (map[i][j + 1] < 0)
			{
				thread1 += (chess[1][-map[i][j + 1] - 1].value) * (chess[1][-map[i][j + 1] - 1].Pro);
			}
		}
		if (i < 4 && j == 4)               //�߽�
		{
			if (map[i + 1][j] < 0)
			{
				thread1 += (chess[1][-map[i + 1][j] - 1].value) * (chess[1][-map[i + 1][j] - 1].Pro);
			}
		}
		if (i < 4 && j < 4)                //�Ǳ߽�
		{
			if (map[i][j + 1] < 0)         //�ж��·�������ɫ����
			{
				thread11 += (chess[1][-map[i][j + 1] - 1].value) * (chess[1][-map[i][j + 1] - 1].Pro);
			}
			if (map[i + 1][j + 1] < 0)     //�ж����·�������ɫ����
			{
				thread12 += (chess[1][-map[i + 1][j + 1] - 1].value) * (chess[1][-map[i + 1][j + 1] - 1].Pro);
			}
			if (map[i + 1][j] < 0)          //�ж��ҷ�������ɫ����
			{
				thread13 += (chess[1][-map[i + 1][j] - 1].value) * (chess[1][-map[i + 1][j] - 1].Pro);
			}
			if (thread11 >= thread12 && thread11 > thread13)       //�Ƚ�
			{
				thread1 = thread11;
			}
			if (thread12 >= thread11 && thread12 > thread13)       //�Ƚ�
			{
				thread1 = thread12;
			}
			if (thread13 >= thread12 && thread13 > thread11)       //�Ƚ�
			{
				thread1 = thread13;
			}
		}
	}
	printf("����thread1=%f", thread1);
	return thread1;
}


double Thread2(Chess chess[2][6], int i, int j)              //������в��thread2
{
	double thread2 = 0;
	double thread21 = 0, thread22 = 0, thread23 = 0;
	if (MO == 1)        	                                 //�췽
	{
	

		if (i == 4 && j == 4)                                 //����
		{
			thread2 += 0;
		}
		if (i == 4 && j < 4)                                  //�߽�
		{
			if (map[i][j + 1] < 0)
			{
				thread2 += (chess[1][-map[i][j + 1] - 1].value) * (chess[1][-map[i][j + 1] - 1].Pro);
			}
		}
		if (i < 4 && j == 4)                                  //�߽�
		{
			if (map[i + 1][j] < 0)
			{
				thread2 += (chess[1][-map[i + 1][j] - 1].value) * (chess[1][-map[i + 1][j] - 1].Pro);
			}
		}
		if (i < 4 && j < 4)                                    //�Ǳ߽�
		{
			if (map[i][j + 1] < 0)                             //�ж��·�������ɫ����
			{
				thread21 += (chess[1][-map[i][j + 1] - 1].value) * (chess[1][-map[i][j + 1] - 1].Pro);
			}
			if (map[i + 1][j + 1] < 0)                         //�ж����·�������ɫ����
			{
				thread22 += (chess[1][-map[i + 1][j + 1] - 1].value) * (chess[1][-map[i + 1][j + 1] - 1].Pro);
			}
			if (map[i + 1][j] < 0)                             //�ж��ҷ�������ɫ����
			{
				thread23 += (chess[1][-map[i + 1][j] - 1].value) * (chess[1][-map[i + 1][j] - 1].value);
			}
			if (thread21 >= thread22 && thread21 > thread23)         //�Ƚ�
			{ 
				thread2 = thread21;
			}
			if (thread22 >= thread21 && thread22 > thread23)         //�Ƚ�
			{
				thread2 = thread22;
			}
			if (thread23 >= thread22 && thread23 > thread21)         //�Ƚ�
			{
				thread2 = thread23;
			}
		}
	}



	if (MO == 0)                               //����
	{	
		if (i == 0 && j == 0)                  //����
		{
			thread2 += 0;
		}
		if (i == 0 && j > 0)                   //�߽�
		{
			if (map[i][j - 1] > 0)
			{
				thread2 += (chess[0][map[i][j - 1] - 1].value) * (chess[0][map[i][j - 1] - 1].Pro);
			}
		}
		if (j == 0 && i > 0)                   //�߽�
		{
			if (map[i - 1][j] > 0)
			{
				thread2 += (chess[0][map[i - 1][j] - 1].value) * (chess[0][map[i - 1][j] - 1].Pro);
			}
		}
		if (i > 0 && j > 0)                    //�Ǳ߽�
		{
			if (map[i][j - 1] > 0)             //�ж��Ϸ����޺�ɫ����
			{
				thread21 += (chess[0][map[i][j - 1] - 1].value) * (chess[0][map[i][j - 1] - 1].Pro);
			}
			if (map[i - 1][j - 1] > 0)             //�ж����Ϸ����޺�ɫ����
			{
				thread22 += (chess[0][map[i - 1][j - 1] - 1].value) * (chess[0][map[i - 1][j - 1] - 1].Pro);
			}
			if (map[i - 1][j] > 0)             //�ж������޺�ɫ����
			{
				thread23 += (chess[0][map[i - 1][j] - 1].value) * (chess[0][map[i - 1][j] - 1].Pro);
			}
			if (thread21 >= thread22 && thread21 > thread23)           //�Ƚ�
			{ 
				thread2 = thread21;
			} 
			if (thread22 >= thread21 && thread22 > thread23)           //�Ƚ�
			{
				thread2 = thread22;
			}
			if (thread23 >= thread22 && thread23 > thread21)           //�Ƚ�
			{
				thread2 = thread23;
			}
		}
	}
	printf("����thread2=%f", thread2);
	return thread2;
}




 
void  GetBestMove(Chess chess[2][6],int i,int j,int q)
{

			int valuemap1[5][5] = { 0,1,1,1,1,1,2,2,2,3,1,2,4,4,6,1,2,4,8,12,1,3,6,12,100 };
			int valuemap2[5][5] = { 100,12,6,3,1,12,8,4,2,1,6,4,4,2,1,3,2,2,2,1,1,1,1,1,0 };
			double v=-1000, value;
			double exp1, exp2, thread1, thread2;
			if (MO == 1)                                 //�췽�ƶ�
			{
				double value1 = -1000, value2 = -1000, value3 = -1000;
				if (j < 4)                               //�ж��ܷ������ƶ�
				{
					Chess chess1[2][6];                  //����һ����
						for (int J = 0; J < 6; J++)
						{
							chess1[0][J] = chess[0][J]; 
							chess1[0][J].value = valuemap1[chess1[0][J].P.x][chess1[0][J].P.y];
							
						}
						for (int J = 0; J < 6; J++)      //�����Ӹ���valueֵ
						{
							chess1[1][J] = chess[1][J];
							chess1[1][J].value = valuemap2[chess1[1][J].P.x][chess1[1][J].P.y];
						}
					int num=0;
					if (map[i][j + 1] > 0)               //�ж���ɫΪ��ɫ
					{
						num = map[i][j + 1] - 1;         //��ȡ��������ֵ
						chess1[0][num].bl = 0;           //��������
						chess1[0][num].Pro = 0;          //��������
						chess1[0][num].move = 0;         //�ƶ�����
					}
					if (map[i][j + 1] < 0)               //�ж���ɫΪ��ɫ
					{
						num = -map[i][j + 1] - 1;        //��ȡ��������ֵ
						chess1[1][num].bl = 0;           //��������
						chess1[1][num].Pro = 0;          //��������
						chess1[1][num].move = 0;         //�ƶ�����
					}
					chess1[!MO][q].P.x = i;              //ģ�������ƶ�
					chess1[!MO][q].P.y = j + 1;
					chess1[!MO][q].value = valuemap1[i][j + 1];                 //ģ�������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)                               //������������
					{
						exp1 += (chess1[0][num].value) * (chess1[0][num].Pro);
						exp2 += (chess1[1][num].value) * (chess1[1][num].Pro);
						thread1 += Thread1(chess1, chess1[0][num].P.x, chess1[0][num].P.y);
						thread2 += Thread2(chess1, chess1[0][num].P.x, chess1[0][num].P.y);
					}
					value1 = exp1 - exp2 + 1 * thread1 - 1 * thread2;           //����ģ�������ƶ��������ֵ
				}
				if (i < 4 && j < 4)                      //�ж��ܷ��������ƶ�
				{
					Chess chess2[2][6];                  //����һ����
					for (int J = 0; J < 6; J++)          
					{
						chess2[0][J] = chess[0][J];
						chess2[0][J].value = valuemap1[chess2[0][J].P.x][chess2[0][J].P.y];
					}
					for (int J = 0; J < 6; J++)          //�����Ӹ���valueֵ
					{
						chess2[1][J] = chess[1][J];
						chess2[1][J].value = valuemap2[chess2[1][J].P.x][chess2[1][J].P.y];
					}
					int num;
					if (map[i + 1][j + 1] > 0)           //�ж���ɫΪ��ɫ
					{
						num = map[i + 1][j + 1] - 1;     //��ȡ��������ֵ
						chess2[0][num].bl = 0;           //��������
						chess2[0][num].Pro = 0;          //��������
						chess2[0][num].move = 0;         //�ƶ�����
					}
					if (map[i + 1][j + 1] < 0)           //�ж���ɫΪ��ɫ
					{
						num = -map[i + 1][j + 1] - 1;    //��ȡ��������ֵ
						chess2[1][num].bl = 0;           //��������
						chess2[1][num].Pro = 0;          //��������
						chess2[1][num].move = 0;         //�ƶ�����
					}
					chess2[!MO][q].P.x = i + 1;          //ģ���������ƶ�
					chess2[!MO][q].P.y = j + 1;
					chess2[!MO][q].value = valuemap1[i + 1][j + 1];             //ģ���������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)                               //������������
					{
						exp1 += (chess2[0][num].value) * (chess2[0][num].Pro);
						exp2 += (chess2[1][num].value) * (chess2[1][num].Pro);
						thread1 += Thread1(chess2, chess2[0][num].P.x, chess2[0][num].P.y);
						thread2 += Thread2(chess2, chess2[0][num].P.x, chess2[0][num].P.y);
					}
					value2 = exp1 - exp2 + 1 * thread1 - 1 * thread2;            //����ģ���������ƶ��������ֵ
				}

				if (i < 4)                               //�ж��ܷ������ƶ�
				{
					Chess chess3[2][6];                  //����һ����
					for (int J = 0; J < 6; J++)
					{
						chess3[0][J] = chess[0][J];
						chess3[0][J].value = valuemap1[chess3[0][J].P.x][chess3[0][J].P.y];
					}
					for (int J = 0; J < 6; J++)          //�����Ӹ���valueֵ
					{
						chess3[1][J] = chess[1][J];
						chess3[1][J].value = valuemap2[chess3[1][J].P.x][chess3[1][J].P.y];
					}
					int num;
					if (map[i + 1][j] > 0)               //�ж���ɫ��ɫ
					{
						num = map[i + 1][j] - 1;         //��ȡ��������ֵ
						chess3[0][num].bl = 0;           //��������
						chess3[0][num].Pro = 0;          //��������
						chess3[0][num].move = 0;         //�ƶ�����
					}
					if (map[i + 1][j] < 0)               //�ж���ɫΪ��ɫ
					{
						num = -map[i + 1][j] - 1;        //��ȡ��������ֵ
						chess3[1][num].bl = 0;           //��������
						chess3[1][num].Pro = 0;          //��������
						chess3[1][num].move = 0;         //�ƶ�����
					}
					chess3[!MO][q].P.x = i + 1;          //ģ�������ƶ�
					chess3[!MO][q].P.y = j;
					chess3[!MO][q].value = valuemap1[i + 1][j];                //ģ�������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)                              //������������
					{
						exp1 += (chess3[0][num].value) * (chess3[0][num].Pro);
						exp2 += (chess3[1][num].value) * (chess3[1][num].Pro);
						thread1 += Thread1(chess3, chess3[0][num].P.x, chess3[0][num].P.y);
						thread2 += Thread2(chess3, chess3[0][num].P.x, chess3[0][num].P.y);
					}
					value3 = exp1 - exp2 + 1 * thread1 - 1 * thread2;          //����ģ�������ƶ��������ֵ
				}
				
				if (value2 <= value1 && value3 <= value1)//�����ƶ�value��󣬸�������value��nextֵ
				{
					v = value1;
					chess[!MO][q].next = 1;
					chess[!MO][q].v = value1;
				}
				if (value2 >= value1 && value2 >= value3)//�������ƶ�value��󣬸�������value��nextֵ
				{
					v = value2;
					chess[!MO][q].next = 2;
					chess[!MO][q].v = value2;
				}
				if (value3 >= value1 && value3 >= value2)//�����ƶ�value��󣬸�������value��nextֵ
				{
					v = value3;
					chess[!MO][q].next = 3; 
					chess[!MO][q].v = value3;

				}

			}
			if (MO == 0)//�����ƶ�
			{
				double value1=-1000, value2=-1000, value3=-1000;
				if (j > 0)                               //�ж��ܷ������ƶ�
				{
					Chess chess4[2][6];                  //����һ����
					for (int J = 0; J < 6; J++)
					{
						chess4[0][J] = chess[0][J];
						chess4[0][J].value = valuemap1[chess4[0][J].P.x][chess4[0][J].P.y];
					}
					for (int J = 0; J < 6; J++)          //�����Ӹ���valueֵ
					{
						chess4[1][J] = chess[1][J];
						chess4[1][J].value = valuemap2[chess4[1][J].P.x][chess4[1][J].P.y];
					}
					int num;
					if (map[i][j - 1] > 0)               //�ж���ɫΪ��ɫ
					{
						num = map[i][j - 1] - 1;         //��ȡ��������ֵ
						chess4[0][num].bl = 0;           //��������
						chess4[0][num].Pro = 0;          //��������
						chess4[0][num].move = 0;         //�ƶ�����
					}
					if (map[i][j - 1] < 0)               //�ж���ɫΪ��ɫ
					{
						num = -map[i][j - 1] - 1;        //��ȡ��������ֵ
						chess4[1][num].bl = 0;           //��������
						chess4[1][num].Pro = 0;          //��������
						chess4[1][num].move = 0;         //�ƶ�����
					}
					chess4[!MO][q].P.x = i;              //ģ�������ƶ�
					chess4[!MO][q].P.y = j - 1;
					chess4[!MO][q].value = valuemap2[i][j - 1];                 //ģ�������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)                               //������������
					{
						exp1 += (chess4[1][num].value) * (chess4[1][num].Pro); 
						exp2 += (chess4[0][num].value) * (chess4[0][num].Pro);
						thread1 += Thread1(chess4, chess4[1][num].P.x, chess4[1][num].P.y);
						thread2 += Thread2(chess4, chess4[1][num].P.x, chess4[1][num].P.y);
					}
					value1 = exp1 - exp2 + thread1 - thread2;                   //����ģ�������ƶ��������ֵ
				}
				if (i > 0 && j > 0)                       //�ж��ܷ��������ƶ�
				{
					Chess chess5[2][6];                   //����һ����
					for (int J = 0; J < 6; J++)
					{
						chess5[0][J] = chess[0][J];
						chess5[0][J].value = valuemap1[chess5[0][J].P.x][chess5[0][J].P.y];
					}
					for (int J = 0; J < 6; J++)           //�����Ӹ���valueֵ  
					{
						chess5[1][J] = chess[1][J];
						chess5[1][J].value = valuemap2[chess5[1][J].P.x][chess5[1][J].P.y];
					}
					int num = 0;
					if (map[i - 1][j - 1] > 0)            //�жϸ���ɫΪ��ɫ
					{
						num = map[i - 1][j - 1] - 1;      //��ȡ��������ֵ
						chess5[0][num].bl = 0;            //��������
						chess5[0][num].Pro = 0;           //��������
						chess5[0][num].move = 0;          //�ƶ�����
					}
					if (map[i - 1][j - 1] < 0)            //�жϸ�����Ϊ��ɫ
					{
						num = -map[i - 1][j - 1] - 1;     //��ȡ��������ֵ
						chess5[1][num].bl = 0;            //��������
						chess5[1][num].Pro = 0;           //��������
						chess5[1][num].move = 0;          //�ƶ�����
					}
					chess5[!MO][q].P.x = i - 1;           //ģ���������ƶ�
					chess5[!MO][q].P.y = j - 1;
					chess5[!MO][q].value = valuemap2[i - 1][j - 1];            //ģ���������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)                              //������������
					{
						exp1 += (chess5[1][num].value) * (chess5[1][num].Pro);
						exp2 += (chess5[0][num].value) * (chess5[0][num].Pro);
						thread1 += Thread1(chess5, chess5[1][num].P.x, chess5[1][num].P.y);
						thread2 += Thread2(chess5, chess5[1][num].P.x, chess5[1][num].P.y);
					}
					value2 = exp1 - exp2 + thread1 - thread2;                   //����ģ�������ƶ��������ֵ
				}
				if (i > 0)                                //�ж��ܷ������ƶ�
				{
					Chess chess6[2][6];                   //����һ����
					for (int J = 0; J < 6; J++)
					{
						chess6[0][J] = chess[0][J];
						chess6[0][J].value = valuemap1[chess6[0][J].P.x][chess6[0][J].P.y];
					}
					for (int J = 0; J < 6; J++)           //�����Ӹ���valueֵ  
					{
						chess6[1][J] = chess[1][J];
						chess6[1][J].value = valuemap2[chess6[1][J].P.x][chess6[1][J].P.y];
					}
					int num;
					if (map[i - 1][j] > 0)                //�жϸ�����Ϊ��ɫ
					{
						num = map[i - 1][j] - 1;          //��ȡ��������ֵ
						chess6[0][num].bl = 0;            //��������
						chess6[0][num].Pro = 0;           //��������
						chess6[0][num].move = 0;          //�ƶ�����
					}
					if (map[i - 1][j] < 0)                //�жϸ�����Ϊ��ɫ
					{
						num = -map[i - 1][j] - 1;         //��ȡ��������ֵ
						chess6[1][num].bl = 0;            //��������
						chess6[1][num].Pro = 0;           //��������
						chess6[1][num].move = 0;          //�ƶ�����
					}
					chess6[!MO][q].P.x = i - 1;           //ģ�������ƶ�
					chess6[!MO][q].P.y = j;
					chess6[!MO][q].value = valuemap2[i - 1][j];                //ģ�������ƶ���valueֵ�ı�
					exp1 = 0; exp2 = 0; thread1 = 0; thread2 = 0;
					for (num = 0; num < 6; num++)
					{
						exp1 += (chess6[1][num].value) * (chess6[1][num].Pro);
						exp2 += (chess6[0][num].value) * (chess6[0][num].Pro);
						thread1 += Thread1(chess6, chess6[1][num].P.x, chess6[1][num].P.y);
						thread2 += Thread2(chess6, chess6[1][num].P.x, chess6[1][num].P.y);
					}
					value3 = exp1 - exp2 + thread1 - thread2;                   //����ģ�������ƶ��������ֵ
				}
				
				if (value2 <= value1 && value3 <= value1)//�����ƶ�value��󣬸�������value��nextֵ
				{
					v = value1;
					chess[!MO][q].next = -1;
					chess[!MO][q].v = value1;
				}
				if (value2 >= value1 && value2 >= value3)//�������ƶ�value��󣬸�������value��nextֵ
				{
					v = value2;
					chess[!MO][q].next = -2;
					chess[!MO][q].v = value2;
				}
				if (value3 >= value1 && value3 >= value2)//�����ƶ�value��󣬸�������value��nextֵ
				{
					v = value3;
					chess[!MO][q].next = -3;
					chess[!MO][q].v = value3;
				}
			}
          

}


Fin ChooseBest(Chess chess[2][6])
{
	double Value = -1000;                        //�趨Ϊ������ֹΪ0����
	int fin = 0;
	Fin p;                                       //����p���洢��Ϣ
	p.x = 0;
	p.y = 0;
	p.fin = 0;
	for (int q = 0; q < 6; q++)
	{
		if (chess[!MO][q].move == 1)
		{
			
			GetBestMove(chess, chess[!MO][q].P.x, chess[!MO][q].P.y, q);            //ͨ���Ƚϻ�������ƶ����Ӻ��ƶ�����
			if (chess[!MO][q].v > Value) {
				fin = q;
				p.fin = q;
				p.x = chess[!MO][q].P.x;
				p.y = chess[!MO][q].P.y;
				Value = chess[!MO][q].v;
			}
			chess[!MO][q].v = 0;                                                    //��������
	
		}
	}
	if (chess[!MO][fin].next == 1)//�����ƶ�
	{
		p.x =p.x ;
		p.y = p.y+1;
	}
	if (chess[!MO][fin].next == 2)//�������ƶ�
	{
		p.x =p.x + 1;
		p.y =p.y + 1;
	}
	if (chess[!MO][fin].next == 3)//�����ƶ�
	{
		p.x =p.x+1;
		p.y =p.y ;
	}
	if (chess[!MO][fin].next == -1)//�����ƶ�
	{
		p.x = p.x ;
		p.y = p.y-1;
	}
	if (chess[!MO][fin].next == -2)//�������ƶ�
	{
		p.x = p.x - 1;
		p.y = p.y - 1;
	}
	if (chess[!MO][fin].next == -3)//�����ƶ�
	{
		p.x =p.x-1;
		p.y = p.y ;
	}
	return p;
}



void paff(Chess chess[2][6])     
{if (choose)
	{
		Fin P = ChooseBest(chess);
		chess[!MO][P.fin].MoveTo(chess[!MO][P.fin], P.x, P.y);
		prob(chess);
	}
}

