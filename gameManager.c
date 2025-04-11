
#include <stdio.h>
#include "cprocessing.h"
#include "gameManager.h"
#include <stdlib.h>
#include "utility.h"

void init_Game_Manager(GAME_MANAGER* gameManager)
{
	CP_Vector startPositon = CP_Vector_Set(800, 500);
	init_Player(&(gameManager->player), startPositon);
}

// Update Game Objects
void update_Game_Manager(GAME_MANAGER* gameManager, CP_Vector updateVector, float dt) {
	// Update plyer's position when input WASD
	CP_Vector uVectorNoraml = CP_Vector_Normalize(updateVector);
	updatePlayer(&(gameManager->player), uVectorNoraml, dt);
}


void printGameObjects(GAME_MANAGER* gameManager)
{
	printPlayer(&(gameManager->player));
}
