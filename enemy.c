
#include "stdlib.h"
#include "enemy.h"
#include "player.h"

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
	init_Footprint(&(enemy->footprint));
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
	enemy->vector_Sight = CP_Vector_Set(1,0); // TO Do need to fix for initialization
	init_Footprint(&(enemy->footprint));
}

void update_Enemy(ENEMY* enemy, float dt)
{
	patrol_Enemy(enemy, dt);
	
	// Need to check time to update, add and delete footprint
	float time_present = CP_System_GetSeconds();

	//update_Footprint(&(enemy->footprint), dt);

	// To Do need to fix
	if ( is_Empty(&(enemy->footprint)) ||  (time_present - enemy->footprint.generatedTime[enemy->footprint.rear]) >= GENTIMEGAP_FOOTPRINT ) {
		add_Footprint(&(enemy->footprint), enemy->position, enemy->vector_Sight);
	}

	//add_Footprint(&(enemy->footprint), enemy->position);
	checkDuration_Footprint(&(enemy->footprint), time_present);
}

void print_Enemy(ENEMY* enemy)
{
	/*CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(enemy->position.x, enemy->position.y, enemy->radius);*/
	print_Footprint(&(enemy->footprint));
}

void patrol_Enemy(ENEMY* enemy, float dt)
{
	int startPosition = enemy->destinationIndex - 1;
	if (enemy->destinationIndex == 0)
	{
		startPosition = enemy->patrolPoints - 1;
	}
	CP_Vector dPatrolPosition = CP_Vector_Set(enemy->destinations[enemy->destinationIndex].x - enemy->position.x, enemy->destinations[enemy->destinationIndex].y - enemy->position.y);

	CP_Vector dPatrolNormal = CP_Vector_Normalize(dPatrolPosition);
	enemy->position.x += enemy->speed * dPatrolNormal.x*dt;
	enemy->position.y += enemy->speed * dPatrolNormal.y*dt;

	enemy->vector_Sight = dPatrolNormal;

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

int check_Collision_Enemy_Object(ENEMY* enemy, CP_Vector position_Object, float radius_Object)
{
	return checkCollision_Circle_to_Circle(enemy->position, enemy->radius, position_Object, radius_Object);
}

void rollback_Move_Enemy_Position(ENEMY* enemy, CP_Vector updateVector, float dt)
{
	CP_Vector dPosition = CP_Vector_Scale(updateVector, dt * (enemy->speed));

	enemy->position = CP_Vector_Subtract(enemy->position, dPosition);

	CP_Vector dPosition_transpose = CP_Vector_Set(dPosition.y, -1*dPosition.x);

	enemy->position = CP_Vector_Subtract(enemy->position, dPosition_transpose);
}