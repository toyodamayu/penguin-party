#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>     
#include <ctime>        
#include <cstdlib>

int bord[10][15] =
{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,0} };

int Key[256];

int gpUpdateKey()
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{
			Key[i]++;
		}
		else
		{
			Key[i] = 0;
		}
	}

	return 0;
}

int card[36] = { 1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5 };

void hand(void);
int random(int min, int max);
void even(void);
void odd(void);
void vs(void);
void first(void);
int Max(int hand[14]);
int Min(int hand[14]);

int turn;
int max, min;
int big;

typedef struct player {
	char name[30];
	int attack;
	int hand[14];
}PLAYER;
PLAYER you;
PLAYER com;

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

	LoadGraphScreen(0, 0, "back.png", TRUE);
	ScreenFlip();

	hand();

	vs();
	first();

	even();
	odd();

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
	int YOU = 0;
	for (int i = 0; i < 10; i++)
	{
		int x = 30;
		for (int j = 0; j < 15; j++)
		{
			if (bord[i][j] == 2)
			{
				switch (you.hand[YOU])
				{
				case 1:
					LoadGraphScreen(x, y, "g.png", TRUE);
					ScreenFlip();
					YOU++;
					break;
				case 2:
					LoadGraphScreen(x, y, "b.png", TRUE);
					ScreenFlip();
					YOU++;
					break;
				case 3:
					LoadGraphScreen(x, y, "y.png", TRUE);
					ScreenFlip();
					YOU++;
					break;
				case 4:
					LoadGraphScreen(x, y, "r.png", TRUE);
					ScreenFlip();
					YOU++;
					break;
				case 5:
					LoadGraphScreen(x, y, "p.png", TRUE);
					ScreenFlip();
					YOU++;
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

void even(void)
{
	int y = 0;
	for (int i = 0; i < 10; i++)
	{
		int x = 30;
		for (int j = 0; j < 15; j++)
		{
			if (bord[i][j] == 1 && i % 2 == 0)
			{
				LoadGraphScreen(x, y, "option.png", TRUE);
				ScreenFlip();
			}
			x += 60;
		}
		y += 90;
	}
}

void odd(void)
{
	int y = 0;
	for (int i = 0; i < 10; i++)
	{
		int x = 0;
		for (int j = 0; j < 15; j++)
		{
			if (bord[i][j] == 1 && i % 2 == 1)
			{
				LoadGraphScreen(x, y, "option.png", TRUE);
				ScreenFlip();
			}
			x += 60;
		}
		y += 90;
	}
}

void vs(void)
{
	srand((unsigned int)time(NULL));
	you.attack = rand() % 10 + 1;

	if (you.attack % 2 == 0)
	{
		LoadGraphScreen(0, 0, "you.png", TRUE);
		ScreenFlip();
		turn = 0;
	}

	else
	{
		printf("æU:%s\n", com.name);
		turn = 1;
	}
}

void first(void)
{
	if (turn == 0)
	{
		int a;
		bord[7][7] = you.hand[a - 1];
		you.hand[a - 1] = 0;
		turn++;
	}
	else
	{
		max = Max(com.hand);
		for (int i = 0; i < 14; i++)
		{
			if (com.hand[i] == max)
			{
				bord[7][7] = com.hand[i];
				int x = 210, y = 240;
				switch (com.hand[i])
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
				com.hand[i] = 0;
				turn--;
				break;
			}
			else
			{
				continue;
			}
		}
	}
}

int Max(int hand[14])
{
	big = 0;
	int g = 0, b = 0, y = 0, r = 0, p = 0;
	int no;

	for (int i = 0; i < 14; i++)
	{
		if (hand[i] == 1)
		{
			g++;
		}
		else if (hand[i] == 2)
		{
			b++;
		}
		else if (hand[i] == 3)
		{
			y++;
		}
		else if (hand[i] == 4)
		{
			r++;
		}
		else if (hand[i] == 5)
		{
			p++;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (g > big)
		{
			big = g;
			no = 1;
		}
		else if (b > big)
		{
			big = b;
			no = 2;
		}
		else if (y > big)
		{
			big = y;
			no = 3;
		}
		else if (r > big)
		{
			big = r;
			no = 4;
		}
		else if (p > big)
		{
			big = p;
			no = 5;
		}
	}

	return no;
}

int Min(int hand[14])
{
	int min = 8;
	int g = 0, b = 0, y = 0, r = 0, p = 0;
	int no;

	for (int i = 0; i < 14; i++)
	{
		if (hand[i] == 1)
		{
			g++;
		}
		else if (hand[i] == 2)
		{
			b++;
		}
		else if (hand[i] == 3)
		{
			y++;
		}
		else if (hand[i] == 4)
		{
			r++;
		}
		else if (hand[i] == 5)
		{
			p++;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (g < min)
		{
			min = g;
			no = 1;
		}
		else if (b < min)
		{
			min = b;
			no = 2;
		}
		else if (y < min)
		{
			min = y;
			no = 3;
		}
		else if (r < min)
		{
			min = r;
			no = 4;
		}
		else if (p < min)
		{
			min = p;
			no = 5;
		}
	}

	return no;
}