#include "cprocessing.h"
#include "mainmenu.h"
#include "gameManager.h"
#include "utility.h"

//제목
char Title[15] = "Hidden Pickle";

//이미지
CP_Image digiPen_Image_File; // 인트로 이미지 파일

CP_Image title_Logo_Image_File;// 타이틀 이미지 파일

CP_Image title_Background_Image_File;// 타이틀 배경 파일

CP_Image* button_Image_List; // 버튼 이미지 리스트 0: Normal, 1: Hover, 2: Pressed

//이미지 구조체
typedef struct Image{
    float x;
    float y;
    float width;
    float height;
    int alpha;
    float timeForAlpha; // 인트로 투명도 조절용
} IMAGE;

#define Config_width 700
#define Config_height 800
#define Config_Exit_width 30 // width == height

IMAGE DigiPen_Image = { 0, 0, 800, 200, 0, 0 }, Title_Image = { 0, 270, 600, 500, 255, 0 }, 
button_Image = {0, 0, 384, 128, 255, 0}, Config_Image = { 0, 0, Config_width, Config_height, 255, 0 }, background_Image = { 0, 0, 1800, 900, 255, 0 },
Config_Exit_Image = { (Config_width - Config_Exit_width) / 2, (Config_height - Config_Exit_width) / 2, Config_Exit_width, Config_Exit_width, 255, 0 }; // 각 이미지 구조체 값

#define Delta_alpha 3

//사운드
CP_Sound DigiPen_SFX_File, click_SFX_File;	// 인트로 사운드 파일

typedef enum state{
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

void mainmenu_init(void)
{
	CP_System_SetWindowTitle(Title);

	button_Font = CP_Font_Load("Assets/Exo2-Regular.ttf"); // 폰트 불러오기, 추후 변경
	CP_Font_Set(button_Font); // 폰트 적용
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); // 폰트 수직, 수평 가운데 정렬
	CP_Settings_TextSize(72.f); // 폰트 사이즈 설정

	digiPen_Image_File = CP_Image_Load("Assets/DigiPen_WHITE.png"); // 이미지 불러오기

	title_Logo_Image_File = CP_Image_Load("Assets/Hidden_Pickle_Title.png");

	title_Background_Image_File = CP_Image_Load("Assets/Title_Background.png");

	// 다수의 이미지를 읽을 때 사용할 수 있음. 추후 함수로 분리

	button_Image_List = (CP_Image*)malloc(3 * sizeof(CP_Image));

	for (int i = 0; i < 3; i++)
	{
		char buffer[50];

		sprintf_s(buffer, 50, "Assets/button%d.png", i);

		button_Image_List[i] = CP_Image_Load(buffer);
	}
	
	//

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

	DigiPen_SFX_File = CP_Sound_Load("Assets/Clap.wav"); // 사운드 불러오기
	click_SFX_File = CP_Sound_Load("Assets/click.ogg");

}

void mainmenu_update(void)
{
	if(isIntroStateOn == true)
	{
		print_Intro();
	}

	if (isIntroStateOn == false)
	{
		print_Mainmenu();
	}

}

void print_Intro(void)
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

void print_Mainmenu(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));

	//타이틀 배경 이미지 출력 추가

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
					CP_Engine_SetNextGameState(init_Game_Manager, update_Game_Manager, exit_Game_Manager);
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
		CP_Image_Draw(button_Image_List[0], Config_Image.x, Config_Image.y, Config_Image.width, Config_Image.height, Config_Image.alpha);

		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(Config_Exit_Image.x, Config_Exit_Image.y, Config_Exit_width, Config_Exit_width);

		if (isMouseInsideRect(Config_Exit_Image.x, Config_Exit_Image.y, Config_Exit_width, Config_Exit_width, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			if (CP_Input_MouseClicked()) //클릭 사운드 추가
			{
				CP_Sound_Play(click_SFX_File);
				isConfigStateOn = false;
			}
		}
	}

}

void mainmenu_exit(void)
{
	CP_Image_Free(&digiPen_Image_File); // 이미지 해제
	CP_Image_Free(&title_Logo_Image_File);
	CP_Image_Free(button_Image_List);
	CP_Image_Free(&title_Background_Image_File);
	CP_Sound_Free(&DigiPen_SFX_File);
}