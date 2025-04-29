
#include <stdio.h>
#include "animation.h"

//void init_Animation(ANIMATION* animation)
//{
//}

void init_Animation(ANIMATION* animation, char* filename, int count_FrameAnimation) {
	animation->count_FrameAnimation = count_FrameAnimation;
	animation->currentFrame = 0;
	//animation->imageFrame = malloc(count_FrameAnimation * sizeof(CP_Image));

	char png[] = ".png";

	for (int i = 0; i < count_FrameAnimation; i++) {
		char indexImage[3];
		intToCharArray(i, indexImage);
		
		char imagePath[100];

		/*int length = (int)strlen(filename);*/
			
		strcpy_s(imagePath, sizeof(imagePath), filename);

		strcat_s(imagePath, sizeof(imagePath), indexImage);
		strcat_s(imagePath, sizeof(imagePath), png);
		//printf("%s\n", imagePath);
		animation->imageFrame[i] = CP_Image_Load(imagePath);
	}

	animation->frameDelay = 1;
	animation->frameTimer = 0;
}


void update_Animation(ANIMATION* animation, float df)
{
	animation->frameTimer += df;
	if (animation->frameTimer > animation->frameDelay) {
		if (animation->currentFrame < animation->count_FrameAnimation-1) {
			animation->currentFrame++;
		}
		else {
			animation->currentFrame = 0;
		}
		
		animation->frameTimer = 0;
	}
}

void print_Animation(ANIMATION* animation, CP_Vector position, float angle)
{
	CP_Image_DrawAdvanced(animation->imageFrame[animation->currentFrame], 
		position.x, position.y,
		(float)CP_Image_GetWidth(animation->imageFrame[animation->currentFrame]) * 3 / 5, 
		(float)CP_Image_GetHeight(animation->imageFrame[animation->currentFrame]) * 3 / 5,
		255, angle);
}
