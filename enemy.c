#include <stdio.h>
#include "stdlib.h"
#include "cprocessing.h"
#include "enemy.h"

//CP_Vector_DL* insert_first(CP_Vector_DL* head, CP_Vector vector)
//{
//	CP_Vector_DL* node = malloc(sizeof(CP_Vector_DL));
//	node->preDestination = head;
//	node->destination = vector;
//	node->nextDestination = head->nextDestination;
//
//	if (head == NULL) {
//		head = node;
//		head->nextDestination = head;
//	}
//	else {
//		node->nextDestination = head->nextDestination;
//		head->nextDestination = node;
//	}
//
//	return head;
//}
//
//CP_Vector_DL* insert_last(CP_Vector_DL* head, CP_Vector vector)
//{
//	CP_Vector_DL* node = malloc(sizeof(CP_Vector_DL));
//	node->destination = vector;
//
//	if (head == NULL) {
//		head = node;
//		node->nextDestination = head;
//	}
//	else {
//		node->nextDestination = head->nextDestination;
//		head->nextDestination = node;
//	}
//
//	return head;
//}

void init_Enemy(ENEMY* enemy, CP_Vector startPosition)
{
	enemy->position = CP_Vector_Set(startPosition.x, startPosition.y);
	enemy->life = 1;
	enemy->speed = 8;
	enemy->attackPoint = 1;
	enemy->radius = 100;
}

void init_Enemy_Patrol(ENEMY* enemy, CP_Vector startPosition, CP_Vector* destinations, int patrolPoints)
{
	enemy->position = CP_Vector_Set(startPosition.x, startPosition.y);
	enemy->life = 1;
	enemy->speed = 100;
	enemy->attackPoint = 1;
	enemy->radius = 100;
	enemy->destinations = destinations;
	enemy->patrolPoints = patrolPoints;
	enemy->destinationIndex = 1;
}

void updateEnemy(ENEMY* enemy, float dt)
{
	patrolEnemy(enemy, dt);
}

void printEnemy(ENEMY* enemy)
{
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(enemy->position.x, enemy->position.y, enemy->radius);
}

void patrolEnemy(ENEMY* enemy, float dt)
{
	int startPosition = enemy->destinationIndex - 1;
	if (enemy->destinationIndex == 0)
	{
		startPosition = enemy->patrolPoints - 1;
	}
	CP_Vector dPatrolPosition = CP_Vector_Set(enemy->destinations[enemy->destinationIndex].x - enemy->destinations[startPosition].x, enemy->destinations[enemy->destinationIndex].y - enemy->destinations[startPosition].y);

	CP_Vector dPatrolNormal = CP_Vector_Normalize(dPatrolPosition);
	enemy->position.x += enemy->speed * dPatrolNormal.x*dt;
	enemy->position.y += enemy->speed * dPatrolNormal.y*dt;

	// Change Destination
	if ((dPatrolPosition.x <= 0 && enemy->destinations[enemy->destinationIndex].x >= enemy->position.x) || (dPatrolPosition.x >= 0 && enemy->destinations[enemy->destinationIndex].x <= enemy->position.x)) {
		if ((dPatrolPosition.y <= 0 && enemy->destinations[enemy->destinationIndex].y >= enemy->position.y) || (dPatrolPosition.y >= 0 && enemy->destinations[enemy->destinationIndex].y <= enemy->position.y)) {
			if (enemy->destinationIndex >= enemy->patrolPoints - 1) enemy->destinationIndex = 0;
			else {
				enemy->destinationIndex++;
			}
		}
	}
}

