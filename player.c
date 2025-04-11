
#include <stdio.h>
#include "cprocessing.h"
#include "player.h"

void init_Player(PLAYER* player, CP_Vector startPosition) {
	player->position.x = startPosition.x;
	player->position.y = startPosition.y;
	//int speed = 5;
	//int life = 3;
	//float radius = 100;
}

//void updatePlayer(PLAYER* player, float dt, CP_KEY key ) {
//	if (CP_Input_KeyDown(KEY_W)) player->position.y -= player->speed * dt;
//	if (CP_Input_KeyDown(KEY_S)) player->position.y += player->speed * dt;
//	if (CP_Input_KeyDown(KEY_A)) player->position.x -= player->speed * dt;
//	if (CP_Input_KeyDown(KEY_D)) player->position.x += player->speed * dt;
//}


void printPlayer(PLAYER* player) {
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player->position.x, player->position.y, 150);
}