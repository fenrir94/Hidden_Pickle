#include "cprocessing.h"
#include "light.h"
#include "gameManager.h"
#include "utility.h"

float light_Width;
float light_Height;

void init_Light(LIGHT* light)
{
	light_Width = (float)CP_System_GetWindowWidth() * 2;
	light_Height = (float)CP_System_GetWindowHeight() * 2;

	light->lightImage = CP_Image_Load("./Assets/Image/transparent_center_200.png");
	light->lightSize = CP_Vector_Set(light_Width, light_Height);
	light->lightState = off;
}

void update_Light(int lightState)
{
 	if (lightState == off)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x - 300, light_Width, (light_Width * 2));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y - 150, light_Height, (light_Height * 2));
	}
	else if (lightState == on)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x + 300, light_Width, (light_Width * 2));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y + 150, light_Height, (light_Height * 2));
	}
	else if (lightState == end)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x + 300, light_Width, (light_Width * 9));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y + 150, light_Height, (light_Height * 9));
	}
}

void printVisionblocker(LIGHT* light, int checkLampOn)
{

	if (checkLampOn == 1) 
	{
		light->lightState = on;
		update_Light(light->lightState);
	}
	else
	{
		light->lightState = off;
		update_Light(light->lightState);
	}


	CP_Image_Draw(light->lightImage, (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, light->lightSize.x, light->lightSize.y, 255);
}