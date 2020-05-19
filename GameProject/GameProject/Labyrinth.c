#include "Labyrinth.h"
#include "Game.h"

//Labirintus letrehozasa es beolvasasa file-bol:

Labyrinth * createAndReadLabyrinth(FILE * file)
{
	//Labirintusnak helyfoglalas:
	Labyrinth* labyrinth = (Labyrinth*)calloc(1, sizeof(Labyrinth));
	//ellenorzes
	if (labyrinth == NULL) {
		printf("Sikertelen helyfoglalas!");
	}

	//labirintus hosszanak es szelessegenek a beolvasasa filebol:
	fscanf(file, "%i%i", &labyrinth->length, &labyrinth->width);
	labyrinth->map = (int**)calloc(labyrinth->length, sizeof(int*));
	//ellenorzes
	if (labyrinth->map == NULL) {
		printf("Sikertelen helyfoglalas!");
	}
	//Helyfoglalas:
	for (int i = 0; i < labyrinth->length; i++) {
		labyrinth->map[i] = (int*)calloc(labyrinth->width, sizeof(int));
		//ellenorzes
		if (labyrinth->map[i] == NULL) {
			printf("Sikertelen helyfoglalas!");
		}
	}
	//Beolvasas:
	for (int i = 0; i < labyrinth->length; i++) {
		for (int j = 0; j < labyrinth->width; j++) {
			fscanf(file, "%i", &labyrinth->map[i][j]);
		}
	}
	return labyrinth;
}

//Labirintus(=palya) kirajzolasa:

void PrintLabyrinth(Labyrinth * labyrinth, Player* player)
{
	printf("\n\n");
	printf("\n\n");
	printf(ANSI_COLOR_GREEN "SCORE: %i" ANSI_COLOR_RESET "\n", player->points);
	printf("\n\n");
	printf("\n\n");
	for (int i = 0; i < labyrinth->length; i++) {
		for (int j = 0; j < labyrinth->width; j++) {
			switch (labyrinth->map[i][j]) {
			case 0:
				printf("%3c", ' ');  //jarhato ut jelolese
				break;
			case 1:
				setlocale(LC_ALL, "");
				printf(ANSI_COLOR_RED "%3c" ANSI_COLOR_RESET, '—');  //falak jelolese
				break;
			case 2:
				printf(ANSI_COLOR_RED "%3c" ANSI_COLOR_RESET, '|');  //falak jelolese
				break;
			case 3:
				printf(ANSI_COLOR_GREEN "%3c" ANSI_COLOR_RESET, 'E');  //kijarat jelolese
				break;
			case 4:
				printf("%3c", 'P');  //jatekos jelolese
				break;
			case 5:
				printf(ANSI_COLOR_YELLOW "%3c" ANSI_COLOR_RESET, '*');  //kincsek jelolese
				break;
			case 6:
				printf(ANSI_COLOR_CYAN "%3c" ANSI_COLOR_RESET, '@');  //"szornyek" jelolese
				break;
			}
		}
		printf("\n\n");
	}
	printf(ANSI_COLOR_YELLOW "\n\n                        >>Collect all treasures!<<          " ANSI_COLOR_RESET "\n");
}

//Jatekos poziciojanak az allando frissitese:

int updatePlayerPosition(Labyrinth* labyrinth, Player* player, int value, char direction) {
	labyrinth->map[player->x][player->y] = 4;  //jatekos poziciojat a 4-es szam jeloli
	//ellenorzes
	switch (direction) {
	//Az x-tengelyen valo mozgatasa a jatekosnak:
	case 'x':
		//utvonal meghatarozasa, ahol mozoghat a jatekos:
		if (player->x + value > 0 && player->x + value < labyrinth->length) {
			int previousPositionX = player->x;
			int previousPositionY = player->y;
			if (labyrinth->map[player->x + value][player->y] == 0) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
			}
			//pontszamok novelese abban az esetben ha a jatekos kincset vesz fel:
			else if(labyrinth->map[player->x + value][player->y] == 5) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
				player->points += 10;  //score novelese
			}
			//annak az esetnek a kezelese, ha a jatekos a szornyel talalkozik:
			else if (labyrinth->map[player->x + value][player->y] == 6) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf(ANSI_COLOR_RED "\n\n\n>>>>>>>>>> Oh, no... You encountered an obstacle! <<<<<<<<<<" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED "\n\n       Would you like to play again? Press 'R'                   " ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED "\n\n       If you want to quit -> Press 'Q'                          " ANSI_COLOR_RESET);
				char option = getch();
				switch (option) {
				case 'r': startGame(1);
					break;
				case 'q': exit(1);
					break;
				}
				break;
			}
			//a kijaraton valo kozlekedes lehetosegenek a megoldasa:
			else if (labyrinth->map[player->x + value][player->y] == 3) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf(ANSI_COLOR_GREEN "\n---------> Total score: %i  <---------\n" ANSI_COLOR_RESET, player->points);
				printf(ANSI_COLOR_YELLOW"\n         > Congratulations! <        \n\n" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED                           ">>Press Enter to go to next level ...<<\n\n" ANSI_COLOR_RESET);
				getchar();
				//startGame(2); //meghivom a masodik palyat
				return 1;
			}
		}
		return 0;
		break;
	//A jatekos y-on tengelyen valo mozgasanak a szabalyozasa:
	case 'y':
		//utvonal meghatarozasa, ahol mozoghat a jatekos:
		if (player->y + value > 0 && player->y + value < labyrinth->width) {
			int previousPositionX = player->x;
			int previousPositionY = player->y;
			if (labyrinth->map[player->x][player->y + value] == 0) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
			}
			//pontszamok novelese abban az esetben ha a jatekos kincset vesz fel:
			else if (labyrinth->map[player->x][player->y + value] == 5) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
				player->points += 10;  //score novelese
			}
			//annak az esetnek a kezelese, ha a jatekos a szornyel talalkozik:
			else if (labyrinth->map[player->x][player->y + value] == 6) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf(ANSI_COLOR_RED "\n\n\n>>>>>>>>>> Oh, no... You encountered an obstacle! <<<<<<<<<<" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED "\n\n       Would you like to play again? Press 'R'                   " ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED "\n\n       If you want to quit -> Press 'Q'                          " ANSI_COLOR_RESET);
				char option = getch();
				switch (option) {
				case 'r': startGame(1);
					break;
				case 'q': exit(1);
					break;
				}
				break;
			}
			//a kijaraton valo kozlekedes lehetosegenek a megoldasa:
			else if (labyrinth->map[player->x][player->y + value] == 3) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf(ANSI_COLOR_GREEN "\n---------> Total score: %i  <---------\n" ANSI_COLOR_RESET, player->points);
				printf(ANSI_COLOR_YELLOW "\n         > Congratulations! <        \n\n" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RED ">>Press Enter to go to next level ...<<\n\n" ANSI_COLOR_RESET);
				getchar();
				//startGame(2); //meghivom a masodik palyat
				return 1;
			}
		}
		return 0;
		break;
	}






	//for (int i = 0; i < labyrinth->length; i++) {
	//	for (int j = 0; j < labyrinth->width; j++) {
	//		if (player->x-1 == labyrinth->length || player->y-1 == labyrinth->width) {
	//			printf("Game Over!");
	//			exit(1);
	//		}
	//	}
	//}


	//int previousPositionX = labyrinth->map[player->x];
	//int previousPositionY = labyrinth->map[player->y];
	//if (labyrinth->map[player->x][player->y] == '0') {
	//	labyrinth->map[player->x][player->y] = 'P';
	//	labyrinth->map[previousPositionX][previousPositionY] = '0';
	//}
}

//A kincsek automatikus iigeneralasat megvalosito fuggveny:
void generateTreasures(Labyrinth * labyrinth, int numberOfTreasures)
{
	int count = 0;
	srand(time(NULL));
	while (count < numberOfTreasures) {
		int x = 1 + rand() % (labyrinth->length - 1);   //min + rand() % (max - min + 1) --> a random generalas keplete
		int y = 1 + rand() % (labyrinth->width - 1);   
		if (labyrinth->map[x][y] == 0) {
			labyrinth->map[x][y] = 5;
			count++;
		}
	}
}
