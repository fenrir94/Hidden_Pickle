#include "utility.h"

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
