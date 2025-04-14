#pragma once

#include <stdio.h>
#include "cprocessing.h"

#define BASIC_LIFE = 3;

typedef struct player {
	CP_Vector position;
	int speed;
	int life;
	float radius;
} PLAYER;

void init_Player(PLAYER* player, CP_Vector startPosition);

void updatePlayer(PLAYER* player, CP_Vector updateVector, float dt);

void printPlayer(PLAYER* player);