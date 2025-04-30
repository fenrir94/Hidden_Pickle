#pragma once

#include <stdio.h>
#include <math.h>
#include "cprocessing.h"
#include "itemBox.h"
#include "utility.h"


#define TIME_BULLLET 2

typedef struct gun {
	CP_Vector position_Gun;
	float length_Vector_Gun;
	float angle_Gun;
	CP_Vector position_Bullet[MAX_BULLET];
	CP_Vector vector_Shooting[MAX_BULLET];
	float time_Shooting[MAX_BULLET];
	int count_Bullet;
	float radius_Bullet;
	float speed_Bullet;
	int attackPoint;
	//float range; // Shooting Range
} GUN;

void init_Gun(GUN* gun, CP_Vector vector_Shooting);

int getIndexEmptyBullet(GUN* gun);

void addBullet_Gun(GUN* gun, CP_Vector startPosition, CP_Vector vectorShooting, int indexEmpty);

void update_Gun(GUN* gun, CP_Vector position_Player, CP_Vector vector_Shooting, float dt);

int checkCollision_Bullet_Object(GUN* gun, CP_Vector positionObject, float radius);

void printBullet(GUN* gun, CP_Vector position_Player, float angle);

void endBullet(GUN* gun, int indexBullet);

int isBulletShooting(float time_Shooting);