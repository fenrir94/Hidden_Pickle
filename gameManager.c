
#include <stdio.h>
#include "cprocessing.h"
#include "gameManager.h"
#include <stdlib.h>

void init_Game_Manager(GAME_MANAGER* gameManager)
{
	CP_Vector startPositon = CP_Vector_Set(800, 500);
	init_Player(&(gameManager->player), startPositon);
}

void printGameObjects(GAME_MANAGER* gameManager)
{
	printPlayer(&(gameManager->player));
}
