#pragma once

#include <stdio.h>
#include "cprocessing.h"

typedef struct exit_Place {
	CP_Vector position;
	float radius;
} EXIT_PLACE;

void init_Exit_Place(EXIT_PLACE* exit_Place, CP_Vector position);


void print_Exit_Place(EXIT_PLACE* exit_Place);