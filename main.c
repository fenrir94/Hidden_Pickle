
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


// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);

	CP_Engine_Run();

	return 0;
}
