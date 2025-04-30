#pragma once

#include <stdio.h>
#include "cprocessing.h"
#include "itemBox.h"
#include "gun.h"
#include "animation.h"
#include "bodyPart.h"
#include "utility.h"
#include "bloodpool.h"	

#define BASIC_LIFE 3
#define TIME_INVINCIBILITY 1
#define COUNT_PARTS_PLAYER 2

typedef struct player {
	CP_Vector position;
	CP_Vector worldPos;
	int speed;
	int life;
	float radius;
	int getKey;
	GUN gun;
	int battery;
	int isLampOn;
	float time_Hit;
	CP_Vector shooting_Vector;
	int isAiming;
	BODY_PART feet;
	BODY_PART body;
	BLOODPOOL bloodpool;
} PLAYER;

void init_Player(PLAYER* player, CP_Vector startPosition);

void update_Player(PLAYER* player, CP_Vector updateVector, float dt);

void rollback_Player_Position(PLAYER* player, CP_Vector updateVector, float dt);

int check_Collision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object);

void getDamage_Player(PLAYER* player, int attackPoint);

void get_Item(PLAYER* player, EItemType item_type);

void use_Battery(PLAYER* player);

void checkAiming_Player(PLAYER* player, CP_KEY key, CP_KEY mouse);

int shootingBullet_Player(PLAYER* player, CP_KEY key, CP_KEY mouse);

void print_Player_Life(PLAYER* player, int life);

void print_Player_Battery(PLAYER* player, int battery);

void print_Player_Bulltet_UI(PLAYER* player, int bullet);

void print_Player(PLAYER* player);

int isInvincibility(PLAYER* player, float dt);

void rotate_Player(PLAYER* player);

void print_Player_Aiming(PLAYER* player, CP_Vector vector_Gun);