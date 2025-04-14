#pragma once

#include <stdio.h>
#include "cprocessing.h"

typedef struct footprint {
	float* generatedTime;
	int rear, front;
} FOOTPRINT;

void init_Footprint(FOOTPRINT* footprint);

void update_Footprint(float dt);

void print_Footprint(FOOTPRINT* footprint);