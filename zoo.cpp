#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bord[10][15] =
{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,0} };

int card[36] = { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5 };

void hand(void);
int random(int min, int max);

typedef struct player {
	char name[30];
	int attack;
	int hand[14];
}PLAYER;
PLAYER you = { "���Ȃ�" };
PLAYER com = { "�R���s���[�^" };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(900, 900, 16);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	hand();

	WaitKey();
	DxLib_End();
	return 0;
}

void hand(void)
{
	for (int i = 35; i > 0; i--)
	{
		int tmp;
		int j = random(0, 35);
		if (i != j)
		{
			tmp = card[i];
			card[i] = card[j];
			card[j] = tmp;
		}
	}

	for (int i = 0; i < 14; i++)
	{
		you.hand[i] = card[i];
	}
	for (int i = 14; i < 28; i++)
	{
		com.hand[i - 14] = card[i];
	}

	int y = 0;
	for (int i = 0; i < 10; i++)
	{
		int x = 30;
		for (int j = 0; j < 15; j++)
		{
			if (bord[i][j] == 2)
			{
				switch (you.hand[j])
				{
				case 1:
					LoadGraphScreen(x, y, "g.png", TRUE);
					ScreenFlip();
					break;
				case 2:
					LoadGraphScreen(x, y, "b.png", TRUE);
					ScreenFlip();
					break;
				case 3:
					LoadGraphScreen(x, y, "y.png", TRUE);
					ScreenFlip();
					break;
				case 4:
					LoadGraphScreen(x, y, "r.png", TRUE);
					ScreenFlip();
					break;
				case 5:
					LoadGraphScreen(x, y, "p.png", TRUE);
					ScreenFlip();
					break;
				}
			}
			x += 60;
		}
		y += 90;
	}
}

int random(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}