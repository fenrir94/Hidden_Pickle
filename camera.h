#pragma once

typedef struct map {
	float minX;
    float maxX;
    float minY;
    float maxY;
} MAP;

CP_Vector init_Camera(MAP* map, CP_Vector map_size);

void update_Camera(MAP* map, CP_Vector updateVector, float dt);

int checkCameraTrigger(PLAYER* player, CP_Vector updateVector);