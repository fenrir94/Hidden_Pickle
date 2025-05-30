#pragma once

/*
This is a header file about Game Manager Object.
Game Manager manages game objects such as player, enemies, map, and etc.

*/
#include <stdio.h>
#include <time.h>
#include "cprocessing.h"
#include "imageManager.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "itemBox.h"
#include "exitPlace.h"
#include "mainmenu.h"
#include "obstacle.h"
#include "gun.h"
#include "minimap.h"
#include "background.h"
#include "light.h"
#include "resultScreen.h"


#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400

typedef enum gameState {
	GAME_STATE_PLAYING,
	GAME_STATE_PAUSE,
	GAME_STATE_WIN,
	GAME_STATE_LOSE
} EgameState;

typedef struct gameManager {
	PLAYER player;
	ENEMY* enemies;
	int enemyCount;
	ITEM_BOX* item_Boxes;
	int itemCount;
	EXIT_PLACE exit_Place;
	OBSTACLE* obstacles;
	int obstacleCount;
	MAP map_Bounds;
	MINIMAP minimap;
	BACKGROUND background;
	LIGHT light;
	RESULT_SCREEN result_Screen;
	EgameState game_State;
} GAME_MANAGER;

extern GAME_MANAGER game_Manager;

void init_Game_Manager(void);

void update_Game_Manager(void);

void print_GameObjects(GAME_MANAGER* gameManager);

void exit_Game_Manager(void);

int check_Collision_Player_Enemy(PLAYER* player, ENEMY* enemy); 

int check_Collision_Player_Item(PLAYER* player, ITEM_BOX* item_box);

int check_Is_Obstacle_In_Players_Sight(PLAYER* player, OBSTACLE* obstacles);

void check_Collision_Rollback_Player_Obstacles(PLAYER* player, OBSTACLE* obstacles, int count_Obstacles, CP_Vector input, float dt);

int check_Collision_Player_Obstacles(PLAYER* player, OBSTACLE* obstacles, int count_Obstacles);

int check_Collision_Player_Enter_Exit_Place(PLAYER* player, EXIT_PLACE* exit_Place);

int check_Collision_Enemy_Obstacles(ENEMY* enemy, OBSTACLE* obstacles, int count_Obstacles);

void check_Collsion_Bullet_Enemy(GUN* gun, ENEMY* enemy, int count_Enemy);

void check_Collsion_Bullet_Obstacles(GUN* gun, OBSTACLE* obstacles, int count_Obstacles);

int check_Player_Win(void);

int check_Player_Lose(PLAYER* player);

