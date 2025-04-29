
#include "bloodpool.h"

// init when object's life == 0
void init_Bloodpool(BLOODPOOL* bloodpool, CP_Vector position)
{
	bloodpool->position = position;
	bloodpool->time_Generated = CP_System_GetSeconds();
	bloodpool->size = 0;
	bloodpool->alpha = 255;
}

// update time to size up and reduce alpha value 
void update_Bloodpool(BLOODPOOL* bloodpool)
{
	// To Do change data
	float time_Present = CP_System_GetSeconds();
	if (time_Present - bloodpool->time_Generated <= 3 ) {
		bloodpool->size++;
	}
	else {
		bloodpool->alpha -= 10;
	}
}

// get return value when animation ended
int getAnimationEnded(BLOODPOOL* bloodpool)
{
		
	return CP_System_GetSeconds() - bloodpool->time_Generated > 6;
}

// print bloodpool
void print_Bloodpool(BLOODPOOL* bloodpool)
{
	// TO DO Fix
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, bloodpool->alpha));
	CP_Graphics_DrawCircle(bloodpool->position.x, bloodpool->position.y, (float)bloodpool->size);
}
