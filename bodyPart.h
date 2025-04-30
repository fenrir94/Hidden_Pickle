#pragma once

#include "cprocessing.h"
#include "animation.h"


typedef struct body_Part {
	int count_Animation;
	ANIMATION* animation;
	EAnimationType animation_Type;
}BODY_PART;

//void init_Body_Part(BODY_PART* body_Part, int count_Animation);

void init_Body_BodyPart(BODY_PART* body_Part, int count_Animation);

void init_Feet_BodyPart(BODY_PART* body_Part, int count_Animation);

void changeAnimation_BodyPart(BODY_PART* body_Part, EAnimationType animation_Type);

void update_BodyPart(BODY_PART* body_Part, float dt);

void print_Body_BodyPart(BODY_PART* body_Part, CP_Vector position, float angle);

void print_Feet_BodyPart(BODY_PART* body_Part, CP_Vector position, float angle);