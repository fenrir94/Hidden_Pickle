
//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ?2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <Windows.h>
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gameManager.h"
#include "utility.h"
#include "mainmenu.h"


#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400



CP_Vector player_position;
CP_Vector* patrol_position;

CP_Vector patrol;

int patrolPoints = 3;
int destination = 1;
int speed = 4;

int getStartPoint(int dest) {
	if (dest == 0) return patrolPoints-1;
	else return dest - 1;
}

GAME_MANAGER game_Manager;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	init_Game_Manager(&game_Manager);
	// initialize variables and CProcessing settings for this gamestate
	player_position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	
	
	patrol_position = malloc(patrolPoints * sizeof(CP_Vector));
	patrol_position[0] = CP_Vector_Set(200, 400);
	patrol_position[1] = CP_Vector_Set(800, 400);
	patrol_position[2] = CP_Vector_Set(600, 800);

	patrol = CP_Vector_Set(patrol_position[0].x, patrol_position[0].y);

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

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);

	CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	CP_System_SetWindowSize(1600, 900);

	CP_Engine_Run();
	return 0;
}
