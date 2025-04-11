#pragma once

/*
This is a header file about Game Manager Object.
Game Manager manages game objects such as player, enemies, map, and etc.

*/
#include <stdio.h>
#include "cprocessing.h"
#include "player.h"


typedef struct gameManager {
	PLAYER player;
	/*
	* 
	* Enemy
	* Map
	* Minimap
	* Camera
	* item
	* 
	*/
} GAME_MANAGER;

void init_Game_Manager(GAME_MANAGER* gameManager);


void printGameObjects(GAME_MANAGER* gameManager);
