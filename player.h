#pragma once

#include <stdio.h>
#include "cprocessing.h"
#include "itemBox.h"

#define BASIC_LIFE 3

typedef struct player {
	CP_Vector position;
	int speed;
	int life;
	float radius;
	int getKey;
	GUN gun;
	int battery;
} PLAYER;

void init_Player(PLAYER* player, CP_Vector startPosition);

void updatePlayer(PLAYER* player, CP_Vector updateVector, float dt);

int checkCollision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object);

void getPlayerHit(PLAYER* player, int attackPoint);

void printPlayer(PLAYER* player);