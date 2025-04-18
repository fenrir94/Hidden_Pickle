
#include "player.h"
#include "utility.h"

void init_Player(PLAYER* player, CP_Vector startPosition) {
	player->position.x = startPosition.x;
	player->position.y = startPosition.y;
	player->speed = 200;
	player->life = 3;
	player->radius = 50;
	player->getKey = 0;
	player->battery = 30;
	player->time_Hit = 0;
}

void update_Player(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Add(player->position, dPoistion);
}

void rollback_Player_Position(PLAYER* player, CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Subtract(player->position, dPoistion);
}

int check_Collision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, position_Object, radius_Object);
}


int isInvincibility(PLAYER* player, float dt)
{
	if (dt - player->time_Hit <= TIME_INVINCIBILITY) {
		return 1;
	}
	else {
		return 0;
	}
}


void get_Player_Hit(PLAYER* player, int attackPoint) {
	float time_Present = CP_System_GetSeconds();
	if (isInvincibility(player, time_Present) == 0) {
		player->life -= attackPoint;
		player->time_Hit = time_Present;
	}
	
}

void get_Item(PLAYER* player, EItemType item_type) {
	printf("Get Item! %d\n", item_type);
	if (item_type == KEY_Item)
	{
		player->getKey = 1;
		printf("Get Key! %d\n", player->getKey);
	}
	else if (item_type == BULLET_Item)
	{
		if (player->gun.bullets + 6 > MAX_BULLET) {
			player->gun.bullets = MAX_BULLET;
		}
		player->gun.bullets += 6;
	}
	else if (item_type == BATTERY_Item)
	{
		if (player->battery + 50 > MAX_BATTERY) {
			player->battery = MAX_BATTERY;
		}
		player->battery += 40;
	}
}

void print_Player(PLAYER* player) {
	float time_present = CP_System_GetSeconds();
	if ((int)((time_present - player->time_Hit) * 10) % 2 != 1 && time_present - player->time_Hit <= TIME_INVINCIBILITY) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	}
	else {
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	}
	
	
	CP_Graphics_DrawCircle(player->position.x, player->position.y, player->radius);

	print_Player_Life(player->life);
	print_Plyaer_Lamp(player->battery);
}





void print_Player_Life(int life) {
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	int gap = 100;

	for (int i = 0; i < life; i++) {
		CP_Graphics_DrawCircle(50+(float)i*gap, 50, 80);
	}
}

void print_Plyaer_Lamp(int battery)
{
	CP_Settings_RectMode(CP_POSITION_CORNER);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(30,100,202,32);

	//CP_Settings_Fill(CP_Color_Create(255, 0, 255, 0));
	//CP_Graphics_DrawRect(31, 101, 200, 30);

	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Graphics_DrawRect(31, 101, (float)battery*2, 30);

	CP_Settings_RectMode(CP_POSITION_CENTER);

}


