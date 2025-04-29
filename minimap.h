#pragma once

typedef struct minimap {
	CP_Vector playerIconPosition;
	CP_Vector exitIconPosition;
	CP_Vector* itemIconPosition;
	CP_Vector* obstacleIconPosition;
} MINIMAP;

void initMinimap(MINIMAP* minimap, CP_Vector mab_size, CP_Vector initVector);

void updateMinimap(CP_Vector updateVector, float dt);

void printMinimap(void);

void rollback_Player_Icon_Position(MINIMAP* minimap, CP_Vector updateVector, float dt);