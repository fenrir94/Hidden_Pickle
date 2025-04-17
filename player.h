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
	float time_Hit;
} PLAYER;

void init_Player(PLAYER* player, CP_Vector startPosition);

void update_Player(PLAYER* player, CP_Vector updateVector, float dt);

void rollback_Player_Position(PLAYER* player, CP_Vector updateVector, float dt);

int check_Collision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object);

void get_Player_Hit(PLAYER* player, int attackPoint);



void get_Item(PLAYER* player, EItemType item_type);

void print_Player_Life(int life);

void print_Plyaer_Lamp(int battery);

void print_Player(PLAYER* player);



