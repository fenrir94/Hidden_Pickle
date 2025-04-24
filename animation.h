#pragma once


#include <string.h>
#include "cprocessing.h"
#include "utility.h"


#define DELAY_FRAME 300
#define FRAME 20

typedef enum animationType {
	IDLE,
	MOVE
} EAnimationType;

typedef struct animation {
	int count_FrameAnimation;
	int currentFrame;
	CP_Image imageFrame[FRAME];
	float frameDelay;
	float frameTimer;
	CP_Vector position;
} ANIMATION;

void init_Animation(ANIMATION* animation, char* filename, int count_FrameAnimation);

//void init_IDLEAnimation(ANIMATION* animation, char* filename, int count_FrameAnimation);
//
//void init_MOVEAnimation(ANIMATION* animation, char* filename, int count_FrameAnimation);
//
//void init_SHOOTAnimation(ANIMATION* animation, char* filename, int count_FrameAnimation);

void update_Animation(ANIMATION* animation, float df);

void print_Animation(ANIMATION* animation, CP_Vector position, float angle);