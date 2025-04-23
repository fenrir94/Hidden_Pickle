#pragma once

#include "cprocessing.h"

typedef struct background {
	CP_Vector startPosition;
	CP_Image image_Background;
	int width_Tile;
	int height_Tile;
	int count_Width;
	int count_Height;
} BACKGROUND;

void init_Background(BACKGROUND* background, char* directory_Image, int width_Map, int height_Map, float minMapX, float minMapY);

//void move_Background(BACKGROUND* background, CP_Vector moveCamera);

void print_Background(BACKGROUND* background);