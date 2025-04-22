#pragma once

typedef struct minimab {
	CP_Vector playerIconPosition;
	CP_Vector exitIconPosition;
	CP_Vector* itemIconPosition;
	CP_Vector* obstacleIconPosition;
} MINIMAB;

void initMinimab(MINIMAB* minimab, CP_Vector mab_size, CP_Vector initVector);

void updateMinimab(CP_Vector updateVector, float dt);

void printMinimab(void);

void rollback_Player_Icon_Position(MINIMAB* minimab, CP_Vector updateVector, float dt);