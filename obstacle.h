#pragma once

#include "cprocessing.h"

typedef enum obstacle_Type {
	WALL
} EObstacleType;

typedef struct obstacle {
	CP_Vector position;
	float radius;
	EObstacleType obstacle_Type;
	int isCollided;
	int alpha;
} OBSTACLE;

void init_Obstacle(OBSTACLE* obstacle, CP_Vector position, EObstacleType obstacle_Type);

void print_Obstacles(OBSTACLE* obstacle, int count_Obstacle);

void print_Obstacle(OBSTACLE* obstacle);

void update_Alpha_Obstacle(OBSTACLE* obstacle, int isPlayerNear);

int checkNearPlayer_Obstacle(OBSTACLE* obstacle, CP_Vector positionPlayer, float radiusPlayer);