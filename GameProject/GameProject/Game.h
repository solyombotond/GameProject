#pragma once
#ifndef GAME_H
#define GAME_H
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
#include "Labyrinth.h"


//Jatek kezdese:
void startGame(int level);
//Szint/palya inicializalasa:
void initializeLevel(const char* fileName, int level);
//Jatekos lepesei:
int playerSteps(Player* player, Labyrinth* labyrinth);








#endif // !GAME_H
