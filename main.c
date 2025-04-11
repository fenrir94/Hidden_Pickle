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
	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	CP_Vector uVector = getKeyVector();

	update_Game_Manager(&game_Manager, uVector, dt);

	
	// In order to understand the code below, 
	// you need to understand how 'blend modes' work.
	//
	// A way to think about blend modes is this: whenever you place something
	// on the screen, for each pixel affected, we will do an operation between
	// the original pixel and the pixel you place (we will call this the 'new' pixel). 
	// 
	// The default blend mode is CP_BLEND_ALPHA, which will use the color of the 
	// new pixel you place multiplied by the alpha value in percentage, where 255 is 100%
	// and 0 is 0%...127 is around 50%. The remaining alpha value will use the original pixel's color. 
	// 
	// This means that if you place a shape with the color (255, 0, 0, 127) on the screen, 
	// for each pixel affected, it will use around 50% of red and 50% of whatever the background
	// color is.
	// 
	// Another blend mode is CP_BLEND_ADD. This will simply add (with a cap of 255) the original
	// pixel with the new pixel. Should be straightforward here. 
	// 
	// An interesting blend mode is CP_BLEND_MULTIPLY. This will multiply the new pixel by the 
	// original pixel, where the original pixel's values will be treated as a percentage, where
	// 255 is 100% and 0 is 0%...127 is around 50%.
	// 
	// This means that if the original pixel's value is 0, the resultant pixel value no matter what you do
	// will be 0 because anything that multiplies by 0 is 0. If the original pixel's value is 255 (i.e. 100%), 
	// the resultant pixel's value will be the new pixel value.
	// 
	// By layering and switching blend modes, we can create many interesting effects only limited
	// by your creativity! In this case, we are going to show a 'light source' effect.
	// 


	//
	// Set dark background
	//
	// I set it to be not-so-black so that you can see what it's hiding


	// Add white to certain parts of the dark background that we want to see
	// This will create the 'light source' effect.
	//CP_Settings_BlendMode(CP_BLEND_ADD);

	// This is a 'light source' on the player
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawCircle(player_position.x, player_position.y, 300);

	// Add some more random 'light sources'
	//CP_Graphics_DrawCircle(100, 100, 100);
	//CP_Graphics_DrawCircle(1300, 800, 400);
	//CP_Graphics_DrawCircle(200, 300, 100);
	//CP_Graphics_DrawCircle(200, 300, 100);



	// Test Patrol
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));

	int startPosition = getStartPoint(destination);

	CP_Vector dPatrolPosition = CP_Vector_Set(patrol_position[destination].x - patrol_position[startPosition].x, patrol_position[destination].y - patrol_position[startPosition].y);

	CP_Vector dPatrolNormal= CP_Vector_Normalize(dPatrolPosition);
	patrol = CP_Vector_Set(patrol.x + speed * dPatrolNormal.x, patrol.y + speed * dPatrolNormal.y);


	CP_Graphics_DrawCircle(patrol.x, patrol.y, 100);

	// Change Destination
	if ((dPatrolPosition.x <= 0 && patrol_position[destination].x >= patrol.x) || (dPatrolPosition.x >= 0 && patrol_position[destination].x <= patrol.x)) {
		if ((dPatrolPosition.y <= 0 && patrol_position[destination].y >= patrol.y) || (dPatrolPosition.y >= 0 && patrol_position[destination].y <= patrol.y)) {
			if (destination == patrolPoints-1) destination = 0;
			else {
				destination++;
			}
		}
	}


	//
	// Scene
	//
	// Multipy the rest of the scene. 
	// 
	//CP_Settings_BlendMode(CP_BLEND_MULTIPLY);
	//// This is the player
	//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	//CP_Graphics_DrawCircle(player_position.x, player_position.y, 100);

	//// These are some random things on the scene
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	//CP_Graphics_DrawRect(100, 100, 50, 50);
	//CP_Graphics_DrawRect(100, 300, 50, 50);
	//CP_Graphics_DrawRect(1400, 600, 50, 50);
	//CP_Graphics_DrawRect(1300, 100, 50, 50);

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
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	//CP_Engine_SetNextGameState(game_init, update_Game_Manager, game_exit);
	CP_Engine_Run();
	return 0;
}
