#include<stdio.h>
#include<easyx.h>
#include<time.h>
#include<iostream>//ws
#include<graphics.h>//ws

#include<ctime>
#include <random>//�����

#include<stdio.h>//��ý��
#include<Windows.h>//��ý��
#include<mmsystem.h>//��ý���ļ�
#pragma comment(lib,"winmm.lib")//��ý��

#define GRID_W 70    //���ӵĿ��
#define INTERVAL 70  //��϶��С
#define ROW 5
#define COL 5

int s = 0;//�����

bool sign1 = false;
bool sign2 = false;
bool sign3 = false;
bool sign4 = false;
bool vocal = false;

//����
bool playBackgroundMusic(bool vocal, const char* music)
{
	if (vocal)
	{
		char cmd[100] = { 0 };
		sprintf_s(cmd, "open %s alias bgm", music);
		MCIERROR ret = mciSendString(cmd, NULL, 0, NULL);
		if (ret != 0)
		{
			char err[100] = { 0 };
			mciGetErrorString(ret, err, sizeof(err));
			printf("[open]:%s", err);
		}
		mciSendString("play bgm", NULL, 0, NULL);
	}
	else
	{
		char cmd[100] = { 0 };
		sprintf_s(cmd, "close %s alias bgm", music);
		MCIERROR ret = mciSendString(cmd, NULL, 0, NULL);
		if (ret != 0)
		{
			char err[100] = { 0 };
			mciGetErrorString(ret, err, sizeof(err));
			// printf("[close]:%s", err);  
		}
		mciSendString("close bgm", NULL, 0, NULL);
	}

	return true;
}

//�ж����λ��
bool inArea(int mx, int my, int x, int y, int w, int h)
{

	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}
//�жϰ�ť�Ƿ񱻵��
bool buttont(ExMessage msg, int x, int y, int w, int h)
{

	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}
//�ж����Ƿ��ڷ�Χ
int numbers(ExMessage msg, int x, int y, int w, int h)
{
	if (msg.x <= GRID_W * 6 && msg.x >= GRID_W && msg.y <= GRID_W * 6 && msg.y >= GRID_W && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}


bool button(ExMessage msg, int x, int y, int w, int h, const char* text)  //dk
{  

    int rx = x;  
    int ry = y;  
    int rw = w;  
    int rh = h;  
  
    settextcolor(WHITE);  
    setbkmode(TRANSPARENT);  
    settextstyle(27, 0, "Small Fonts");  
  
    // ����ڰ�ť�����ڣ����ͣ���ڰ�ť�ϣ�  
    if (inArea(msg.x, msg.y, x, y, w, h))  
    {  
       
        setlinecolor(LIGHTGRAY);  
        roundrect(rx, ry, rx + rw, ry + rh, 5, 5);  
        setlinecolor(LIGHTGRAY);  
        setlinestyle(PS_SOLID, 8);  
        roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);  
        setlinecolor(WHITE);  
        setlinestyle(PS_SOLID, 5);  
        roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);  
        setfillcolor(RGB(0, 164, 255));  
        solidroundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);  

        int gao = (rw - textwidth(text)) / 2;  
        int kuan = (rh - textheight(text)) / 2;  
        outtextxy(rx + gao + 2, ry + kuan + 2, text);  
    }  
	else//���δͣ���ڰ�ť��
	{
		//��ť
		setlinecolor(DARKGRAY);
		setlinestyle(PS_SOLID, 8);
		roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);//��Ӱ���ƶ���
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 5);
		roundrect(rx, ry, rx + rw, ry + rh, 5, 5);//��ť�߿�Բ�Ǿ��Σ�
		setfillcolor(RGB(0, 164, 255));
		solidroundrect(rx, ry, rx + rw, ry + rh, 5, 5);//��ť���

		//����
		int gao = (rw - textwidth(text)) / 2;
		int kuan = (rh - textheight(text)) / 2;
		outtextxy(rx + gao, ry + kuan, text);
	}

	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}


void RedVictory()//ʤ������
{
	//��ͼ
	setlinestyle(PS_SOLID, 8);
	setlinecolor(BLACK);
	roundrect(200, 200, 700, 370, 15, 15);//�������� Բ��ˮƽ�ʹ�ֱ�뾶
	setfillcolor(RGB(246, 255, 86));
	solidroundrect(200, 200, 700, 370, 15, 15);//�����Σ��ޱ߿�
	//����
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, "GOTHIC_FONT");//����߶ȡ������ȣ�0��������Ӧ������������
	outtextxy(220, 250, "Red Square Win!");//���������Լ�������Ϣ

}
void BlueVictory()//ʤ������
{
	//��ͼ
	setlinestyle(PS_SOLID, 8);
	setlinecolor(BLACK);
	roundrect(200, 200, 700, 370, 15, 15);//�������� Բ��ˮƽ�ʹ�ֱ�뾶
	setfillcolor(RGB(246, 255, 86));
	solidroundrect(200, 200, 700, 370, 15, 15);//�����Σ��ޱ߿�
	//����
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, "GOTHIC_FONT");//����߶ȡ������ȣ�0��������Ӧ������������	
	outtextxy(220, 250, "Blue Square Win!");//���������Լ�������Ϣ

}
void GameEnds()
{
	//��ͼ
	setlinestyle(PS_SOLID, 8);
	setlinecolor(BLACK);
	roundrect(200, 200, 700, 370, 15, 15);
	setfillcolor(RGB(246, 255, 86));
	solidroundrect(200, 200, 700, 370, 15, 15);
	//����
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, "GOTHIC_FONT");
	outtextxy(220, 250, "  Game  Over!");

}

void side(bool sign, int x, int y, int w, int h, const char* text)//�任���巽 ��ɫ
{
	//��ťͼ��
	int rx = x;
	int ry = y;
	int rw = w;
	int rh = h;

	//������ɫ
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	settextstyle(27, 0, "Small Fonts");
	//���Ч��
	if (sign)
	{
		setlinecolor(LIGHTGRAY);
		roundrect(rx, ry, rx + rw, ry + rh, 5, 5);//Ĩȥԭ�л�ɫ�߿�
		setlinecolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 8);
		roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);//Ĩȥ��Ӱ
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 5);
		roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);//���º�ť�İ�ɫ�߿�
		setfillcolor(RGB(255, 151, 151));//��
		solidroundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);//��䰴ť

		//����
		int gao = (rw - textwidth(text)) / 2;
		int kuan = (rh - textheight(text)) / 2;
		outtextxy(rx + gao + 2, ry + kuan + 2, text);
	}
	else
	{
		//��ť
		setlinecolor(DARKGRAY);
		setlinestyle(PS_SOLID, 8);
		roundrect(rx + 2, ry + 2, rx + rw + 2, ry + rh + 2, 5, 5);//��Ӱ���ƶ���
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 5);
		roundrect(rx, ry, rx + rw, ry + rh, 5, 5);//��ť�߿�Բ�Ǿ��Σ�
		setfillcolor(RGB(0, 0, 0));//��
		solidroundrect(rx, ry, rx + rw, ry + rh, 5, 5);//��ť���

		//����
		int gao = (rw - textwidth(text)) / 2;
		int kuan = (rh - textheight(text)) / 2;
		outtextxy(rx + gao, ry + kuan, text);
	}
	

}
bool sides(bool sign)//�任���巽 ����
{
	if (sign)
	{
		side(true, 455, 90, 125, 50, "Red Square");
		side(false, 455, 230, 125, 50, "Blue Square ");
	}
	else
	{
		side(true, 455, 230, 125, 50, "Blue Square ");
		side(false, 455, 90, 125, 50, "Red Square");
	}
	return true;
}

//�����
int Num(ExMessage msg)
{
	if (buttont(msg, 70 + 7 * 1, 460, 50, 50))
	{
		printf("1\n");
		return 1;
	}

	if (buttont(msg, 70 + 7 * 2 + 50 * 1, 460, 50, 50))
	{
		printf("2\n");
		return 2;
	}

	if (buttont(msg, 70 + 7 * 3 + 50 * 2, 460, 50, 50))
	{
		printf("3\n");
		return 3;
	}

	if (buttont(msg, 70 + 7 * 4 + 50 * 3, 460, 50, 50))
	{
		printf("4\n");
		return 4;
	}

	if (buttont(msg, 70 + 7 * 5 + 50 * 4, 460, 50, 50))
	{
		printf("5\n");
		return 5;
	}

	if (buttont(msg, 70 + 7 * 6 + 50 * 5, 460, 50, 50))
	{
		printf("6\n");
		return 6;
	}
	return 0;
}
//1,3��ʾ���ԣ�2��4��ʾ���
int ComputerMan(int m)
{
	if (sign1 && m)
	{
		return 1;
	}
	else if (sign2 && m)
	{
		return 2;
	}

	if (sign3 && !m)
	{
		return 3;
	}
	else if (sign4 && !m)
	{
		return 4;
	}
}


//�����������
void UII(ExMessage msg, bool& gamestart, bool& red, bool& blue)
{

	//���̰�ɫ���
	setfillcolor(WHITE);
	solidrectangle(70, 70, 420, 420);

	//���̸�
	setfillcolor(BLACK);
	solidrectangle(GRID_W * 2, GRID_W, GRID_W * 3, GRID_W * 2);
	solidrectangle(GRID_W * 4, GRID_W, GRID_W * 5, GRID_W * 2);
	solidrectangle(GRID_W, GRID_W * 2, GRID_W * 2, GRID_W * 3);
	solidrectangle(GRID_W * 3, GRID_W * 2, GRID_W * 4, GRID_W * 3);
	solidrectangle(GRID_W * 5, GRID_W * 2, GRID_W * 6, GRID_W * 3);
	solidrectangle(GRID_W * 2, GRID_W * 3, GRID_W * 3, GRID_W * 4);
	solidrectangle(GRID_W * 4, GRID_W * 3, GRID_W * 5, GRID_W * 4);
	solidrectangle(GRID_W, GRID_W * 4, GRID_W * 2, GRID_W * 5);
	solidrectangle(GRID_W * 3, GRID_W * 4, GRID_W * 4, GRID_W * 5);
	solidrectangle(GRID_W * 5, GRID_W * 4, GRID_W * 6, GRID_W * 5);
	solidrectangle(GRID_W * 2, GRID_W * 5, GRID_W * 3, GRID_W * 6);
	solidrectangle(GRID_W * 4, GRID_W * 5, GRID_W * 5, GRID_W * 6);

	//���̱߿�
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(70, 70, 420, 420);

	//���̻���
	line(GRID_W, GRID_W * 2, GRID_W * 6, GRID_W * 2);//��һ
	line(GRID_W, GRID_W * 3, GRID_W * 6, GRID_W * 3);//���
	line(GRID_W, GRID_W * 4, GRID_W * 6, GRID_W * 4);//����
	line(GRID_W, GRID_W * 5, GRID_W * 6, GRID_W * 5);//����
	line(GRID_W * 2, GRID_W, GRID_W * 2, GRID_W * 6);//��һ
	line(GRID_W * 3, GRID_W, GRID_W * 3, GRID_W * 6);//����
	line(GRID_W * 4, GRID_W, GRID_W * 4, GRID_W * 6);//����
	line(GRID_W * 5, GRID_W, GRID_W * 5, GRID_W * 6);//����

	// ����̨���(��)
	setfillcolor(LIGHTGRAY);
	fillrectangle(70, 440, 420, 530);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(70, 440, 420, 530);

	//����̨���(��)
	setfillcolor(LIGHTGRAY);
	fillrectangle(440, 70, 930, 530);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(440, 70, 930, 530);

	//���������λ��
	setfillcolor(BLACK);
	solidroundrect(675, 445, 725, 495, 7, 7);

	//�������ť�Լ����������-dk
		if (button(msg, 455, 445, 200, 50, "Random Number"))
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(1, 6);
			s = dis(gen);
			printf("%d", s);
		}
	if (s != 0)
	{
		char num[20];
		sprintf(num, "%d", s);
		setfillcolor(BLACK);
		solidroundrect(675, 445, 725, 495, 7, 7);
		settextcolor(WHITE); 
		settextstyle(55, 0, "Small Fonts");
		if (s == 1)
			outtextxy(688, 442, num);  
		else 
			outtextxy(685, 442, num); 
	}

	/************************************************************/ //ws
	//��Ϸ��ʼ�ж�
	if (button(msg, 455, 370, 125, 50, "start") && gamestart == false)
	{
		printf("start\n");
		gamestart = true;
		red = false;
		blue = false;
		msg.message = 0;
	}
	//���ְ�ť
	button(msg, 70 + 7 * 1, 460, 50, 50, "1");
	button(msg, 70 + 7 * 2 + 50 * 1, 460, 50, 50, "2");
	button(msg, 70 + 7 * 3 + 50 * 2, 460, 50, 50, "3");
	button(msg, 70 + 7 * 4 + 50 * 3, 460, 50, 50, "4");
	button(msg, 70 + 7 * 5 + 50 * 4, 460, 50, 50, "5");
	button(msg, 70 + 7 * 6 + 50 * 5, 460, 50, 50, "6");
	//������巽�ж�
	side(false, 455, 90, 125, 50, "Red Square");
	side(false, 455, 230, 125, 50, "Blue Square ");

	if (buttont(msg, 620, 90, 125, 50))
	{
		sign1 = true;
		sign2 = false;
	}
	else if (buttont(msg, 785, 90, 125, 50))
	{
		sign1=false;
		sign2=true;
	}
	if (buttont(msg, 620, 230, 125, 50))
	{
		sign3 = true;
		sign4 = false;
	}
	else if (buttont(msg, 785, 230, 125, 50))
	{
		sign3 = false;
		sign4 = true;
	}

	side(sign1, 620, 90, 125, 50, "computer");
	side(sign2, 785, 90, 125, 50, "player");
	side(sign3, 620, 230, 125, 50, "computer");
	side(sign4, 785, 230, 125, 50, "player");
	
	//�߶�
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	line(455, 360, 910, 360);
	//��������
	if (button(msg, 785, 370, 125, 50, "Music"))
	{
		printf("Music\n");
		if (vocal)
		{
			vocal = false;
		}
		else
		{
			vocal = true;
		}
		//Ŀǰ�赥��1.rise  2.sentive  3.supercell 4.YOU
		playBackgroundMusic(vocal, "backgroundMusic/YOU.mp3");//����
		mciSendString("setaudio bgm volume to 60", NULL, 0, NULL);//������Χ0-1000
		
	}
		
	//������ť
	if (button(msg, 620, 370, 125, 50, "Game ends"))
	{
		printf("Game ends\n");
		gamestart = false;
		red = true;
		blue = true;
		BeginBatchDraw();

		GameEnds();

		EndBatchDraw();
		Sleep(6000);//��ͣ��ʾ����
		
		//getchar();
	}



	/**************************************************************/

}
