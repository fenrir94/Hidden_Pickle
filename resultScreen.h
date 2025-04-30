#pragma once
#include "cprocessing.h"

CP_Image menu_Ui_Image_File;

CP_Image round_Button_Image_File;

CP_Image round_Button_Pressed_Image_File;

CP_Image next_Icon_Image_File;

CP_Image repeat_Icon_Image_File;

CP_Image select_Icon_Image_File;

CP_Image screen_Black_Image_File;

float screen_Black_Alpha;

typedef enum isResultScreenOn {
	RESULT_SCREEN_OFF,
	RESULT_SCREEN_ON
} EisResultScreenOn;

typedef enum game_State {
	GAME_STATE_PLAYING,
	GAME_STATE_WIN,
	GAME_STATE_LOSE
} EgameState;

typedef enum animation_State {
	ANIMATION_NONE,
	ANIMATION_LOSE,
	ANIMATION_GAME_OVER
} EanimationState;

typedef enum is_Button_Pressed {
	NOT_PRESSED,
	PRESSED
} EisButtonPressed;

typedef struct uiImage {
	float x;
	float y;
	float size;
	EisButtonPressed isButtonPressed;
} UI_IMAGE;

typedef struct result_Screen {
	EisResultScreenOn isScreenOn;
	EgameState gameState;
	EanimationState animationState;
	UI_IMAGE button_Image[3];
} RESULT_SCREEN;

void init_Result_Screen(RESULT_SCREEN* result_screen);

void init_Result_Screen_Button(RESULT_SCREEN* result_screen);

void update_Result_Screen(RESULT_SCREEN* result_screen, int gameResult);

void update_Result_Screen_Button(RESULT_SCREEN* result_screen);

void print_Result_Screen(RESULT_SCREEN* result_screen);