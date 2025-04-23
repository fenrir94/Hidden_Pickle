#pragma once

#include "cprocessing.h"

#define DELAY_FRAME 300


typedef enum type_Animation {
	IDLE,
	MOVE
} TYPE_ANIMATION;

typedef struct animation {
	int count_FrameAnimation;
	int currentFrame;
	CP_Image imageFrame[20];
	int frameDelay;
	int frameTimer;
	CP_Vector position;
} ANIMATION;

void init_Animation(ANIMATION* animation);

void update_Animation(ANIMATION* animation, float dt);

void print_Animation(ANIMATION* animation);