#include "cprocessing.h"
#include "mainmenu.h"
#include <math.h>
#include <stdlib.h>
#include "gameManager.h"

//제목
char Title[15] = "Hidden Pickle";

//메인메뉴 상태
int menu_state = 0;
enum menu_state{
	intro,
	menu, 
	playGame
};



//이미지
CP_Image DigiPen_IM_File; // 인트로 이미지 파일

CP_Image Title_IM_File;// 타이틀 이미지 파일

//이미지 구조체
typedef struct Image{
    float x;
    float y;
    float width;
    float height;
    int alpha;
    float timeForAlpha; // 인트로 투명도 조절용
} IM;

IM DigiPen_IM = {0, 0, 800, 200, 0, 0}, Title_IM = {0, 270, 600, 500, 255, 0}; // 이미지 구조체 값

#define Delta_alpha 3

//좌표 구조체
typedef struct Coord{
    float x;
    float y;
} CD;

//버튼
#define Button_width 600
#define Button_height 100

CD Exit_xy = {0, -300}, Conf_xy = {0, -150}, Play_xy = {0, 0};

//컨피그
int config_state = 0;

#define Config_width 700
#define Config_height 800
#define Config_Exit_width 30 // width == height

CD Config_xy = {0, 0}, Config_Exit_xy = {(Config_width-Config_Exit_width)/2, (Config_height-Config_Exit_width)/2};

//사운드
CP_Sound DigiPen_SFX_File;	// 인트로 사운드 파일

//사운드 호출 상태
int sound_state = 1;
enum sound_state{
	off,
	on
};


//색
CP_Color Black;
CP_Color Green;

//폰트
CP_Font Button_Font;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
// 사각형 범위 클릭 감지 함수
{
	if (area_center_x - area_width / 2 < click_x && click_x < area_center_x + area_width / 2 &&
		area_center_y - area_height / 2 < click_y && click_y < area_center_y + area_height / 2)
	{
		if (CP_Input_MouseClicked())
		{
			return 1;
		}
	}
	
	return 0;
}


int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
// 원형 범위 클릭 감지 함수
{
	if (pow(click_x - circle_center_x, 2.0) + pow(click_y - circle_center_y, 2.0) <= pow(diameter / 2, 2.0))
	{
		if (CP_Input_MouseClicked())
		{
			return 1;
		}
	}

	return 0;
}

void MoveCoords(float *x, float *y)
// 좌표 이동 함수 (0,0)이 중심이 되도록
{
	*x += (float)CP_System_GetWindowWidth() / 2;

	*y *= -1;

	*y += (float)CP_System_GetWindowHeight() / 2;
}

void mainmenu_init(void)
{
	CP_System_SetWindowTitle(Title);

	Button_Font = CP_Font_Load("Assets/Exo2-Regular.ttf"); // 폰트 불러오기, 추후 변경
	CP_Font_Set(Button_Font); // 폰트 적용
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE); // 폰트 수직, 수평 가운데 정렬
	CP_Settings_TextSize(72.f); // 폰트 사이즈 설정

	DigiPen_IM_File = CP_Image_Load("Assets/DigiPen_WHITE.png"); // 이미지 불러오기
	MoveCoords(&(DigiPen_IM.x), &(DigiPen_IM.y)); // 이미지 좌표 이동

	Title_IM_File = CP_Image_Load("Assets/Hidden_Pickle_Title.png");
	MoveCoords(&(Title_IM.x), &(Title_IM.y));

	MoveCoords(&(Exit_xy.x), &(Exit_xy.y));
	MoveCoords(&(Conf_xy.x), &(Conf_xy.y));
	MoveCoords(&(Play_xy.x), &(Play_xy.y));

	MoveCoords(&(Config_xy.x), &(Config_xy.y));
	MoveCoords(&(Config_Exit_xy.x), &(Config_Exit_xy.y));

	Black = CP_Color_Create(0, 0, 0, 255);
	Green = CP_Color_Create(0, 0, 255, 255);

	DigiPen_SFX_File = CP_Sound_Load("Assets/Clap.wav"); // 사운드 불러오기

}

void mainmenu_update(void)
{
	if(menu_state == intro)
	{
		if(sound_state == on)
		{
			CP_Sound_Play(DigiPen_SFX_File);
			sound_state = off;
		}
		
		CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255)); // 해당 배경색으로 초기화

		CP_Image_Draw(DigiPen_IM_File, DigiPen_IM.x, DigiPen_IM.y, DigiPen_IM.width, DigiPen_IM.height, DigiPen_IM.alpha); // 이미지 그리기

		DigiPen_IM.timeForAlpha += CP_System_GetDt(); // 시간 받아오기

		if (DigiPen_IM.timeForAlpha <= 1.5)
		{
			DigiPen_IM.alpha += Delta_alpha; // 투명도 변화
		}
		else if ((DigiPen_IM.timeForAlpha > 1.5))
		{
			DigiPen_IM.alpha -= Delta_alpha;
		}

		if (DigiPen_IM.timeForAlpha >= 3 || CP_Input_KeyDown(KEY_SPACE))
		// 인트로 시간 5초가 지나거나, 스페이스 바 입력, 더블 클릭 시 스테이트 변경
		{
			menu_state = menu;
			sound_state = on;
		}

	}

	if(menu_state == menu)
	{
		if(CP_Input_KeyTriggered(KEY_SPACE))
		{
			CP_Sound_Play(DigiPen_SFX_File);
		}
		CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));

		CP_Image_Draw(Title_IM_File, Title_IM.x, Title_IM.y, Title_IM.width, Title_IM.height, Title_IM.alpha);

		CP_Settings_Fill(CP_Color_Create(85, 85, 85, 255)); // 이 다음 그려지는 도형이나 문자의 색상 결정
		CP_Graphics_DrawRect(Exit_xy.x, Exit_xy.y, Button_width, Button_height);
		CP_Graphics_DrawRect(Conf_xy.x, Conf_xy.y, Button_width, Button_height);
		CP_Graphics_DrawRect(Play_xy.x, Play_xy.y, Button_width, Button_height);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Exit", Exit_xy.x, Exit_xy.y);
		CP_Font_DrawText("Config", Conf_xy.x, Conf_xy.y);
		CP_Font_DrawText("Play", Play_xy.x, Play_xy.y);

		if (config_state == off)
		{
			if(IsAreaClicked(Exit_xy.x, Exit_xy.y, Button_width, Button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				exit(0);
			}

			if(IsAreaClicked(Conf_xy.x, Conf_xy.y, Button_width, Button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				config_state = on;			
			}

			if(IsAreaClicked(Play_xy.x, Play_xy.y, Button_width, Button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(init_Game_Manager, update_Game_Manager, exit_Game_Manager);
			}
		}

		if (config_state == on)
		{
			
			CP_Settings_Fill(CP_Color_Create(85, 85, 85, 200));
			CP_Graphics_DrawRect(Config_xy.x, Config_xy.y, Config_width, Config_height);

			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRect(Config_Exit_xy.x, Config_Exit_xy.y, Config_Exit_width, Config_Exit_width);

			/*
			CP_Graphics_DrawLine(Soundbar_xy_1.x, Soundbar_xy_1.y, Soundbar_xy_2.x, Soundbar_xy_2.y);

			CP_Settings_Stroke(Green);

			CP_Graphics_DrawLine(Soundbar_xy_1.x, Soundbar_xy_1.y, Soundbar_xy_2.x, Soundbar_xy_2.y);
			*/

			if(IsAreaClicked(Config_Exit_xy.x, Config_Exit_xy.y, Config_Exit_width, Config_Exit_width, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				config_state = off;
			}
		}
	}

}

void mainmenu_exit(void)
{
	CP_Image_Free(&DigiPen_IM_File); // 이미지 해제
	CP_Image_Free(&Title_IM_File);
	CP_Sound_Free(&DigiPen_SFX_File);

}