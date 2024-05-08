#include<stdio.h>
#include<time.h>
#include"UI.h"
#include"AI.h"

void Redplayer(int& );                               //�췽����
void Blueplayer(int& );                              //��������
void movechess(bool , bool , bool );                 //�ƶ�����                                                                                                                                                                                                                                                                                                                                              
void block();                                        //�ƶ����ӵı�־

ExMessage msg = { 0 };                //������Ϣ�Ľṹ�����


//����ڶ�ά����map�ϵ�����
int mx()                            
{
	if (msg.x > INTERVAL)
	{
		if (msg.x < 2 * GRID_W)
			return 0;
		else if (msg.x < 3 * GRID_W)
			return 1;
		else if (msg.x < 4 * GRID_W)
			return 2;
		else if (msg.x < 5 * GRID_W)
			return 3;
		else if (msg.x < 6 * GRID_W)
			return 4;
	}

}
int my()
{
	if (msg.y > INTERVAL)
	{
		if (msg.y < 2 * GRID_W)
			return 0;
		else if (msg.y < 3 * GRID_W)
			return 1;
		else if (msg.y < 4 * GRID_W)
			return 2;
		else if (msg.y < 5 * GRID_W)
			return 3;
		else if (msg.y < 6 * GRID_W)
			return 4;
	}

}




void draw();
void show(bool&, bool&, bool&);
void movechess(bool , bool , bool );


//���ڿ��ӻ�

void  startup(bool& gamestart, bool& red, bool& blue)
{
	//����һ�����ڲ���˫����Ϣ����
	initgraph(1000, 600, EX_SHOWCONSOLE | EX_DBLCLKS);
	setbkcolor(RGB(251, 255, 200));
	cleardevice();
	if (!gamestart) {       //�����Ϸû�п�ʼ
		show(gamestart, red, blue);
	}

}




//�췽����
void Redplayer(int& j)
{
	if (buttont(msg, GRID_W, GRID_W, 5 * GRID_W, 5 * GRID_W))
	{
		chess[0][j].num = j + 1;
		chess[0][j].color = 0;
		chess[0][j].Pro = 1.0 / 6.0;
		chess[0][j].move = 0;
		//if (chess[0][j - 1].bl && j != 0)
		//	printf("   %d   %d    %d", chess[0][j - 1].P.x, chess[0][j].P.y, chess[0][j - 1].color);
		if (buttont(msg, 1 * GRID_W, 1 * GRID_W, GRID_W, GRID_W) && map[0][0] == 0)
		{
			map[0][0] = j + 1;
			chess[0][j].P.x = 0;
			chess[0][j].P.y = 0;
			chess[0][j].bl = 1;
			++j;
		}
		if (buttont(msg, 2 * GRID_W, 1 * GRID_W, GRID_W, GRID_W) && map[1][0] == 0)
		{
			map[1][0] = j + 1;
			chess[0][j].P.x = 1;
			chess[0][j].P.y = 0;
			chess[0][j].bl = 1;
			++j;
		}
		if (buttont(msg, 1 * GRID_W, 2 * GRID_W, GRID_W, GRID_W) && map[0][1] == 0)
		{
			map[0][1] = j + 1;
			chess[0][j].P.x = 0;
			chess[0][j].P.y = 1;
			chess[0][j].bl = 1;
			++j;
		}
		if (buttont(msg, 1 * GRID_W, 3 * GRID_W, GRID_W, GRID_W) && map[0][2] == 0)
		{
			map[0][2] = j + 1;
			chess[0][j].P.x = 0;
			chess[0][j].P.y = 2;
			chess[0][j].bl = 1;
			++j;
		}
		if (buttont(msg, 3 * GRID_W, 1 * GRID_W, GRID_W, GRID_W) && map[2][0] == 0)
		{
			map[2][0] = j + 1;
			chess[0][j].P.x = 2;
			chess[0][j].P.y = 0;
			chess[0][j].bl = 1;
			++j;
		}
		if (buttont(msg, 2 * GRID_W, 2 * GRID_W, GRID_W, GRID_W) && map[1][1] == 0)
		{
			map[1][1] = j + 1;
			chess[0][j].P.x = 1;
			chess[0][j].P.y = 1;
			chess[0][j].bl = 1;
			++j;
		}

	}
}
//��������
void Blueplayer(int& j)
{
	if (buttont(msg, GRID_W, GRID_W, 5 * GRID_W, 5 * GRID_W))
	{
		chess[1][j].num = j + 1;
		chess[1][j].color = 1;
		chess[1][j].Pro = 1.0 / 6.0;
		chess[1][j].move = 0;
		if (buttont(msg, 5 * GRID_W, 5 * GRID_W, GRID_W, GRID_W) && map[4][4] == 0)
		{
			map[4][4] = -j - 1;
			chess[1][j].P.x = 4;
			chess[1][j].P.y = 4;
			chess[1][j].bl = 1;
			++j;
		}
		if (buttont(msg, 5 * GRID_W, 4 * GRID_W, GRID_W, GRID_W) && map[4][3] == 0)
		{
			map[4][3] = -j - 1;
			chess[1][j].P.x = 4;
			chess[1][j].P.y = 3;
			chess[1][j].bl = 1;
			++j;
		}
		if (buttont(msg, 4 * GRID_W, 5 * GRID_W, GRID_W, GRID_W) && map[3][4] == 0)
		{
			map[3][4] = -j - 1;
			chess[1][j].P.x = 3;
			chess[1][j].P.y = 4;
			chess[1][j].bl = 1;
			++j;
		}
		if (buttont(msg, 5 * GRID_W, 3 * GRID_W, GRID_W, GRID_W) && map[4][2] == 0)
		{
			map[4][2] = -j - 1;
			chess[1][j].P.x = 4;
			chess[1][j].P.y = 2;
			chess[1][j].bl = 1;
			++j;
		}
		if (buttont(msg, 3 * GRID_W, 5 * GRID_W, GRID_W, GRID_W) && map[2][4] == 0)
		{
			map[2][4] = -j - 1;
			chess[1][j].P.x = 2;
			chess[1][j].P.y = 4;
			chess[1][j].bl = 1;
			++j;
		}
		if (buttont(msg, 4 * GRID_W, 4 * GRID_W, GRID_W, GRID_W) && map[3][3] == 0)
		{
			map[3][3] = -j - 1;
			chess[1][j].P.x = 3;
			chess[1][j].P.y = 3;
			chess[1][j].bl = 1;
			++j;
		}
	}
}

void sign(bool gamestart, bool red, bool blue, ExMessage msg)                        //����ѡ�������Ϊ�������ϱ��
{
	if (blue && gamestart && red)
	{
		if (msg.message == WM_LBUTTONDOWN && buttont(msg, 70, 440, 420, 530))        //ѡ������
		{
			if (Num(msg))
			{
				int p = Num(msg) - 1;
				if (chess[!MO][p].bl)
					chess[!MO][p].move = 1;
				else
				{
					int t = 0;
					for (int i = p; i <= 5 && t == 0; i++)
						if (chess[!MO][i].bl)
						{
							chess[!MO][i].move = 1;
							t = 1;
						}
					t = 0;
					for (int i = p; i >= 0 && t == 0; i--)
						if (chess[!MO][i].bl)
						{
							chess[!MO][i].move = 1;
							t = 1;
						}
				}
			}
			int j = 0;
			for (int i = 0; i < 6; i++)
				j += chess[!MO][i].move;
			if (j > 2)
			{
				for (int k = 0; k <= 1; k++)
					for (int i = 0; i < 6; i++)
						chess[k][i].move = 0;
			}
			else if (j > 0 && j <= 2)
				choose = 1;
		}
	}
}




//����
void show(bool& gamestart, bool& red, bool& blue)
{
	peekmessage(&msg, EX_MOUSE | EX_KEY);

	BeginBatchDraw();

	cleardevice();

	

	//��������
	UII(msg, gamestart, red, blue);	



	if(gamestart)
		sides(MO);
	

	//Ϊ�ƶ��������ϱ�־
	sign(gamestart, red, blue, msg);
	//����־�������ϱ��ֳ���
	block();

	if (ComputerMan(MO) == 2 || ComputerMan(MO) == 4)
	{
		//����˫���ֱ�����
		if (!red && gamestart)
		{
			int j = 0;
			for (int i = 0; i < 6; i++)
			{
				j += chess[0][i].bl;
			}
			if (j < 6)
			{
				Redplayer(j);
			}
			else if (j == 6)
			{
				MO = 0;
				red = true;
			}
		}

		if (!blue && gamestart && red)
		{
			int j = 0;
			for (int i = 0; i < 6; i++)
			{
				j += chess[1][i].bl;
			}
			if (j < 6)
			{
				Blueplayer(j);
			}
			else if (j == 6)
			{
				MO = 1;
				blue = true;
			}
		}
		movechess(blue, gamestart, red);//�ƶ�����
	}

	 if (ComputerMan(MO) == 1 || ComputerMan(MO) == 3)
	{
		if (gamestart)
		{
			if (red && blue && choose)                  //�ƶ����� 
			{
				paff(chess);
				
			}
			else if(!red)                              //�ڷ�����
			{
				putr(red, chess, map,MO);
			}
			else if (red && !blue)
			{
				putb(blue, chess, map,MO);
			}
		}
	}


	 //�������Ӽ�������
	 draw();

	//����Ϣ��������Ϊ��
	msg.message = 0;

	int k = 0;
	//�ж�ʤ��
	if (blue && red && gamestart)
	{
		if(winner())
		k = 1;
	}
	
	EndBatchDraw();


	if(k==1)
		Sleep(6000);

}

//�������Ӽ�������
void draw()
{
	setbkmode(TRANSPARENT);
	for (int i = 0; i < 6; i++)
	{
		if (chess[0][i].bl)        //�췽
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			setfillcolor(RGB(255, 46, 46));
			fillcircle(chess[0][i].P.x * GRID_W + 105, chess[0][i].P.y * GRID_W + 105, 30);
			settextstyle(40, 0, "");
			settextcolor(BLACK);
			char str[5] = "";
			sprintf(str, "%d", chess[0][i].num);
			outtextxy(chess[0][i].P.x * GRID_W + 97, chess[0][i].P.y * GRID_W + 87, str);
		}
		if (chess[1][i].bl)         //����
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			setfillcolor(RGB(0, 164, 255));
			fillcircle(chess[1][i].P.x * GRID_W + 105, chess[1][i].P.y * GRID_W + 105, 30);
			settextstyle(40, 0, "");
			settextcolor(BLACK);
			char str[5] = "";
			sprintf(str, "%d", chess[1][i].num);
			outtextxy(chess[1][i].P.x * GRID_W + 97, chess[1][i].P.y * GRID_W + 87, str);
		}
		
	}
}
//�����ƶ���־������ɫ���߷����ʾ
void block()
{
	for (int i = 0; i < 6; i++)
	{
		if (chess[0][i].move == 1)           //�췽�ܹ����ƶ������ӳ��ַ�����Ϊ��־
		{
			setlinecolor(GREEN);
			setlinestyle(PS_DASHDOT, 2);
			rectangle(INTERVAL + chess[0][i].P.x * GRID_W + 5, INTERVAL + chess[0][i].P.y * GRID_W + 5, INTERVAL + (chess[0][i].P.x + 1) * GRID_W - 5, INTERVAL + (chess[0][i].P.y + 1) * GRID_W - 5);

		}

		if (chess[1][i].bl)
		{
			if (chess[1][i].move == 1)       //�����ܹ����ƶ������ӳ��ַ�����Ϊ��־
			{
				setlinecolor(GREEN);
				setlinestyle(PS_DASHDOT, 2);
				rectangle(INTERVAL + chess[1][i].P.x * GRID_W + 5, INTERVAL + chess[1][i].P.y * GRID_W + 5, INTERVAL + (chess[1][i].P.x + 1) * GRID_W - 5, INTERVAL + (chess[1][i].P.y + 1) * GRID_W - 5);

			}
		}
	}
}


//�ƶ�����
void movechess(bool blue, bool gamestart, bool red)
{
	if (blue && gamestart && red)
	{
		int j = 0;

		for (int i = 0; i < 6; i++)
			j += chess[!MO][i].move;


		if (j == 1)                                                                 //���ҽ���һ�������ƶ�
		{
			int m = !MO;
			int n = -1;
			for (int i = 0; i < 6; i++)
				if (chess[m][i].move == 1)
				{
					n = i;
				}
			if (msg.message == WM_LBUTTONDOWN && buttont(msg, GRID_W, GRID_W, 5 * GRID_W, 5 * GRID_W))
			{
				chess[m][n].MoveTo(chess[m][n], mx(), my());                       //�ƶ�
				chess[m][n].move = 0;
				choose = 0;
				prob(chess);
			}
		}
		else if (j == 2)                                                           //�����������ӿ����ƶ�ʱ
		{
			if (msg.message == WM_LBUTTONDOWN && buttont(msg, GRID_W, GRID_W, 5 * GRID_W, 5 * GRID_W))
			{
				for (int i = 0; i < 6; i++)
					chess[!MO][i].move = 0;
				if (map[mx()][my()] > 0 && MO)
				{
					chess[0][map[mx()][my()] - 1].move = 1;
				}

				if (map[mx()][my()] < 0 && !MO)
				{
					chess[1][-map[mx()][my()] - 1].move = 1;
				}
			}
		}
		else if (j > 2)
		{
			for (int k = 0; k <= 1; k++)
				for (int i = 0; i < 6; i++)
					chess[k][i].move = 0;
		}
	}
}