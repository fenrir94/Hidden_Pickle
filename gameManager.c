
#include <stdio.h>
#include "cprocessing.h"
#include "gameManager.h"
#include <stdlib.h>
#include "utility.h"
#include "camera.h"

GAME_MANAGER game_Manager;

void init_Game_Manager(void )
{
	CP_Vector startPositionPlayer = CP_Vector_Set(800, 500);
	init_Player(&((&game_Manager)->player), startPositionPlayer);

	(&game_Manager)->enemyCount = 3;

	CP_Vector* startPositionEnemies = (CP_Vector*)malloc(sizeof(CP_Vector)* (&game_Manager)->enemyCount);
	startPositionEnemies[0] = CP_Vector_Set(200, 200);
	startPositionEnemies[1] = CP_Vector_Set(1600, 200);
	startPositionEnemies[2] = CP_Vector_Set(800 , 400);

	CP_Vector* patrol1 = (CP_Vector*)malloc(2 * sizeof(CP_Vector));
	patrol1[0] = CP_Vector_Set(200, 200);
	patrol1[1] = CP_Vector_Set(200, 600);

	CP_Vector* patrol2 = (CP_Vector*)malloc(2 * sizeof(CP_Vector));
	patrol2[0] = CP_Vector_Set(1600, 200);
	patrol2[1] = CP_Vector_Set(400, 200);

	CP_Vector* patrol3 = (CP_Vector*)malloc(3 * sizeof(CP_Vector));
	patrol3[0] = CP_Vector_Set(800, 400);
	patrol3[1] = CP_Vector_Set(500, 700);
	patrol3[2] = CP_Vector_Set(1200, 400);

	(&game_Manager)->enemies = (ENEMY*)malloc((&game_Manager)->enemyCount * sizeof(ENEMY));
	init_Enemy_Patrol((&game_Manager)->enemies, startPositionEnemies[0], patrol1, 2);
	init_Enemy_Patrol((&game_Manager)->enemies + 1, startPositionEnemies[1], patrol2, 2);
	init_Enemy_Patrol((&game_Manager)->enemies + 2, startPositionEnemies[2], patrol3, 3);

	//for (int i = 0; i < gameManager->enemyCount; i++) {
	//	init_Enemy((gameManager->enemies + i), startPositionEnemies[i]);
	//}

	initCamera();
}

// Update Game Objects
void update_Game_Manager(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	CP_Vector uVector = getKeyVector();
	
	
	// Update plyer's position when input WASD
	CP_Vector uVectorNoraml = CP_Vector_Normalize(uVector);

	if (checkCameraTrigger(&(game_Manager.player), uVectorNoraml))
	{
		updateCamera(uVectorNoraml, dt);
	}
	else
	{
		updatePlayer(&(game_Manager.player), uVectorNoraml, dt);
	}

	for (int i = 0; i < (&game_Manager)->enemyCount; i++) {
		updateEnemy((&game_Manager)->enemies+i, dt);
	}

	printGameObjects(&game_Manager);

}


void printGameObjects(GAME_MANAGER* gameManager)
{
	printPlayer(&(gameManager->player));
	for (int i = 0; i < gameManager->enemyCount; i++) {
		printEnemy(gameManager->enemies + i);
	}
}


// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void exit_Game_Manager(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}