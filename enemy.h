#pragma once

#include <stdio.h>
#include "cprocessing.h"
#include "footprint.h"


typedef enum enemy_Type{
	WAIT,
	PATROL,
	PATROL_ONLY,
	ATTACK_WAIT,
	ATTACK_PATROL
} ENEMY_TYPE;

typedef struct enemy {
	CP_Vector position;
	int speed;
	int life;
	int attackPoint;
	float attackRange; // Enemy Attack Collision
	float radius; // Enemy Collision
	CP_Vector vector_Sight;
	float radius_Sight; // Enemy Dectecton Collision
	FOOTPRINT footprint;
	CP_Vector* destinations;
	int patrolPoints;
	int destinationIndex;
	ENEMY_TYPE enemyType;
	//CP_Vector_DL* destinations;

} ENEMY;

void init_Enemy(ENEMY* enemy, CP_Vector startPosition);

void init_Enemy_Patrol(ENEMY* enemy, CP_Vector startPosition, CP_Vector* destination, int patrolPoints);

void update_Enemy(ENEMY* enemy, CP_Vector positon_player, float dt);

void print_Enemy(ENEMY* enemy);

void move_Enemy(ENEMY* enemy, float dt);

void patrol_Enemy(ENEMY* enemy, float dt);

int check_Collision_Enemy_Object(ENEMY* enemy, CP_Vector position_Object, float radius_Object);

void rollback_Move_Enemy_Position(ENEMY* enemy, CP_Vector updateVector, float dt); 

void check_DetectPlayer_Enemy(ENEMY* enemy, CP_Vector position_Player, float radius_Player);

void chasePlayer_Enemy(ENEMY* enemy, CP_Vector position_Player);