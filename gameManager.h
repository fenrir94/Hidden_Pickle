#pragma once

/*
This is a header file about Game Manager Object.
Game Manager manages game objects such as player, enemies, map, and etc.

*/
#include <stdio.h>
#include <time.h>
#include "cprocessing.h"
#include "player.h"
#include "enemy.h"
#include "itemBox.h"



#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400


typedef struct gameManager {
	PLAYER player;
	ENEMY* enemies;
	int enemyCount;
	ITEM_BOX* item_Boxes;
	int itemCount;

	/*
	*
	* Map
	* Minimap
	* Camera
	* 
	*/
} GAME_MANAGER;

extern GAME_MANAGER game_Manager;

void init_Game_Manager(void);

void update_Game_Manager(void);

void print_GameObjects(GAME_MANAGER* gameManager);

void exit_Game_Manager(void);

int checkCollision_Player_Enemy(PLAYER* player, ENEMY* enemy); 

int checkCollision_Player_Item(PLAYER* player, ITEM_BOX* item_box);


