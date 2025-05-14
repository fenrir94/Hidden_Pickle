#pragma once

#include "cprocessing.h"

typedef struct imageManager {
	CP_Image tileDirt;
	CP_Image imageFootLeft_Patrol;
	CP_Image imageFootRight_Patrol;
	CP_Image itemBox;
	CP_Image tree[4];
	CP_Image bloodpool;
	CP_Image bloodEffect;
	CP_Image exit;
} IMAGE_MANAGER;

extern IMAGE_MANAGER image_Manager;

void init_ImageManager(IMAGE_MANAGER* imageManager);

void free_ImageManager(IMAGE_MANAGER* imageManager);