
#include "player.h"
#include "utility.h"

void init_Player(PLAYER* player, CP_Vector startPosition) {
	player->position.x = startPosition.x;
	player->position.y = startPosition.y;
	player->speed = 200;
	player->life = 3;
	player->radius = 50;
	player->getKey = 0;
}

void update_Player(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Add(player->position, dPoistion);
}


int check_Collision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, position_Object, radius_Object);
}

void get_Player_Hit(PLAYER* player, int attackPoint) {
	player->life -= attackPoint;
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
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player->position.x, player->position.y, player->radius);
}


