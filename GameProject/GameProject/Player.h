#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

//Jatekos struktura letrehozasa:
typedef struct {
	int x;
	int y;
	int points;
}Player;

//Jatekos letrehozasa:
Player* createPlayer(int x, int y);
//Az x-tengelyen(fuggoleges) valo mozgas:
void moveX(int value, Player* player);
//Az y-tengelyen(viszintes) valo mozgas:
void moveY(int value, Player* player);







#endif // !PLAYER_H
