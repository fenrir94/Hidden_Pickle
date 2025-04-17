
#include "exitPlace.h"

void init_Exit_Place(EXIT_PLACE* exit_Place, CP_Vector position)
{
	exit_Place->position = CP_Vector_Set(position.x, position.y);
	exit_Place->radius = 150;
}

void print_Exit_Place(EXIT_PLACE* exit_Place)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 125));
	CP_Graphics_DrawCircle(exit_Place->position.x, exit_Place->position.y, exit_Place->radius);
}
