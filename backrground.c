#include "background.h"

void init_Background(BACKGROUND* background, char* directory_Image, int width_Map, int height_Map, float minMapX, float minMapY)
{
	background->image_Background = CP_Image_Load(directory_Image);
	background->width_Tile = CP_Image_GetWidth(background->image_Background);
	background->height_Tile = CP_Image_GetHeight(background->image_Background);
	background->count_Width = width_Map / background->width_Tile + 1;
	background->count_Height = height_Map / background->height_Tile + 1;
	background->startPosition = CP_Vector_Set(minMapX, minMapY);
}

//void move_Background(BACKGROUND* background, CP_Vector moveCamera)
//{
//	background->startPosition = CP_Vector_Add(background->startPosition, moveCamera);
//}

void print_Background(BACKGROUND* background)
{
	CP_Settings_ImageFilterMode(CP_IMAGE_FILTER_NEAREST);
	//CP_Settings_ImageMode(CP_POSITION_CORNER);
	for (int i = 0; i < background->count_Width; i++) {
		for (int j = 0; j < background->count_Height; j++) {
			CP_Image_Draw(background->image_Background, (float)background->startPosition.x + i * background->width_Tile, (float)background->startPosition.y + j * background->height_Tile, (float)background->width_Tile, (float)background->height_Tile, 255);
		}
	}

	//CP_Settings_ImageMode(CP_POSITION_CENTER);
}
