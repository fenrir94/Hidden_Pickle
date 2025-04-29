#pragma once

#include "cprocessing.h"


typedef struct bloodpool {
	CP_Vector position;
	float time_Generated;
} BLOODPOOL;


void init_Bloodpool(BLOODPOOL* bloodpool, CP_Vector position);

void update_Bloodpool(BLOODPOOL* bloodpool, float dt);

int getAnimationEnded(BLOODPOOL* bloodpool);

void print_Bloodpool(BLOODPOOL* bloodpool);