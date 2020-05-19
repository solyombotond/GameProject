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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//A labirintus struktura letrehozasa:
typedef struct{
	int** map;
	int length;
	int width;
}Labyrinth;

//Labirintus letrehozasa es beolvasasa file-bol:
Labyrinth* createAndReadLabyrinth(FILE* file);
//Labirintus(=palya) kirajzolasa:
void PrintLabyrinth(Labyrinth* labyrinth, Player* player);
//Jatekos poziciojanak az allando frissitese:
int updatePlayerPosition(Labyrinth* labyrinth, Player* player, int value, char direction);
//A kincsek automatikus iigeneralasat megvalosito fuggveny:
void generateTreasures(Labyrinth* labyrinth, int numberOfTreasures);







#endif // !LABYRINTH_H
