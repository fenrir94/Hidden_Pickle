#pragma once

typedef struct minimap {
	CP_Vector playerIconPosition;
	CP_Vector exitIconPosition;
	CP_Vector* itemIconPosition;
	CP_Vector* obstacleIconPosition;
	int alpha;
} MINIMAP;

void init_Minimap(MINIMAP* minimap, CP_Vector map_size, CP_Vector initVector);

void update_Minimap(MINIMAP* minimap, CP_Vector updateVector, float dt);

void change_Minimap_Alpha(MINIMAP* minimap, float dt);

void print_Minimap(MINIMAP* minimap);

void rollback_Player_Icon_Position(MINIMAP* minimap, CP_Vector updateVector, float dt);