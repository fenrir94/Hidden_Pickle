
#include "obstacle.h"
#include "imageManager.h"

void init_Obstacle(OBSTACLE* obstacle, CP_Vector position, EObstacleType obstacle_Type)
{
	obstacle->position = CP_Vector_Set(position.x, position.y);
	obstacle->radius = 100; // TO DO Need to Change
	obstacle->obstacle_Type = obstacle_Type;
	obstacle->isCollided = 0;
	obstacle->alpha = 255;
	obstacle->indexTree = CP_Random_GetInt() % 4;
	
	obstacle->imageObstacle = image_Manager.tree[obstacle->indexTree];
}

void update_Alpha_Obstacle(OBSTACLE* obstacle, int isPlayerNear) {
	if (isPlayerNear)
	{
		obstacle->alpha = 125;
	}
	else {
		obstacle->alpha = 255;
	}
}

int checkNearPlayer_Obstacle(OBSTACLE* obstacle, CP_Vector positionPlayer, float radiusPlayer)
{
	if (CP_Vector_Distance(obstacle->position, positionPlayer) < obstacle->radius * 1.5 + radiusPlayer) {
		return 1;
	}
	else {
		return 0;
	}
}


void print_Obstacles(OBSTACLE* obstacle, int count_Obstacle)
{
	for (int i = 0; i < count_Obstacle; i++) {
		print_Obstacle(&obstacle[i]);
	}
}

void print_Obstacle(OBSTACLE* obstacle)
{
	CP_Image_Draw(obstacle->imageObstacle, obstacle->position.x, obstacle->position.y, obstacle->radius * 2, obstacle->radius * 2, obstacle->alpha);
	
}
