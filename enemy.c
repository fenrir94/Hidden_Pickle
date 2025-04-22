
#include "stdlib.h"
#include "enemy.h"
#include "player.h"


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
	enemy->radius_Sight = 600;
	init_Footprint(&(enemy->footprint));
	enemy->enemyType = PATROL;
}

void update_Enemy(ENEMY* enemy, CP_Vector positon_player, float dt)
{
	if (enemy->enemyType == PATROL || enemy->enemyType == PATROL_ONLY) {
		patrol_Enemy(enemy, dt);
	}
	else if (enemy->enemyType == ATTACK_WAIT || enemy->enemyType == ATTACK_PATROL ) {
		printf("Chase!");
		chasePlayer_Enemy(enemy, positon_player);
		move_Enemy(enemy, dt);
	}
	else { // WAIT Detecting Rotate

	}
	
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

void move_Enemy(ENEMY* enemy, float dt) {
	enemy->position.x += enemy->speed * enemy->vector_Sight.x*dt;
	enemy->position.y += enemy->speed * enemy->vector_Sight.y*dt;
}

void patrol_Enemy(ENEMY* enemy, float dt)
{
	int startPosition = enemy->destinationIndex - 1;
	if (enemy->destinationIndex == 0)
	{
		startPosition = enemy->patrolPoints - 1;
	}
	CP_Vector dPatrolPosition = CP_Vector_Set(enemy->destinations[enemy->destinationIndex].x - enemy->position.x, enemy->destinations[enemy->destinationIndex].y - enemy->position.y);

	enemy->vector_Sight = CP_Vector_Normalize(dPatrolPosition);
	
	move_Enemy(enemy, dt);

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

	//enemy->vector_Sight = CP_Vector_Normalize(dPosition_transpose);

	/*changeAngle_Footprint(&(enemy->footprint), CP_Vector_Normalize(dPosition_transpose));*/

}

void check_DetectPlayer_Enemy(ENEMY* enemy, CP_Vector position_Player, float radius_Player)
{
	if (checkCollision_Circle_to_Circle(enemy->position, enemy->radius_Sight, position_Player, radius_Player)) {
		//printf("Chase Angle! %f\n", CP_Vector_Angle(enemy->vector_Sight, CP_Vector_Subtract(position_Player, enemy->position)));
		if (CP_Vector_Angle(enemy->vector_Sight, CP_Vector_Subtract(position_Player, enemy->position)) <= 60) {
			if (enemy->enemyType == WAIT) enemy->enemyType = ATTACK_WAIT;
			if (enemy->enemyType == PATROL) enemy->enemyType = ATTACK_PATROL;
		}
	} 
	else {
		if (enemy->enemyType == ATTACK_WAIT) enemy->enemyType = WAIT;
		if (enemy->enemyType == ATTACK_PATROL) enemy->enemyType = PATROL;
	}
}

void chasePlayer_Enemy(ENEMY* enemy, CP_Vector position_Player)
{
	CP_Vector chaseVector = CP_Vector_Subtract(position_Player, enemy->position);

	enemy->vector_Sight = CP_Vector_Normalize(chaseVector);

}

void getDamage_Enemy(ENEMY* enemy, int attackPoint)
{
}

