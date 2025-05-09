#pragma once

#include <stdio.h>
#include "cprocessing.h"


typedef struct bloodpool {
	CP_Vector position;
	float timeGenerated;
	int size;
	int alpha;
	float timeDuration;
} BLOODPOOL;


void init_Bloodpool(BLOODPOOL* bloodpool, CP_Vector position, float timeDuration);

void update_Bloodpool(BLOODPOOL* bloodpool);

int getAnimationEnded_Bloodpool(BLOODPOOL* bloodpool);

void print_Bloodpool(BLOODPOOL* bloodpool);