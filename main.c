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


#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400

CP_Vector player_position;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	player_position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	// Very bad player movement code!
	if (CP_Input_KeyDown(KEY_W)) player_position.y -= PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_S)) player_position.y += PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_A)) player_position.x -= PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_D)) player_position.x += PLAYER_SPEED * dt;

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
	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

	// Add white to certain parts of the dark background that we want to see
	// This will create the 'light source' effect.
	CP_Settings_BlendMode(CP_BLEND_ADD);

	// This is a 'light source' on the player
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player_position.x, player_position.y, 300);

	// Add some more random 'light sources'
	CP_Graphics_DrawCircle(100, 100, 100);
	CP_Graphics_DrawCircle(1300, 800, 400);
	CP_Graphics_DrawCircle(200, 300, 100);
	CP_Graphics_DrawCircle(200, 300, 100);

	//
	// Scene
	//
	// Multipy the rest of the scene. 
	// 
	CP_Settings_BlendMode(CP_BLEND_MULTIPLY);
	// This is the player
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player_position.x, player_position.y, 100);

	// These are some random things on the scene
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(100, 100, 50, 50);
	CP_Graphics_DrawRect(100, 300, 50, 50);
	CP_Graphics_DrawRect(1400, 600, 50, 50);
	CP_Graphics_DrawRect(1300, 100, 50, 50);
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
	CP_Engine_Run();
	return 0;
}
