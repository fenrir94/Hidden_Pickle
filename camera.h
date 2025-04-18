#pragma once

void initCamera(void);

void updateCamera(CP_Vector updateVector, float dt);

int checkCameraTrigger(PLAYER* player, CP_Vector updateVector);

void printVisionblocker(CP_Image* visionblockerOff, CP_Image* visionblockerOn, int useBattery);