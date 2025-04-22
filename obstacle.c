
#include "obstacle.h"

void init_Obstacle(OBSTACLE* obstacle, CP_Vector position, EObstacleType obstacle_Type)
{
	obstacle->position = CP_Vector_Set(position.x, position.y);
	obstacle->radius = 100; // TO DO Need to Change
	obstacle->obstacle_Type = obstacle_Type;
	obstacle->isCollided = 0;
}

void print_Obstacles(OBSTACLE* obstacle, int count_Obstacle)
{
	for (int i = 0; i < count_Obstacle; i++) {
		print_Obstacle(obstacle+i);
	}
}

void print_Obstacle(OBSTACLE* obstacle)
{
	CP_Settings_Fill(CP_Color_Create(165, 42, 42, 255));
	CP_Graphics_DrawCircle(obstacle->position.x, obstacle->position.y, obstacle->radius);
}
