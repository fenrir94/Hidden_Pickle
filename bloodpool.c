
#include "bloodpool.h"
#include "imageManager.h"

// init when object's life == 0
void init_Bloodpool(BLOODPOOL* bloodpool, CP_Vector position, float timeDuration)
{
	bloodpool->position = position;
	bloodpool->timeGenerated = CP_System_GetSeconds();
	bloodpool->size = 100;
	bloodpool->alpha = 200;
	bloodpool->timeDuration = timeDuration;
}

// update time to size up and reduce alpha value 
void update_Bloodpool(BLOODPOOL* bloodpool)
{
	// To Do change data
	if (CP_System_GetSeconds() - bloodpool->timeGenerated < bloodpool->timeDuration / 2) {
		if (bloodpool->size < 300) bloodpool->size++;

	}
	else if (CP_System_GetSeconds() - bloodpool->timeGenerated < bloodpool->timeDuration && CP_System_GetSeconds() - bloodpool->timeGenerated > bloodpool->timeDuration / 2) {
		if (bloodpool->alpha > 10) {
			bloodpool->alpha -= 1;
		}
	}
}


// get return value when animation ended
int getAnimationEnded_Bloodpool(BLOODPOOL* bloodpool)
{
	return CP_System_GetSeconds() - bloodpool->timeGenerated > bloodpool->timeDuration;
}

// print bloodpool
void print_Bloodpool(BLOODPOOL* bloodpool)
{
	if (CP_System_GetSeconds() - bloodpool->timeGenerated < bloodpool->timeDuration) {
		// TO DO Fix
		//CP_Settings_Fill(CP_Color_Create(bloodpool->hue, 0, 0, 255));
		//CP_Graphics_DrawCircle(bloodpool->position.x, bloodpool->position.y, (float)bloodpool->size);
		CP_Image_Draw(image_Manager.bloodpool, bloodpool->position.x, bloodpool->position.y, (float)bloodpool->size, (float)bloodpool->size, bloodpool->alpha);

	}

}
