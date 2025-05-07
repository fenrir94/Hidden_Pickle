#include "cprocessing.h"
#include "cursor.h"
#include "gameManager.h"

CP_Image pointer_Cursor_Image_File;
CP_Image target_Cursor_Image_File;

void init_Cursor(void)
{
	pointer_Cursor_Image_File = CP_Image_Load("Assets/UI/pointer_cursor.png");
	target_Cursor_Image_File = CP_Image_Load("Assets/UI/target_cursor.png");
}

void print_Cursor(void)
{
	CP_Image_Draw(pointer_Cursor_Image_File, CP_Input_GetMouseX() + 12, CP_Input_GetMouseY() + 12, 32, 32, 255);
}

void print_Cursor_Playing(void)
{
	if (game_Manager.result_Screen.isScreenOn == RESULT_SCREEN_ON)
	{
		CP_Image_Draw(pointer_Cursor_Image_File, CP_Input_GetMouseX() + 12, CP_Input_GetMouseY() + 12, 32, 32, 255);
	}
	else
	{
		CP_Image_Draw(target_Cursor_Image_File, CP_Input_GetMouseX() + 12, CP_Input_GetMouseY() + 12, 64, 64, 255);
	}
}

void free_Cursor(void)
{
	CP_Image_Free(&pointer_Cursor_Image_File);
	CP_Image_Free(&target_Cursor_Image_File);
}