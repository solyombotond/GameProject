#include "Player.h"


//Jatekos letrehozasa:

Player* createPlayer(int x, int y) {

	Player* player = (Player*)calloc(1, sizeof(Player));  //helyfoglalas
	player->x = x;
	player->y = y;
	player->points = 0;  //0- kezdeti erteke a pontszamainak
	
	return player;
}

//Az x-tengelyen(fuggoleges) valo mozgas:

void moveX(int value, Player* player) {
	player->x += value;
}

//Az y-tengelyen(viszintes) valo mozgas:

void moveY(int value, Player* player) {
	player->y += value;
}