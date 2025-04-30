#include "resultScreen.h"
#include "utility.h"
#include "stageSelectMenu.h"
#include "gameManager.h"

CP_Font ui_Font;

CP_Sound result_Click_SFX_File;

extern int stage_Number;
extern int max_Stage_Number;

int stage_Number_State = 1;
int printed_Stage_Number = 0;

void init_Result_Screen(RESULT_SCREEN* result_screen)
{
	result_screen->gameState = GAME_STATE_PLAYING;
	result_screen->isScreenOn = RESULT_SCREEN_OFF;
	result_screen->animationState = ANIMATION_NONE;

	menu_Ui_Image_File = CP_Image_Load("Assets/UI/menu_ui.png");
	round_Button_Image_File = CP_Image_Load("Assets/UI/button_round0.png");
	round_Button_Pressed_Image_File = CP_Image_Load("Assets/UI/button_round1.png");
	next_Icon_Image_File = CP_Image_Load("Assets/UI/icon_next.png");
	repeat_Icon_Image_File = CP_Image_Load("Assets/UI/icon_repeat.png");
	select_Icon_Image_File = CP_Image_Load("Assets/UI/icon_select.png");
	screen_Black_Image_File = CP_Image_Load("Assets/Image/black.png");

	ui_Font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(ui_Font); // 폰트 적용
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); // 폰트 수직, 수평 가운데 정렬
	CP_Settings_TextSize(150.f); // 폰트 사이즈 설정

	result_Click_SFX_File = CP_Sound_Load("Assets/SFX/click.ogg");

	screen_Black_Alpha = 0;

	init_Result_Screen_Button(result_screen);
}

void init_Result_Screen_Button(RESULT_SCREEN* result_screen)
{
	for (int i = 0; i < 3; i++)
	{
		result_screen->button_Image[i].x = (float)(CP_System_GetWindowWidth() / 2 + i * 200 - 200);
		result_screen->button_Image[i].y = (float)(CP_System_GetWindowHeight() / 2 + 250);
		result_screen->button_Image[i].size = (float)192;
		result_screen->button_Image[i].isButtonPressed = NOT_PRESSED;
	}
}

void update_Result_Screen(RESULT_SCREEN* result_screen, int gameResult)
{
	result_screen->gameState = gameResult;
	result_screen->isScreenOn = RESULT_SCREEN_ON;

	if (result_screen->gameState == GAME_STATE_WIN)
	{
		result_screen->animationState = ANIMATION_GAME_OVER;
	}
	else if (result_screen->gameState == GAME_STATE_LOSE)
	{
		result_screen->animationState = ANIMATION_LOSE;
	}
}

void update_Result_Screen_Button(RESULT_SCREEN* result_screen)
{
	for (int i = 0; i < 3; i++)
	{
		if (isMouseInsideCircle(result_screen->button_Image[i].x, result_screen->button_Image[i].y, result_screen->button_Image[i].size, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			if ((result_screen->gameState == GAME_STATE_LOSE || (result_screen->gameState == GAME_STATE_WIN && stage_Number == max_Stage_Number)) && i == 1)
			{
				continue;
			}


			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Sound_Play(result_Click_SFX_File);
				result_screen->button_Image[i].isButtonPressed = PRESSED;
			}
			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
			{
				result_screen->button_Image[i].isButtonPressed = NOT_PRESSED;

				if (i == 0)
				{
					CP_Engine_SetNextGameState(Init_Stage_Select_Menu, Update_Stage_Select_Menu, Exit_Stage_Select_Menu);
				}
				else if (i == 1)
				{
					stage_Number++;
					CP_Engine_SetNextGameStateForced(init_Game_Manager, update_Game_Manager, exit_Game_Manager);
				}
				else if (i == 2)
				{
					CP_Engine_SetNextGameStateForced(init_Game_Manager, update_Game_Manager, exit_Game_Manager);
				}
			}

		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			result_screen->button_Image[i].isButtonPressed = NOT_PRESSED;
		}
	}

}

void print_Result_Screen(RESULT_SCREEN* result_screen)
{
	if (result_screen->animationState == ANIMATION_NONE && result_screen->isScreenOn == RESULT_SCREEN_ON)
	{
		if (stage_Number_State)
		{
			printed_Stage_Number = stage_Number + 1;
			stage_Number_State = 0;
		}

		screen_Black_Alpha = clamp(screen_Black_Alpha + 10, 0 , 150);

		CP_Image_Draw(screen_Black_Image_File, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), (int)screen_Black_Alpha);

		CP_Image_Draw(menu_Ui_Image_File, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 700, 800, 255);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

		char stage_Buffer[15];
		sprintf_s(stage_Buffer, sizeof(stage_Buffer), "STAGE %d", printed_Stage_Number);

		CP_Font_DrawText(stage_Buffer, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 - 150);

		if (result_screen->gameState == GAME_STATE_WIN)
		{
			CP_Font_DrawText("CLEAR!", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
		}
		else
		{
			CP_Font_DrawText("FAIL", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
		}

		for (int i = 0; i < 3; i++)
		{
			if (result_screen->button_Image[i].isButtonPressed == PRESSED)
			{
				CP_Image_Draw(round_Button_Pressed_Image_File, result_screen->button_Image[i].x, result_screen->button_Image[i].y, result_screen->button_Image[i].size, result_screen->button_Image[i].size, 255);
			}
			else if (result_screen->button_Image[i].isButtonPressed == NOT_PRESSED)
			{
				CP_Image_Draw(round_Button_Image_File, result_screen->button_Image[i].x, result_screen->button_Image[i].y, result_screen->button_Image[i].size, result_screen->button_Image[i].size, 255);
			}
		}

		CP_Image_Draw(select_Icon_Image_File, result_screen->button_Image[0].x, result_screen->button_Image[0].y, result_screen->button_Image[0].size, result_screen->button_Image[0].size, 255);

		CP_Image_Draw(repeat_Icon_Image_File, result_screen->button_Image[2].x, result_screen->button_Image[2].y, (float)90, (float)90, 255);

		if (result_screen->gameState == GAME_STATE_LOSE || (result_screen->gameState == GAME_STATE_WIN && stage_Number == max_Stage_Number))
		{
			CP_Image_Draw(round_Button_Pressed_Image_File, result_screen->button_Image[1].x, result_screen->button_Image[1].y, result_screen->button_Image[1].size, result_screen->button_Image[1].size, 255);
		}
		else
		{
			CP_Image_Draw(next_Icon_Image_File, result_screen->button_Image[1].x, result_screen->button_Image[1].y, (float)90, (float)90., 255);
		}

		

		
	}
}
