#include "utility.h"

CP_Vector getKeyVector(void)
{
	CP_Vector uVector = CP_Vector_Set(0, 0);

	if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_UP)) uVector.y--;
	if (CP_Input_KeyDown(KEY_S) || CP_Input_KeyDown(KEY_DOWN)) uVector.y++;
	if (CP_Input_KeyDown(KEY_A) || CP_Input_KeyDown(KEY_LEFT)) uVector.x--;
	if (CP_Input_KeyDown(KEY_D) || CP_Input_KeyDown(KEY_RIGHT)) uVector.x++;

	return uVector;
}
