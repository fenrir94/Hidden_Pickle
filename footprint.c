
#include "footprint.h"

int is_Empty(FOOTPRINT* footprint)
{
	return footprint->front == footprint->rear;
}

int is_Full(FOOTPRINT* footprint) {
	return footprint->front == (footprint->rear+1) % COUNT_FOOTPRINT;
}

void init_Footprint(FOOTPRINT* footprint) {
	footprint->rear = footprint->front = -1;
}

void add_Footprint(FOOTPRINT* footprint, CP_Vector position, CP_Vector vector_Sight) {
	if (is_Full(footprint)) {
		return;
	}
	else {
		footprint->rear = (footprint->rear + 1) % COUNT_FOOTPRINT;
		
		footprint->position[footprint->rear] = CP_Vector_Set(position.x, position.y);
		footprint->generatedTime[footprint->rear] = CP_System_GetSeconds();
		
		CP_Vector vector_X_Norm = CP_Vector_Set(1, 0);
		footprint->angle[footprint->rear] = CP_Vector_Angle(vector_Sight, vector_X_Norm);

		// TO DO Need to Change if Change Coordinate 
		if (vector_Sight.y > 0) footprint->angle[footprint->rear] -= 90;
		else {
			footprint->angle[footprint->rear] = 90 - footprint->angle[footprint->rear];
		}

		
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
// To do 
// Dump
void update_Footprint(FOOTPRINT* footprint, float dt)
{
	int i = footprint->front;
	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		footprint->generatedTime[i] += dt;
		
	}
}


void checkDuration_Footprint(FOOTPRINT* footprint, float time_present)
{
	int i = footprint->front;

	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		if ((time_present - footprint->generatedTime[i]) >= ENDTIME_FOOTPRINT) {
			del_Footprint(footprint);
		}
	}

}

void print_Footprint(FOOTPRINT* footprint)
{
	// TO DO Change to Image
	CP_Settings_RectMode(CP_POSITION_CENTER);

	float time_present = CP_System_GetSeconds();

	int i = footprint->front;
	while (i != footprint->rear) {
		i = (i + 1) % COUNT_FOOTPRINT;
		float time_footprint_duration = time_present - footprint->generatedTime[i];
		if (time_footprint_duration < ENDTIME_FOOTPRINT) {
			int alpha = 255 - (int)time_footprint_duration*50;
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, alpha));
			//CP_Graphics_DrawRect(footprint->position[i].x, footprint->position[i].y, 50, 50);
			CP_Graphics_DrawRectAdvanced(footprint->position[i].x, footprint->position[i].y, 50, 100, footprint->angle[i], 0);
		}
	}
}