#pragma once

/*
* This is a header file about utility functions such as key input
* 
*/

#include <stdio.h>
#include "cprocessing.h"

CP_Vector get_InputVector(void);

/*
* TO DO LIST
* 
* Calculate Angle by CP_Vector of 2 Vector to X Axis
* 
* float angle(CP_Vector start, CP_Vector dest);
* 
*/

int checkCollision_Circle_to_Circle(CP_Vector position_Left, float radius_Left, CP_Vector position_Right, float radius_Right);


//int isCollided_Circle_to_Rect(CP_Vector position_Circle, float radius, CP_Vector position_Right, float radius_Right);

float clamp(float value, float min, float max);