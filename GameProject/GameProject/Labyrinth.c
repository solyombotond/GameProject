#include "Labyrinth.h"

//Labirintus letrehozasa es beolvasasa file-bol:

Labyrinth * createAndReadLabyrinth(FILE * file)
{
	Labyrinth* labyrinth = (Labyrinth*)calloc(1, sizeof(Labyrinth));
	//ellenorzes
	if (labyrinth == NULL) {
		printf("Sikertelen helyfoglalas!");
	}

	fscanf(file, "%i%i", &labyrinth->length, &labyrinth->width);
	labyrinth->map = (int**)calloc(labyrinth->length, sizeof(int*));
	//ellenorzes
	if (labyrinth->map == NULL) {
		printf("Sikertelen helyfoglalas!");
	}

	for (int i = 0; i < labyrinth->length; i++) {
		labyrinth->map[i] = (int*)calloc(labyrinth->width, sizeof(int));
		//ellenorzes
		if (labyrinth->map[i] == NULL) {
			printf("Sikertelen helyfoglalas!");
		}
	}
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
	printf("SCORE: %i", player->points);
	printf("\n\n");
	printf("\n\n");
	for (int i = 0; i < labyrinth->length; i++) {
		for (int j = 0; j < labyrinth->width; j++) {
			switch (labyrinth->map[i][j]) {
			case 0:
				printf("%3c", ' ');
				break;
			case 1:
				setlocale(LC_ALL, "");
				printf("%3c", '—');
				break;
			case 2:
				printf("%3c", '|');
				break;
			case 3:
				printf("%3c", 'E');
				break;
			case 4:
				printf("%3c", 'P');
				break;
			case 5:
				printf("%3c", '*');
				break;
			}
		}
		printf("\n\n");
	}
}

//Jatekos poziciojanak az allando frissitese:

int updatePlayerPosition(Labyrinth* labyrinth, Player* player, int value, char direction) {
	labyrinth->map[player->x][player->y] = 4;
	//ellenorzes
	switch (direction) {
	case 'x':
		if (player->x + value > 0 && player->x + value < labyrinth->length) {
			int previousPositionX = player->x;
			int previousPositionY = player->y;
			if (labyrinth->map[player->x + value][player->y] == 0) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
			}
			else if(labyrinth->map[player->x + value][player->y] == 5) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
				player->points += 10;  //score novelese
			}
			else if (labyrinth->map[player->x + value][player->y] == 3) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveX(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf("Total score: %i\n", player->points);
				printf("Congratulations!\n\n");
				printf("Press Enter to go to next level ...!\n\n");
				getchar();
				//startGame(2); //meghivom a masodik palyat
				return 1;
			}
		}
		return 0;
		break;
	case 'y':
		if (player->y + value > 0 && player->y + value < labyrinth->width) {
			int previousPositionX = player->x;
			int previousPositionY = player->y;
			if (labyrinth->map[player->x][player->y + value] == 0) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
			}
			else if (labyrinth->map[player->x][player->y + value] == 5) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
				player->points += 10;  //score novelese
			}
			else if (labyrinth->map[player->x][player->y + value] == 3) {
				labyrinth->map[previousPositionX][previousPositionY] = 0;
				moveY(value, player);
				labyrinth->map[player->x][player->y] = 4;
				Sleep(3);
				system("CLS");
				printf("Total score: %i\n", player->points);
				printf("Congratulations!\n\n");
				printf("Press Enter to go to next level ...!\n\n");
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

void generateTreasures(Labyrinth * labyrinth, int numberOfTreasures)
{
	int count = 0;
	srand(time(NULL));
	while (count < numberOfTreasures) {
		int x = 1 + rand() % (labyrinth->length - 1);   //min + rand() % (max - min + 1)
		int y = 1 + rand() % (labyrinth->width - 1);   
		if (labyrinth->map[x][y] == 0) {
			labyrinth->map[x][y] = 5;
			count++;
		}
	}
}
