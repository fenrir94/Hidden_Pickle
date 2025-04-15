#pragma once

void initCamera(void);

void updateCamera(CP_Vector updateVector, float dt);

int checkCameraTrigger(PLAYER* player, CP_Vector updateVector);