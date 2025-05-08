
#include "footprint.h"
#include "imageManager.h"

int is_Empty(FOOTPRINT* footprint)
{
	return footprint->front == footprint->rear;
}

int is_Full(FOOTPRINT* footprint) {
	return footprint->front == (footprint->rear+1) % COUNT_FOOTPRINT;
}

void init_Footprint(FOOTPRINT* footprint) {
	footprint->imageFootLeft = image_Manager.imageFootLeft_Patrol;
	footprint->imageFootRight = image_Manager.imageFootLeft_Patrol;
	footprint->rear = footprint->front = -1;
}

void add_Footprint(FOOTPRINT* footprint, CP_Vector position, CP_Vector vector_Sight) {
	if (is_Full(footprint)) {
		return;
	}
	else {
		footprint->rear = (footprint->rear + 1) % COUNT_FOOTPRINT;
		footprint->position[footprint->rear] = CP_Vector_Set(position.x, position.y);
		footprint->generatedTime[footprint->rear] = 0;
		footprint->alpha[footprint->rear] = 255;
		
		footprint->angle[footprint->rear] = getAngle_Vector_AxisX(vector_Sight);
		
		printf("Queue Added in [%d] at %.2f\n", footprint->rear, footprint->generatedTime[footprint->rear]);
	}
}

void del_Footprint(FOOTPRINT* footprint) {
	if (is_Empty(footprint)) {
		return;
	}
	else {
		footprint->front = (footprint->front + 1) % COUNT_FOOTPRINT;
	}
}

// each footprint adds dt 
void update_Footprint(FOOTPRINT* footprint, float dt)
{
	int i = footprint->front;

	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		footprint->generatedTime[i] += dt;
		printf("time: %f", footprint->generatedTime[i]);
		
		footprint->alpha[i] = 255 - (int)footprint->generatedTime[i]*50;
	}
}


void checkDuration_Footprint(FOOTPRINT* footprint)
{
	int i = footprint->front;

	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		if (footprint->generatedTime[i] >= ENDTIME_FOOTPRINT) {
			del_Footprint(footprint);
		}
	}

}

void print_Footprint(FOOTPRINT* footprint)
{
	// TO DO Change to Image
	CP_Settings_RectMode(CP_POSITION_CENTER);
	
	int i = footprint->front;
	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		if (footprint->generatedTime[i] < ENDTIME_FOOTPRINT) {
			if (i % 2 == 0) {
				CP_Image_DrawAdvanced(footprint->imageFootLeft, footprint->position[i].x, footprint->position[i].y, (float)CP_Image_GetWidth(footprint->imageFootLeft), (float)CP_Image_GetHeight(footprint->imageFootLeft), footprint->alpha[i], footprint->angle[i]);
			
			} 
			else {
				CP_Image_DrawAdvanced(footprint->imageFootRight, footprint->position[i].x, footprint->position[i].y, (float)CP_Image_GetWidth(footprint->imageFootRight), (float)CP_Image_GetHeight(footprint->imageFootRight), footprint->alpha[i], footprint->angle[i]);
				
			}
		}
	}
}

