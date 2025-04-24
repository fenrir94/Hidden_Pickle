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

int get_InputSpace(void);

float getAngle_Vector_AxisX(CP_Vector vector);

CP_Vector getMousePosition(void);

int isMouseInsideRect(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
// 사각형 범위 클릭 감지 함수

int isMouseInsideCircle(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
// 원형 범위 클릭 감지 함수

void centeredCoordinate(float* x, float* y);
/* 좌표 이동 함수 (0,0)이 중심이 되도록
x = [-(float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowWidth() / 2]
-900 ~ 900
y = [-(float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowHeight() / 2]
-450 ~ 450
*/

CP_Image* LoadImagesFromAssets(int count, const char* pathFormat);

void FreeAllocatedImages(CP_Image* imageList);