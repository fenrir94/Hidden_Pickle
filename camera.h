#pragma once

typedef struct mab {
	float minX;
    float maxX;
    float minY;
    float maxY;
} MAB;

CP_Vector initCamera(MAB* mab, CP_Vector mab_size);

void updateCamera(CP_Vector updateVector, float dt);

int checkCameraTrigger(PLAYER* player, CP_Vector updateVector);