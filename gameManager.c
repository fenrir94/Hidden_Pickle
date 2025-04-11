
#include <stdio.h>
#include "cprocessing.h"
#include "gameManager.h"
#include <stdlib.h>
#include "utility.h"

GAME_MANAGER game_Manager;

void init_Game_Manager(GAME_MANAGER* gameManager)
{
	CP_Vector startPositionPlayer = CP_Vector_Set(800, 500);
	init_Player(&(gameManager->player), startPositionPlayer);

	gameManager->enemyCount = 3;

	CP_Vector* startPositionEnemies = (CP_Vector*)malloc(sizeof(CP_Vector)*gameManager->enemyCount);
	startPositionEnemies[0] = CP_Vector_Set(200, 200);
	startPositionEnemies[1] = CP_Vector_Set(1600, 200);
	startPositionEnemies[2] = CP_Vector_Set(800 , 400);

	CP_Vector* patrol1 = (CP_Vector*)malloc(2*sizeof(CP_Vector));
	patrol1[0] = CP_Vector_Set(200, 200);
	patrol1[1] = CP_Vector_Set(200, 600);

	CP_Vector* patrol2 = (CP_Vector*)malloc(2 * sizeof(CP_Vector));
	patrol2[0] = CP_Vector_Set(1600, 200);
	patrol2[1] = CP_Vector_Set(400, 200);

	CP_Vector* patrol3 = (CP_Vector*)malloc(2 * sizeof(CP_Vector));
	patrol3[0] = CP_Vector_Set(800, 400);
	patrol3[1] = CP_Vector_Set(500, 700);
	patrol3[2] = CP_Vector_Set(1200, 400);

	gameManager->enemies = (ENEMY*)malloc(gameManager->enemyCount * sizeof(ENEMY));
	init_Enemy_Patrol(gameManager->enemies, startPositionEnemies[0], patrol1, 2);
	init_Enemy_Patrol(gameManager->enemies+1, startPositionEnemies[1], patrol2, 2);
	init_Enemy_Patrol(gameManager->enemies+2, startPositionEnemies[2], patrol3, 3);
	//for (int i = 0; i < gameManager->enemyCount; i++) {
	//	init_Enemy((gameManager->enemies + i), startPositionEnemies[i]);
	//}
}

// Update Game Objects
void update_Game_Manager(GAME_MANAGER* gameManager, CP_Vector updateVector, float dt) {
	// Update plyer's position when input WASD
	CP_Vector uVectorNoraml = CP_Vector_Normalize(updateVector);
	updatePlayer(&(gameManager->player), uVectorNoraml, dt);

	for (int i = 0; i < gameManager->enemyCount; i++) {
		updateEnemy(gameManager->enemies+i, dt);
	}
}


void printGameObjects(GAME_MANAGER* gameManager)
{
	printPlayer(&(gameManager->player));
	for (int i = 0; i < gameManager->enemyCount; i++) {
		printEnemy(gameManager->enemies + i);
	}
}




// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	init_Game_Manager(&game_Manager);
	// initialize variables and CProcessing settings for this gamestate
	//player_position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


	//patrol_position = malloc(patrolPoints * sizeof(CP_Vector));
	//patrol_position[0] = CP_Vector_Set(200, 400);
	//patrol_position[1] = CP_Vector_Set(800, 400);
	//patrol_position[2] = CP_Vector_Set(600, 800);

	//patrol = CP_Vector_Set(patrol_position[0].x, patrol_position[0].y);

}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	CP_Vector uVector = getKeyVector();

	update_Game_Manager(&game_Manager, uVector, dt);

	printGameObjects(&game_Manager);
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}