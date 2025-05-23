#include "utility.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"

CP_Vector get_InputVector(void)
{
	CP_Vector uVector = CP_Vector_Set(0, 0);

	if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_UP)) uVector.y--; // 좌상단이 (0,0)
	if (CP_Input_KeyDown(KEY_S) || CP_Input_KeyDown(KEY_DOWN)) uVector.y++;
	if (CP_Input_KeyDown(KEY_A) || CP_Input_KeyDown(KEY_LEFT)) uVector.x--;
	if (CP_Input_KeyDown(KEY_D) || CP_Input_KeyDown(KEY_RIGHT)) uVector.x++;

	return uVector;
}

// Check Collision of 2 Circles
// To Do 
// Need to Check Collision
int checkCollision_Circle_to_Circle(CP_Vector position_Left, float radius_Left, CP_Vector position_Right, float radius_Right)
{
	float distanceVectors = CP_Vector_Distance(position_Left, position_Right);
	//float distanceVectors = CP_Vector_Length(CP_Vector_Subtract(position_Left, position_Right));
	if (distanceVectors <= (radius_Left + radius_Right)/2) {
		//printf("Collided!  distance:  %f, sum of radius:   %f\n", distanceVectors, radius_Left + radius_Right);
		return 1;
	}
	else {
		return 0;
	}
	
}


float clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	else if (max < value)
	{
		return max;
	}
	else
	{
		return value;
	}
}

int get_InputSpace(void)
{
	int count_Space = 0;
	if (CP_Input_KeyDown(KEY_SPACE)) count_Space++;
	
	return count_Space;

}

float getAngle_Vector_AxisX(CP_Vector vector)
{
	CP_Vector vector_X_Norm = CP_Vector_Set(1, 0);
	float angle = CP_Vector_AngleCCW(vector, vector_X_Norm);
	//printf("Angle! %f\n", footprint->angle[footprint->rear]);
	angle = 90 - angle;
	 //TO DO Need to Change if Change Coordinate 
	/*if (vector.y > 0) angle -= 90;
	else {
		angle = 90 - angle;
	}*/
	return angle;
}

CP_Vector getMousePosition(void)
{
	return CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

int isMouseInsideRect(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
// 사각형 범위 감지 함수
{
	if (area_center_x - area_width / 2 < click_x && click_x < area_center_x + area_width / 2 &&
		area_center_y - area_height / 2 < click_y && click_y < area_center_y + area_height / 2)
	{
		return 1;

	}

	return 0;
}

int isMouseInsideCircle(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
// 원형 범위 감지 함수
{
	if (pow(click_x - circle_center_x, 2.0) + pow(click_y - circle_center_y, 2.0) <= pow(diameter / 2, 2.0))
	{
		return 1;
	}

	return 0;
}

void centeredCoordinate(float* x, float* y)
// 좌표 이동 함수 (0,0)이 중심이 되도록
{
	*x += (float)CP_System_GetWindowWidth() / 2;

	*y *= -1;

	*y += (float)CP_System_GetWindowHeight() / 2;
}


void intToCharArray(int num, char* buffer) {
	if (num < 10) {
		buffer[0] = '0' + (char)(num % 10);
		buffer[1] = '\0';
	}
	else {
		buffer[0] = '0' + (char)(num / 10);
		buffer[1] = '0' + (char)(num % 10);
		buffer[2] = '\0';
	}
}


CP_Image* LoadImagesFromAssets(int count, const char* pathFormat)
{
	CP_Image* imageList = (CP_Image*)malloc(count * sizeof(CP_Image));

	char buffer[100];
	for (int i = 0; i < count; i++)
	{
		sprintf_s(buffer, sizeof(buffer), pathFormat, i);
		imageList[i] = CP_Image_Load(buffer);
	}

	return imageList;
}

// 동적 할당된 메모리를 해제하는 함수
void FreeAllocatedImages(CP_Image* imageList)
{
	if (imageList != NULL)
	{
		free(imageList);  // 메모리 해제
	}

}

double deg_to_rad(float degree)
{
	return degree*(M_PI/180.0f);
}