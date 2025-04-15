
#include "player.h"
#include "utility.h"

void init_Player(PLAYER* player, CP_Vector startPosition) {
	player->position.x = startPosition.x;
	player->position.y = startPosition.y;
	player->speed = 200;
	player->life = 3;
	player->radius = 50;
}

void updatePlayer(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Add(player->position, dPoistion);
}


void printPlayer(PLAYER* player) {
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player->position.x, player->position.y, player->radius);
}