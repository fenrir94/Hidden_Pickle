#include "cprocessing.h"
#include "utility.h"
#include "stageSelectMenu.h"
#include "mainmenu.h"
#include "gameManager.h"
#include "cursor.h"

CP_Image stageSelect_Background_Image_File;
CP_Image* stageSelect_Button_Image_List;

CP_Vector centerVector;

IMAGE stageSelect_Background_Image = { 0, 0, 1800, 900, 255, 0 };
IMAGE exit_Button_Image;
IMAGE* stageSelect_Button_Image;

CP_Sound click_SFX_File;

CP_Font button_Font;

typedef enum state {
	false,
	true
}State;

State isSelectButtonPressed = false;

int stage_Number = -1;
int max_Stage_Number = 1; //stage는 0부터 시작. 스테이지 2개라는 뜻

void Init_Stage_Select_Menu(void)
{
	centerVector = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);

	stageSelect_Background_Image.x = centerVector.x;
	stageSelect_Background_Image.y = centerVector.y;

	stageSelect_Button_Image = (IMAGE*)malloc(2 * sizeof(IMAGE));

	for (int i = 0; i < 2; i++)
	{
		Init_Button(stageSelect_Button_Image + i, CP_Vector_Set(centerVector.x / 2 + i * centerVector.x, centerVector.y), 256, 256);
	}

	Init_Button(&exit_Button_Image, CP_Vector_Set((float)CP_System_GetWindowWidth() - 100, 100), 64, 64);

	button_Font = CP_Font_Load("Assets/Exo2-Regular.ttf"); // 폰트 불러오기, 추후 변경
	CP_Font_Set(button_Font); // 폰트 적용
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); // 폰트 수직, 수평 가운데 정렬
	CP_Settings_TextSize(72.f); // 폰트 사이즈 설정

	stageSelect_Background_Image_File = CP_Image_Load("Assets/Image/stageSelect_Background.png");

	stageSelect_Button_Image_List = LoadImagesFromAssets(3, "Assets/UI/select_menu_button%d.png");

	init_Cursor();

	click_SFX_File = CP_Sound_Load("Assets/SFX/click.ogg");
}

void Update_Stage_Select_Menu(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	//백그라운드 이미지 출력 이미지 좌표 설정해야함
	CP_Image_Draw(stageSelect_Background_Image_File, stageSelect_Background_Image.x, stageSelect_Background_Image.y, stageSelect_Background_Image.width, stageSelect_Background_Image.height, stageSelect_Background_Image.alpha);

	char buffer[15];

	for (int i = 0; i < 2; i++)
	{
		Print_Button(stageSelect_Button_Image + i, i);

		sprintf_s(buffer, sizeof(buffer), "stage %d", i + 1);
		CP_Font_DrawText(buffer, stageSelect_Button_Image[i].x, stageSelect_Button_Image[i].y);
	}

	Print_Exit_Button(&exit_Button_Image);
	CP_Font_DrawText("x", exit_Button_Image.x, exit_Button_Image.y);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
	{
		isSelectButtonPressed = false;
	}
	// 함수로 빼야함

	print_Cursor();
}

void Exit_Stage_Select_Menu(void)
{    
	CP_Image_Free(&stageSelect_Background_Image_File);
	free(stageSelect_Button_Image);

	if (stageSelect_Button_Image_List != NULL)
	{
		for (int i = 0; i < 3; i++) // 버튼 이미지 개수에 맞게 반복
		{
			CP_Image_Free(&stageSelect_Button_Image_List[i]);
		}
		free(stageSelect_Button_Image_List); // 배열 자체도 해제
		stageSelect_Button_Image_List = NULL;
	}

	free_Cursor();
	CP_Sound_Free(&click_SFX_File);
}

void Init_Button(IMAGE* Button, CP_Vector startPosition, float width, float height)
{
	Button->x = startPosition.x;
	Button->y = startPosition.y;
	Button->width = width;
	Button->height = height;
	Button->alpha = 255;
}

void Print_Button(IMAGE* stageSelect_Button, int stageNumber)
{
	CP_Image_Draw(stageSelect_Button_Image_List[0], stageSelect_Button->x, stageSelect_Button->y, stageSelect_Button->width, stageSelect_Button->height, stageSelect_Button->alpha);

	if (isMouseInsideRect(stageSelect_Button->x, stageSelect_Button->y, stageSelect_Button->width, stageSelect_Button->height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		CP_Image_Draw(stageSelect_Button_Image_List[1], stageSelect_Button->x, stageSelect_Button->y, stageSelect_Button->width, stageSelect_Button->height, stageSelect_Button->alpha);
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			CP_Sound_PlayAdvanced(click_SFX_File, 1, 1, FALSE, CP_SOUND_GROUP_0);
			isSelectButtonPressed = true;
		}
		if (isSelectButtonPressed)
		{
			CP_Image_Draw(stageSelect_Button_Image_List[2], stageSelect_Button->x, stageSelect_Button->y, stageSelect_Button->width, stageSelect_Button->height, stageSelect_Button->alpha);


			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
			{
				isSelectButtonPressed = false;
				stage_Number = stageNumber;
				CP_Engine_SetNextGameState(init_Game_Manager, update_Game_Manager, exit_Game_Manager);
			}
		}
	}

}

void Print_Exit_Button(IMAGE* exit_Button)
{
	CP_Image_Draw(stageSelect_Button_Image_List[0], exit_Button->x, exit_Button->y, exit_Button->width, exit_Button->height, exit_Button->alpha);

	if (isMouseInsideRect(exit_Button->x, exit_Button->y, exit_Button->width, exit_Button->height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	{
		CP_Image_Draw(stageSelect_Button_Image_List[1], exit_Button->x, exit_Button->y, exit_Button->width, exit_Button->height, exit_Button->alpha);
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			CP_Sound_PlayAdvanced(click_SFX_File, 1, 1, FALSE, CP_SOUND_GROUP_0);
			isSelectButtonPressed = true;
		}
		if (isSelectButtonPressed)
		{
			CP_Image_Draw(stageSelect_Button_Image_List[2], exit_Button->x, exit_Button->y, exit_Button->width, exit_Button->height, exit_Button->alpha);


			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
			{
				isSelectButtonPressed = false;
				CP_Engine_SetNextGameState(Init_Main_Menu, Update_Main_Menu, Exit_Main_Menu);
			}
		}
	}
}