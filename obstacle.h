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
} OBSTACLE;

void init_Obstacle(OBSTACLE* obstacle, CP_Vector position, EObstacleType obstacle_Type);

void print_Obstacles(OBSTACLE* obstacle, int count_Obstacle);

void print_Obstacle(OBSTACLE* obstacle);