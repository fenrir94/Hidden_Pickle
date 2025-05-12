#include "background.h"
#include "imageManager.h"


void init_Background(BACKGROUND* background, MAP map, int width_Map, int height_Map, CP_Vector initVector)
{
	background->width_Tile = CP_Image_GetWidth(image_Manager.tileDirt);
	background->height_Tile = CP_Image_GetHeight(image_Manager.tileDirt);
	background->count_Width = width_Map / background->width_Tile + 3;
	background->count_Height = height_Map / background->height_Tile + 3;
	background->startPosition = CP_Vector_Set(map.minX + initVector.x, map.minY + initVector.y);

	background->sizeBoundaryImage = 300;
	background->boundaryMax = CP_Vector_Set(map.maxX + initVector.x , map.maxY + initVector.y );
}

void move_Background(BACKGROUND* background, CP_Vector moveCamera)
{
	background->startPosition = CP_Vector_Add(background->startPosition, moveCamera);
	background->boundaryMax = CP_Vector_Add(background->boundaryMax, moveCamera);
}

void print_Background(BACKGROUND* background)
{
	CP_Settings_ImageFilterMode(CP_IMAGE_FILTER_NEAREST);
	//CP_Settings_ImageMode(CP_POSITION_CORNER);
	for (int i = 0; i < background->count_Width; i++) {
		for (int j = 0; j < background->count_Height; j++) {
			CP_Image_Draw(image_Manager.tileDirt, (float)background->startPosition.x + (i-1) * background->width_Tile, (float)background->startPosition.y + (j-1) * background->height_Tile, (float)background->width_Tile, (float)background->height_Tile, 255);
		}
	}

	//CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void print_Boundary_Background(BACKGROUND* background)
{
	// pirnt boundary row
	for (float i = background->startPosition.x - background->sizeBoundaryImage / 2; i < background->boundaryMax.x + background->sizeBoundaryImage; i += (float)background->sizeBoundaryImage*2/3) {
		CP_Image_Draw(image_Manager.tree, i, background->startPosition.y - background->sizeBoundaryImage / 2, background->sizeBoundaryImage, background->sizeBoundaryImage, 225);
		CP_Image_Draw(image_Manager.tree, i, background->boundaryMax.y + background->sizeBoundaryImage / 2, background->sizeBoundaryImage, background->sizeBoundaryImage, 225);
	}

	// print boundary column
	for (float i = background->startPosition.y - background->sizeBoundaryImage / 2; i < background->boundaryMax.y + background->sizeBoundaryImage; i += background->sizeBoundaryImage*2/3) {
		CP_Image_Draw(image_Manager.tree, background->startPosition.x - background->sizeBoundaryImage / 2, i, background->sizeBoundaryImage, background->sizeBoundaryImage, 225);
		CP_Image_Draw(image_Manager.tree, background->boundaryMax.x + background->sizeBoundaryImage / 2, i, background->sizeBoundaryImage, background->sizeBoundaryImage, 225);
	}

}
