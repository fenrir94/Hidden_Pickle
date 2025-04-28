#pragma once

typedef enum isResultScreenOn {
	RESULT_SCREEN_OFF,
	RESULT_SCREEN_ON
} EisResultScreenOn;

typedef enum gameState {
	GAME_STATE_PLAYING,
	GAME_STATE_WIN,
	GAME_STATE_LOSE
} EgameState;

typedef struct result_Screen {
	EisResultScreenOn isScreenOn;
	EgameState gameState;
} RESULT_SCREEN;

void init_Result_Screen(RESULT_SCREEN* result_screen);

void update_Result_Screen(RESULT_SCREEN* result_screen, int gameResult);