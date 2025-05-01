#pragma once
#include "resultScreen.h"

typedef struct minimapDate {
	CP_Vector minimapPosition;
	CP_Vector playerIconPosition;
	CP_Vector exitIconPosition;
	CP_Vector* itemIconPosition;
	CP_Vector* obstacleIconPosition;
	float minimapUiSize;
	float minimapWidth;
	float minimapHeight;
	int alpha;
} MINIMAP_DATA;

typedef enum minimap_State {
	MINIMAP_ON,
	MINIMAP_EXPANDED,
	MINIMAP_OFF
}EminimapState;

typedef struct minimap {
	MINIMAP_DATA normal;
	MINIMAP_DATA expanded;
	EminimapState minimapState;
} MINIMAP;

void init_Minimap(MINIMAP* minimap, CP_Vector map_size, CP_Vector initVector);

void init_Minimap_Expanded(MINIMAP* minimap, CP_Vector initVector);

void update_Minimap(MINIMAP* minimap, CP_Vector updateVector, float dt);

void change_Minimap_Alpha(MINIMAP* minimap, RESULT_SCREEN* result_screen, float dt);

void change_Minimap_State(MINIMAP* minimap);

void print_Minimap(MINIMAP* minimap);

void rollback_Player_Icon_Position(MINIMAP* minimap, CP_Vector updateVector, float dt);