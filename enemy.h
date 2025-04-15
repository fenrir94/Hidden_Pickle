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
	CP_Vector vector_sight;
	FOOTPRINT footprint;
	CP_Vector* destinations;
	int patrolPoints;
	int destinationIndex;
	//CP_Vector_DL* destinations;

} ENEMY;

void init_Enemy(ENEMY* enemy, CP_Vector startPosition);

void init_Enemy_Patrol(ENEMY* enemy, CP_Vector startPosition, CP_Vector* destination, int patrolPoints);

void updateEnemy(ENEMY* enemy, float dt);

void printEnemy(ENEMY* enemy);

void patrolEnemy(ENEMY* enemy, float dt);