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

void update_Light(LIGHT* light, float dt);

void turn_On_Light(LIGHT* light, int checkLampOn);

void printVisionblocker(LIGHT* light);