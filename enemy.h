#pragma once

#include <stdio.h>
#include "cprocessing.h"
#include "footprint.h"

//typedef struct CP_Vector_DL {
//	CP_Vector* preDestination;
//	CP_Vector destination;
//	CP_Vector* nextDestination;
//} CP_Vector_DL;

//CP_Vector_DL* insert_first(CP_Vector_DL* head, CP_Vector vector);
//CP_Vector_DL* insert_last(CP_Vector_DL* head, CP_Vector vector);


typedef struct enemy {
	CP_Vector position;
	int speed;
	int life;
	int attackPoint;
	float radius;
	CP_Vector vector_Sight;
	FOOTPRINT footprint;
	CP_Vector* destinations;
	int patrolPoints;
	int destinationIndex;
	//CP_Vector_DL* destinations;

} ENEMY;

void init_Enemy(ENEMY* enemy, CP_Vector startPosition);

void init_Enemy_Patrol(ENEMY* enemy, CP_Vector startPosition, CP_Vector* destination, int patrolPoints);

void update_Enemy(ENEMY* enemy, float dt);

void print_Enemy(ENEMY* enemy);

void patrol_Enemy(ENEMY* enemy, float dt);

int check_Collision_Enemy_Object(ENEMY* enemy, CP_Vector position_Object, float radius_Object);

void rollback_Move_Enemy_Position(ENEMY* enemy, CP_Vector updateVector, float dt);