#pragma once

#include <stdio.h>
#include "cprocessing.h"
#include "utility.h"

#define COUNT_FOOTPRINT 8
#define GENTIMEGAP_FOOTPRINT 1
#define ENDTIME_FOOTPRINT 5

// Footprint is an element of Enemy. 

typedef struct footprint {
	CP_Image imageFootLeft;
	CP_Image imageFootRight;
	CP_Vector position[COUNT_FOOTPRINT];
	float generatedTime[COUNT_FOOTPRINT];
	int alpha[COUNT_FOOTPRINT];
	float angle[COUNT_FOOTPRINT];
	int rear; 
	int front;
} FOOTPRINT;

// check queue
int is_Empty(FOOTPRINT* footprint);

int is_Full(FOOTPRINT* footprint);

void  add_Footprint(FOOTPRINT* footprint, CP_Vector position, CP_Vector vector_Sight);

void checkDuration_Footprint(FOOTPRINT* footprint);

void del_Footprint(FOOTPRINT* footprint);

void init_Footprint(FOOTPRINT* footprint);

void update_Footprint(FOOTPRINT* footprint, float dt);

void print_Footprint(FOOTPRINT* footprint);