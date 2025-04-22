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
#include "camera.h"
#include "itemBox.h"
#include "exitPlace.h"
#include "mainmenu.h"
#include "obstacle.h"
#include "gun.h"
#include "minimab.h"


#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400


typedef struct gameManager {
	PLAYER player;
	ENEMY* enemies;
	int enemyCount;
	ITEM_BOX* item_Boxes;
	int itemCount;
	EXIT_PLACE exit_Place;
	OBSTACLE* obstacles;
	int obstacleCount;
	MAB map_Bounds;
	MINIMAB minimab;

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

int check_Collision_Player_Enemy(PLAYER* player, ENEMY* enemy); 

int check_Collision_Player_Item(PLAYER* player, ITEM_BOX* item_box);

int check_Is_Obstacle_In_Players_Sight(PLAYER* player, OBSTACLE* obstacles);

int check_Collision_Player_Obstacles(PLAYER* player, OBSTACLE* obstacles, int count_Obstacles);

int check_Collision_Player_Enter_Exit_Place(PLAYER* player, EXIT_PLACE* exit_Place);

int check_Collision_Enemy_Obstacles(ENEMY* enemy, OBSTACLE* obstacles, int count_Obstacles);

void check_Collsion_Bullet_Enemy(GUN* gun, ENEMY* enemy, int count_Enemy);

void check_Collsion_Bullet_Obstacles(GUN* gun, OBSTACLE* obstacles, int count_Obstacles);

void check_Player_Win(void);

void check_Player_Lose(PLAYER* player);
