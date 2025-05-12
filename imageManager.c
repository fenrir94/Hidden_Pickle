

#include "imageManager.h"

void init_ImageManager(IMAGE_MANAGER* imageManager)
{
	imageManager->tileDirt = CP_Image_Load("./Assets/Map_data/Background/Dirt_02.png");

	imageManager->imageFootLeft_Patrol = CP_Image_Load("./Assets/Footprint/footLeft_Cat.png");
	imageManager->imageFootRight_Patrol = CP_Image_Load("./Assets/Footprint/footRight_Cat.png");

	imageManager->itemBox = CP_Image_Load("./Assets/Image/box_Wood.png");
	imageManager->tree = CP_Image_Load("./Assets/Image/tree.png");
	imageManager->bloodpool = CP_Image_Load("./Assets/Image/bloodpool.png");

	imageManager->exit = CP_Image_Load("./Assets/Image/exit.png");
}

void free_ImageManager(IMAGE_MANAGER* imageManager) {

	CP_Image_Free(&imageManager->tileDirt);
	
	CP_Image_Free(&imageManager->imageFootLeft_Patrol);
	CP_Image_Free(&imageManager->imageFootRight_Patrol);

	CP_Image_Free(&imageManager->itemBox);
	CP_Image_Free(&imageManager->tree);
	CP_Image_Free(&imageManager->bloodpool);

	CP_Image_Free(&imageManager->exit);
}