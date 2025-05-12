#pragma once

#include "cprocessing.h"
#include "camera.h"

typedef struct background {
	CP_Vector startPosition;
	CP_Image image_Background;
	int width_Tile;
	int height_Tile;
	int count_Width;
	int count_Height;
	float sizeBoundaryImage;
	CP_Vector boundaryMax;
} BACKGROUND;

void init_Background(BACKGROUND* background, MAP map, int width_Map, int height_Map, CP_Vector initVector);

void move_Background(BACKGROUND* background, CP_Vector moveCamera);

void print_Background(BACKGROUND* background);

void print_Boundary_Background(BACKGROUND* background);