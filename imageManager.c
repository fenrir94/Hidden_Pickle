

#include "imageManager.h"

void init_ImageManager(IMAGE_MANAGER* imageManager)
{
	imageManager->tileDirt = CP_Image_Load("./Assets/Map_data/Background/Dirt_02.png");

	imageManager->imageFootLeft_Patrol = CP_Image_Load("./Assets/Footprint/footLeft_Cat.png");
	imageManager->imageFootRight_Patrol = CP_Image_Load("./Assets/Footprint/footRight_Cat.png");

	imageManager->itemBox = CP_Image_Load("./Assets/Image/box_Wood.png");

	imageManager->tree[0] = CP_Image_Load("./Assets/Image/tree0.png");
	imageManager->tree[1] = CP_Image_Load("./Assets/Image/tree1.png");
	imageManager->tree[2] = CP_Image_Load("./Assets/Image/tree2.png");
	imageManager->tree[3] = CP_Image_Load("./Assets/Image/tree3.png");

	imageManager->bloodpool = CP_Image_Load("./Assets/Image/bloodpool.png");
	imageManager->bloodEffect = CP_Image_Load("./Assets/Image/BloodOverlay.png");
	imageManager->exit = CP_Image_Load("./Assets/Image/exit.png");

	imageManager->exit = CP_Image_Load("./Assets/Image/exit.png");
}

void free_ImageManager(IMAGE_MANAGER* imageManager) {

	CP_Image_Free(&imageManager->tileDirt);
	
	CP_Image_Free(&imageManager->imageFootLeft_Patrol);
	CP_Image_Free(&imageManager->imageFootRight_Patrol);

	CP_Image_Free(&imageManager->itemBox);
	CP_Image_Free(&imageManager->tree[1]);
	CP_Image_Free(&imageManager->tree[0]);
	CP_Image_Free(imageManager->tree);

	CP_Image_Free(&imageManager->bloodpool);

	CP_Image_Free(&imageManager->exit);
}