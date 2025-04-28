#pragma once

typedef enum light_State {
	off,
	on,
	end
} ElightState;

typedef struct light {
	CP_Image lightImage;
	CP_Vector lightSize;
	ElightState lightState;
} LIGHT;

void init_Light(LIGHT* light);

void update_Light(int lightState);

void printVisionblocker(LIGHT* light, int checkLampOn);