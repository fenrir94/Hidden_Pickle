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

void update_Light(LIGHT* light, float dt)
{
	
 	if (light->lightState == off)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x - light_Width * (dt * 10), light_Width, (light_Width * 2));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y - light_Height * (dt * 10), light_Height, (light_Height * 2));
	}
	else if (light->lightState == on)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x + light_Width * (dt * 20), light_Width, (light_Width * 2));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y + light_Height * (dt * 20), light_Height, (light_Height * 2));
	}
	else if (light->lightState == end)
	{
		game_Manager.light.lightSize.x = clamp(game_Manager.light.lightSize.x + (light_Width * 7) * dt, light_Width, (light_Width * 8));
		game_Manager.light.lightSize.y = clamp(game_Manager.light.lightSize.y + (light_Height * 7) * dt, light_Height, (light_Height * 8));
	}
}

void turn_On_Light(LIGHT* light, int checkLampOn)
{
	if (checkLampOn == 1)
	{
		light->lightState = on;
	}
	else
	{
		light->lightState = off;
	}
}

void printVisionblocker(LIGHT* light)
{
	//CP_Image_Draw(light->lightImage, (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, light->lightSize.x, light->lightSize.y, 215);
	//CP_Image_Draw(light->lightImage, (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, light->lightSize.x * 7 / 8, light->lightSize.y * 7 / 8, 127);
}