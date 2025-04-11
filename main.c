#include "cprocessing.h"
#include "mainmenu.h"

int main(void)
{
	CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run();
	return 0;
}
