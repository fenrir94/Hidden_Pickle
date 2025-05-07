#include "cprocessing.h"
#include "mainmenu.h"
#include "gameManager.h"
#include "utility.h"
#include "stageSelectMenu.h"
#include "cursor.h"

//제목
char Title[15] = "Hidden Pickle";

//이미지
CP_Image digiPen_Image_File; // 인트로 이미지 파일

CP_Image title_Logo_Image_File;// 타이틀 이미지 파일

CP_Image title_Background_Image_File;// 타이틀 배경 파일

CP_Image config_Image_File;

CP_Image config_Exit_Button_File;
CP_Image config_Exit_Button_Cross_File;

CP_Image* button_Image_List; // 버튼 이미지 리스트 0: Normal, 1: Hover, 2: Pressed

#define Config_width 700
#define Config_height 800
#define Config_Exit_width 30 // width == height

IMAGE DigiPen_Image = { 0, 0, 800, 200, 0, 0 }, Title_Image = { 0, 270, 600, 500, 255, 0 }, 
button_Image = {0, 0, 384, 128, 255, 0}, Config_Image = { 0, 0, Config_width, Config_height, 255, 0 }, background_Image = { 0, 0, 1800, 900, 255, 0 },
Config_Exit_Image = { (Config_width - Config_Exit_width) / 2, (Config_height - Config_Exit_width) / 2, Config_Exit_width, Config_Exit_width, 255, 0 }; // 각 이미지 구조체 값

#define Delta_alpha 3

//사운드
CP_Sound DigiPen_SFX_File, click_SFX_File;	// 인트로 사운드 파일

typedef enum state {
	false,
	true
}State;


//메인메뉴 상태
State isIntroStateOn = true;

//사운드 호출 상태
State isSoundStateOn = true;

//컨피그 to do
State isConfigStateOn = false;

State isButtonPressed = false;

//폰트
CP_Font button_Font;

int is_Moved = 0;

void Init_Main_Menu(void)
{
	CP_System_ShowCursor(false);

	CP_System_SetWindowTitle(Title);

	button_Font = CP_Font_Load("Assets/Exo2-Regular.ttf"); // 폰트 불러오기, 추후 변경
	CP_Font_Set(button_Font); // 폰트 적용
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); // 폰트 수직, 수평 가운데 정렬
	CP_Settings_TextSize(72.f); // 폰트 사이즈 설정

	digiPen_Image_File = CP_Image_Load("Assets/Image/DigiPen_WHITE.png"); // 이미지 불러오기

	title_Logo_Image_File = CP_Image_Load("Assets/Image/Hidden_Pickle_Title.png");

	title_Background_Image_File = CP_Image_Load("Assets/Image/Title_Background.png");

	config_Image_File = CP_Image_Load("Assets/UI/menu_ui.png");

	button_Image_List = LoadImagesFromAssets(3, "Assets/UI/menu_button%d.png");

	config_Exit_Button_File = CP_Image_Load("Assets/UI/exit_button.png");

	config_Exit_Button_Cross_File = CP_Image_Load("Assets/UI/icon_cross.png");

	if (!is_Moved)
	{
		centeredCoordinate(&(background_Image.x), &(background_Image.y));
		centeredCoordinate(&(DigiPen_Image.x), &(DigiPen_Image.y)); // 좌표 이동
		centeredCoordinate(&(Title_Image.x), &(Title_Image.y));
		centeredCoordinate(&(button_Image.x), &(button_Image.y));
		centeredCoordinate(&(Config_Image.x), &(Config_Image.y));
		centeredCoordinate(&(Config_Exit_Image.x), &(Config_Exit_Image.y));

		is_Moved = 1;
	}
	init_Cursor();

	DigiPen_SFX_File = CP_Sound_Load("Assets/SFX/Clap.wav"); // 사운드 불러오기
	click_SFX_File = CP_Sound_Load("Assets/SFX/click.ogg");

}

void Update_Main_Menu(void)
{
	if(isIntroStateOn == true)
	{
		Print_Main_Menu_Intro();
	}

	if (isIntroStateOn == false)
	{
		Print_Main_Menu();
	}

}

void Print_Main_Menu_Intro(void)
{
	if (isSoundStateOn == true)
	{
		CP_Sound_Play(DigiPen_SFX_File); // 임시
		isSoundStateOn = false;
	}

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255)); // 해당 배경색으로 초기화

	CP_Image_Draw(digiPen_Image_File, DigiPen_Image.x, DigiPen_Image.y, DigiPen_Image.width, DigiPen_Image.height, DigiPen_Image.alpha); // 이미지 그리기

	DigiPen_Image.timeForAlpha += CP_System_GetDt(); // 시간 받아오기

	if (DigiPen_Image.timeForAlpha <= 1.5)
	{
		DigiPen_Image.alpha += Delta_alpha; // 투명도 변화
	}
	else if ((DigiPen_Image.timeForAlpha > 1.5))
	{
		DigiPen_Image.alpha -= Delta_alpha;
	}

	if (DigiPen_Image.timeForAlpha >= 3 || CP_Input_KeyDown(KEY_SPACE))
		// 인트로 시간 5초가 지나거나, 스페이스 바 입력, 더블 클릭 시 스테이트 변경
	{
		isIntroStateOn = false;
		isSoundStateOn = true;
	}
}

void Print_Main_Menu(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));

	CP_Image_Draw(title_Background_Image_File, background_Image.x, background_Image.y, background_Image.width, background_Image.height, background_Image.alpha);

	CP_Image_Draw(title_Logo_Image_File, Title_Image.x, Title_Image.y, Title_Image.width, Title_Image.height, Title_Image.alpha);

	CP_Image_Draw(button_Image_List[0], button_Image.x, button_Image.y, button_Image.width, button_Image.height, button_Image.alpha);
	CP_Image_Draw(button_Image_List[0], button_Image.x, button_Image.y + 150, button_Image.width, button_Image.height, button_Image.alpha);
	CP_Image_Draw(button_Image_List[0], button_Image.x, button_Image.y + 300, button_Image.width, button_Image.height, button_Image.alpha);

	if (isConfigStateOn == false)
	{
		if (isMouseInsideRect(button_Image.x, button_Image.y + 300, button_Image.width, button_Image.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Image_Draw(button_Image_List[1], button_Image.x, button_Image.y + 300, button_Image.width, button_Image.height, button_Image.alpha);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Sound_Play(click_SFX_File);
				isButtonPressed = true;
			}
			if (isButtonPressed)
			{
				CP_Image_Draw(button_Image_List[2], button_Image.x, button_Image.y + 300, button_Image.width, button_Image.height, button_Image.alpha);


				if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
				{
					isButtonPressed = false;
					CP_Engine_Terminate();
				}
			}
		}

		if (isMouseInsideRect(button_Image.x, button_Image.y + 150, button_Image.width, button_Image.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Image_Draw(button_Image_List[1], button_Image.x, button_Image.y + 150, button_Image.width, button_Image.height, button_Image.alpha);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Sound_Play(click_SFX_File);
				isButtonPressed = true;
			}
			if (isButtonPressed)
			{
				CP_Image_Draw(button_Image_List[2], button_Image.x, button_Image.y + 150, button_Image.width, button_Image.height, button_Image.alpha);
				

				if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
				{
					isButtonPressed = false;
					isConfigStateOn = true;
				}
			}
		}

		if (isMouseInsideRect(button_Image.x, button_Image.y, button_Image.width, button_Image.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Image_Draw(button_Image_List[1], button_Image.x, button_Image.y, button_Image.width, button_Image.height, button_Image.alpha);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				CP_Sound_Play(click_SFX_File);
				isButtonPressed = true;
			}

			if (isButtonPressed)
			{
				CP_Image_Draw(button_Image_List[2], button_Image.x, button_Image.y, button_Image.width, button_Image.height, button_Image.alpha);


				if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
				{
					isButtonPressed = false;
		
					CP_Engine_SetNextGameState(Init_Stage_Select_Menu, Update_Stage_Select_Menu, Exit_Stage_Select_Menu);
				}
			}
		}

		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			isButtonPressed = false;
		}
	}

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

	CP_Font_DrawText("Play", button_Image.x, button_Image.y);
	CP_Font_DrawText("Config", button_Image.x, button_Image.y + 150);
	CP_Font_DrawText("Exit", button_Image.x, button_Image.y + 300);


	

	if (isConfigStateOn == true)
	{
		CP_Image_Draw(config_Image_File, Config_Image.x, Config_Image.y, Config_Image.width, Config_Image.height, Config_Image.alpha);

		CP_Image_Draw(config_Exit_Button_File, Config_Exit_Image.x, Config_Exit_Image.y, Config_Exit_Image.width, Config_Exit_Image.height, Config_Exit_Image.alpha);
		CP_Image_Draw(config_Exit_Button_Cross_File, Config_Exit_Image.x, Config_Exit_Image.y, 18, 18, Config_Exit_Image.alpha);

		if (isMouseInsideRect(Config_Exit_Image.x, Config_Exit_Image.y, Config_Exit_width, Config_Exit_width, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			if (CP_Input_MouseClicked()) //클릭 사운드 추가
			{
				CP_Sound_Play(click_SFX_File);
				isConfigStateOn = false;
			}
		}
	}

	print_Cursor();

}

void Exit_Main_Menu(void)
{
	free_Cursor();

	CP_Image_Free(&digiPen_Image_File); // 이미지 해제
	CP_Image_Free(&title_Logo_Image_File);
	CP_Image_Free(&config_Image_File);
	CP_Image_Free(&config_Exit_Button_File);
	CP_Image_Free(&config_Exit_Button_Cross_File);

	if (button_Image_List != NULL)
	{
		for (int i = 0; i < 3; i++) // 버튼 이미지 개수에 맞게 반복
		{
			CP_Image_Free(&button_Image_List[i]);
		}
		free(button_Image_List); // 배열 자체도 해제
		button_Image_List = NULL;
	}

	CP_Image_Free(&title_Background_Image_File);
	CP_Sound_Free(&DigiPen_SFX_File);
}