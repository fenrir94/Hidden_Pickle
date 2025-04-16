
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

void updatePlayer(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Add(player->position, dPoistion);
}


int checkCollision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, position_Object, radius_Object);
}

void getPlayerHit(PLAYER* player, int attackPoint) {
	player->life -= attackPoint;
}

void getItem(PLAYER* player, EItemType item_type) {
	if (item_type == KEY_Item)
	{
		player->getKey = get_item(item_type);
	}
	else if (item_type == BULLET_Item)
	{
		if (player->gun.bullets + get_item(item_type) > MAX_BULLET) {
			player->gun.bullets = MAX_BULLET;
		}
		player->gun.bullets += get_item(item_type);
	}
	else if (item_type == BATTERY_Item)
	{
		if (player->battery + get_item(item_type) > MAX_BATTERY) {
			player->battery = MAX_BATTERY;
		}
		player->battery += MAX_BATTERY;
	}
}

void printPlayer(PLAYER* player) {
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player->position.x, player->position.y, player->radius);
}

