#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
	int x;
	int y;
	int points;
}Player;

Player* createPlayer(int x, int y);
void moveX(int value, Player* player);
void moveY(int value, Player* player);







#endif // !PLAYER_H
