#pragma once
#ifndef LABYRINTH_H
#define LABYRINTH_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#include "Player.h"

typedef struct{
	int** map;
	int length;
	int width;
}Labyrinth;

Labyrinth* createAndReadLabyrinth(FILE* file);
void PrintLabyrinth(Labyrinth* labyrinth, Player* player);
int updatePlayerPosition(Labyrinth* labyrinth, Player* player, int value, char direction);
void generateTreasures(Labyrinth* labyrinth, int numberOfTreasures);







#endif // !LABYRINTH_H
