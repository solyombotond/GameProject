#include "Game.h"
#include "Labyrinth.h"

//Jatek kezdese:

void startGame(int level)
{
	switch (level) {
	case 1:
		initializeLevel("level1.txt", level);
		break;
	case 2:
		initializeLevel("level2.txt", level);
		break;
	case 3:
		initializeLevel("level3.txt", level);
		break;
	}
}

//Szint/palya inicializalasa:

void initializeLevel(const char * fileName, int level)
{
	FILE* file;
	file = fopen(fileName, "rt");
	if (file == NULL) {
		printf("Sikertelen allomany megnyitas!");
		exit(1);
	}
	Labyrinth* labyrinth = createAndReadLabyrinth(file);
	Player* player = createPlayer(1, 1);
	labyrinth->map[1][1] = 4;
	generateTreasures(labyrinth, 10);
	int timeAvailable = 60;  //max ido

	int levelDone = 0;
	
	time_t startTime = time(NULL);
	time_t endTime = time(NULL);

	while (endTime - startTime < timeAvailable && levelDone == 0) {
		printf("\n\nTIME AVAILABLE: %i sec\n", timeAvailable - (endTime-startTime));
		PrintLabyrinth(labyrinth, player);
		//moveY(1, player);
		levelDone = playerSteps(player, labyrinth);
		endTime = time(NULL);
		system("CLS");
		//Sleep(3);
	}
	if (levelDone == 1 && level < 3) {
		startGame(level + 1);
	}
	else if (levelDone != 1) {
		printf("Game Over!\n");
		printf("Time expired!\n");
	}
	else if (levelDone == 1 && level == 3) {
		printf("Well done! This game ended!\n");
	}

	fclose(file);
}

//Jatekos lepesei:

int playerSteps(Player* player, Labyrinth* labyrinth) {
	int levelIsDone = 0;
	char option = getch();
	switch (option) {
	case 'w':
		levelIsDone = updatePlayerPosition(labyrinth, player, -1, 'x');
		break;
	case 'a':
		levelIsDone = updatePlayerPosition(labyrinth, player, -1, 'y');
		break;
	case 's':
		levelIsDone = updatePlayerPosition(labyrinth, player, 1, 'x');
		break;
	case 'd':
		levelIsDone = updatePlayerPosition(labyrinth, player, 1, 'y');
		break;
	}
	return levelIsDone;
}