#pragma once

/*
This is a header file about Game Manager Object.
Game Manager manages game objects such as player, enemies, map, and etc.

*/
#include <stdio.h>
#include "cprocessing.h"
#include "player.h"
#include "enemy.h"

typedef struct gameManager {
	PLAYER player;
	ENEMY* enemies;
	int enemyCount;

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

void update_Game_Manager(GAME_MANAGER* gameManager, CP_Vector updateVector, float dt);

void printGameObjects(GAME_MANAGER* gameManager);
