

#include <stdlib.h>
#include "utility.h"
#include "gameManager.h"
#include "camera.h"

// GLOBAL
GAME_MANAGER game_Manager;

//to do fix -> to .
void init_Game_Manager(void )
{

	CP_Vector startPositionPlayer = CP_Vector_Set(800, 400);
	init_Player(&(game_Manager.player), startPositionPlayer);

	CP_Vector position_Exit_Place = CP_Vector_Set(1200, 0);
	init_Exit_Place(&(game_Manager.exit_Place), position_Exit_Place);

	game_Manager.enemyCount = 3;

	CP_Vector* startPositionEnemies = (CP_Vector*)malloc(sizeof(CP_Vector)* game_Manager.enemyCount);
	startPositionEnemies[0] = CP_Vector_Set(200, 200);
	startPositionEnemies[1] = CP_Vector_Set(1600, 200);
	startPositionEnemies[2] = CP_Vector_Set(600 , 200);


	// TO DO add comments
	CP_Vector* patrol1 = (CP_Vector*)malloc(2*sizeof(CP_Vector));
	patrol1[0] = CP_Vector_Set(200, 200);
	patrol1[1] = CP_Vector_Set(200, 600);

	CP_Vector* patrol2 = (CP_Vector*)malloc(2 * sizeof(CP_Vector));
	patrol2[0] = CP_Vector_Set(1600, 200);
	patrol2[1] = CP_Vector_Set(400, 200);

	CP_Vector* patrol3 = (CP_Vector*)malloc(4 * sizeof(CP_Vector));
	patrol3[0] = CP_Vector_Set(600, 200);
	patrol3[1] = CP_Vector_Set(200, 400);
	patrol3[2] = CP_Vector_Set(600, 600);
	patrol3[3] = CP_Vector_Set(1000, 400);


	game_Manager.enemies = (ENEMY*)malloc(game_Manager.enemyCount * sizeof(ENEMY));
	init_Enemy_Patrol(game_Manager.enemies, startPositionEnemies[0], patrol1, 2);
	init_Enemy_Patrol(game_Manager.enemies + 1, startPositionEnemies[1], patrol2, 2);
	init_Enemy_Patrol(game_Manager.enemies + 2, startPositionEnemies[2], patrol3, 4);

	//for (int i = 0; i < gameManager->enemyCount; i++) {
	//	init_Enemy((gameManager->enemies + i), startPositionEnemies[i]);
	//}

	game_Manager.itemCount = 3;
	game_Manager.item_Boxes = (ITEM_BOX*)malloc(game_Manager.itemCount * sizeof(ITEM_BOX));
	CP_Vector itemPosition = CP_Vector_Set(1200, 400);
	init_itemBox(game_Manager.item_Boxes, KEY_Item, itemPosition);
	itemPosition = CP_Vector_Set(200, 100);
	init_itemBox(game_Manager.item_Boxes + 1, BULLET_Item, itemPosition);
	itemPosition = CP_Vector_Set(900, 700);
	init_itemBox(game_Manager.item_Boxes + 2, BATTERY_Item, itemPosition);


	game_Manager.obstacleCount = 1;
	game_Manager.obstacles = (OBSTACLE*)malloc(sizeof(OBSTACLE) * game_Manager.obstacleCount);
	CP_Vector position_Wall = CP_Vector_Set(500, 500);
	init_Obstacle(game_Manager.obstacles, position_Wall, WALL);


	initCamera();
}

// Update Game Objects
void update_Game_Manager(void) {

	check_Player_Win();

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	// get WASD Vector
	CP_Vector inputVector = get_InputVector();
	
	
	// Update plyer's position when input WASD
	CP_Vector inputVectorNoraml = CP_Vector_Normalize(inputVector);

	for (int i = 0; i < game_Manager.enemyCount; i++) {
		update_Enemy(game_Manager.enemies + i, dt);
	}

	//updateEnemy(game_Manager.enemies + 2, dt);

	
	if (checkCameraTrigger(&(game_Manager.player), inputVectorNoraml))
	{
		updateCamera(inputVectorNoraml, dt);
	}
	else 	{
		update_Player(&(game_Manager.player), inputVectorNoraml, dt);
	}

	// Block Movement of Player when collision
	for (int i = 0; i < game_Manager.enemyCount; i++) {
		if (check_Collision_Player_Enemy(&(game_Manager.player), game_Manager.enemies + i)) {
			get_Player_Hit(&(game_Manager.player), game_Manager.enemies[i].attackPoint);
			rollback_Player_Position(&(game_Manager.player), inputVectorNoraml, dt*4);
		}
	}

	for (int i = 0; i < game_Manager.itemCount; i++) {
		if (!isEmptyBox(game_Manager.item_Boxes + i) && check_Collision_Player_Item(&(game_Manager.player), game_Manager.item_Boxes + i)) {
			collide_itemBox(game_Manager.item_Boxes + i);
			get_Item(&(game_Manager.player), get_Item_Type(game_Manager.item_Boxes + i));
		}
	}

	if (check_Collision_Player_Obstacles(&(game_Manager.player), game_Manager.obstacles, game_Manager.obstacleCount) == 1) {
		rollback_Player_Position(&(game_Manager.player), inputVectorNoraml, dt);
	}

	print_GameObjects(&game_Manager);

}


int check_Collision_Player_Enemy(PLAYER* player, ENEMY* enemy)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, enemy->position, enemy->radius);
}

int check_Collision_Player_Item(PLAYER* player, ITEM_BOX* item_box)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, item_box->position, item_box->radius);
}

int check_Collision_Player_Obstacles(PLAYER* player, OBSTACLE* obstacles, int count_Obstacles)
{
	for (int i = 0; i < count_Obstacles; i++) {
		if (checkCollision_Circle_to_Circle(player->position, player->radius, obstacles[i].position, obstacles[i].radius)) {
			return 1;
		}
	}
	return 0;
}

int check_Collision_Player_Enter_Exit_Place(PLAYER* player, EXIT_PLACE* exit_Place)
{
	if (player->getKey == 1) {
		return checkCollision_Circle_to_Circle(player->position, player->radius, exit_Place->position, exit_Place->radius);
	}
	else {
		return 0;
	}
	
}

void print_GameObjects(GAME_MANAGER* gameManager)
{
	print_Exit_Place(&(gameManager->exit_Place));
	
	print_Obstacles(gameManager->obstacles, gameManager->obstacleCount);

	for (int i = 0; i < gameManager->enemyCount; i++) {
		print_Enemy(gameManager->enemies + i);
	}

	for (int i = 0; i < gameManager->itemCount; i++) {
		print_itemBox(&(gameManager->item_Boxes[i]));
	}

	print_Player(&(gameManager->player));

}


// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void exit_Game_Manager(void)
{
	/*for (int i = 0; i < game_Manager.enemyCount; i++) {

		free(game_Manager.enemies[i].destinations);
	}*/
	free(game_Manager.enemies);
	free(game_Manager.item_Boxes);
	free(game_Manager.obstacles);
	// shut down the gamestate and cleanup any dynamic memory
}



void check_Player_Win(void)
{
	if (check_Collision_Player_Enter_Exit_Place(&(game_Manager.player), &(game_Manager.exit_Place))) {
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}
	
}