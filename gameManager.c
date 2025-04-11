
#include <stdio.h>
#include "cprocessing.h"
#include "gameManager.h"
#include <stdlib.h>
#include "utility.h"

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
