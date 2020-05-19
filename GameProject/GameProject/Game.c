#include "Game.h"
#include "Labyrinth.h"

//Jatek kezdese:

void startGame(int level)
{
	switch (level) {
	case 1:
		initializeLevel("level1.txt", level);  //elso palya beolvasasa allomanybol
		break;
	case 2:
		initializeLevel("level2.txt", level);  //masodik palya beolvasasa allomanybol
		break;
	case 3:
		initializeLevel("level3.txt", level);  //harmadik palya beolvasasa allomanybol
		break;
	}
}

//Szint/palya inicializalasa:

void initializeLevel(const char * fileName, int level)
{
	//Allomanybol valo beolvasas:
	FILE* file;
	file = fopen(fileName, "rt");
	if (file == NULL) {
		printf("Sikertelen allomany megnyitas!");
		exit(1);
	}
	Labyrinth* labyrinth = createAndReadLabyrinth(file);
	Player* player = createPlayer(1, 1);  //jatekos letrehozasa az (1, 1)- es poziciora
	labyrinth->map[1][1] = 4;
	generateTreasures(labyrinth, 60);  //kincsgeneralo fuggveny meghivasa
	int timeAvailable = 45;  //max ido(sec)

	int levelDone = 0;  //teljesitett palyak szamara letrehozott valtozo
	
	time_t startTime = time(NULL);
	time_t endTime = time(NULL);

	while (endTime - startTime < timeAvailable && levelDone == 0) {
		printf(ANSI_COLOR_RED "\n\nTIME AVAILABLE: %i sec\n" ANSI_COLOR_RESET "\n", timeAvailable - (endTime-startTime));  //ido szamlalo
		PrintLabyrinth(labyrinth, player);
		//moveY(1, player);
		levelDone = playerSteps(player, labyrinth);
		endTime = time(NULL);
		system("CLS");
		//Sleep(3);
	}
	//palya teljesiteset ellenorzo fuggveny:
	if (levelDone == 1 && level < 3) {
		startGame(level + 1);
	}
	else if (levelDone != 1) {
		printf(ANSI_COLOR_RED "\n\n---------> GAME OVER! :( <---------\n" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "\n\n        ^ Time expired! ^            \n\n" ANSI_COLOR_RESET);
	}
	//Amennyiben a palyakat sikerult teljesiteni es a kijaraton is kijutottunk:
	else if (levelDone == 1 && level == 3) {
		printf(ANSI_COLOR_GREEN "\n\n      >>  Well done! This game ended!  <<      \n\n" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "\n\n      >>  Press 'R' to Play Again!  <<      \n\n" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED "\n\n      >>  Press 'Q' to Quit!  <<      \n\n" ANSI_COLOR_RESET);
		char option = getch();
		switch (option) {
		case 'r': startGame(1);
			break;
		case 'q': exit(1);
			break;
		}
	}

	fclose(file);
}

//Jatekos lepesei:

int playerSteps(Player* player, Labyrinth* labyrinth) {
	int levelIsDone = 0;
	char option = getch();
	switch (option) {
	case 'w':
		levelIsDone = updatePlayerPosition(labyrinth, player, -1, 'x');  //felfele lepes
		break;
	case 'a':
		levelIsDone = updatePlayerPosition(labyrinth, player, -1, 'y');  //balra lepes
		break;
	case 's':
		levelIsDone = updatePlayerPosition(labyrinth, player, 1, 'x');  //lefele lepes
		break;
	case 'd':
		levelIsDone = updatePlayerPosition(labyrinth, player, 1, 'y');  //jobbra lepes
		break;
	}
	return levelIsDone;
}