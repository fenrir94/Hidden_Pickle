
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "gameManager.h"
#include "camera.h"
#include "player.h"
#include "gun.h"
#include "light.h"
#include "minimap.h"
#include "cJSON.h"
#include "stageSelectMenu.h"
#include "resultScreen.h"
#include "bloodpool.h"

// GLOBAL
GAME_MANAGER game_Manager;

extern CP_Sound gunshot_SFX_File;
extern CP_Sound player_Hit_SFX_File;
extern CP_Sound chest_Open_SFX_File;
extern CP_Sound result_Click_SFX_File;

extern CP_Image menu_Ui_Image_File;
extern CP_Image round_Button_Image_File;
extern CP_Image round_Button_Pressed_Image_File;
extern CP_Image next_Icon_Image_File;
extern CP_Image repeat_Icon_Image_File;
extern CP_Image select_Icon_Image_File;
extern CP_Image screen_Black_Image_File;
extern CP_Image exit_Icon_Image_File;
extern CP_Image obstacle_Icon_Image_File;
extern CP_Image chest_Icon_Image_File;
extern CP_Image player_Icon_Image_File;
extern CP_Image minimap_Frame_Icon_Image_File;
extern CP_Image minimap_Background_Image_File;
extern CP_Image minimap_Black_Image_File;
extern CP_Image vision_line_icon_Image_File;

extern int stage_Number_State;

// GLOBAL
GAME_MANAGER game_Manager;

CP_Vector* startPositionEnemies;
int* patrolPointEnemies;
CP_Vector* destinationsEnemies;
char* buffer;

extern int stage_Number;

//to do fix -> to .
void init_Game_Manager(void)
{
	char map_Name_Buffer[100];

	sprintf_s(map_Name_Buffer, sizeof(map_Name_Buffer), "./Assets/Map_data/map_data_Test%d.JSON", stage_Number);

	//파일 읽어오기
	FILE* file = fopen(map_Name_Buffer, "rb");
	if (!file) {
		printf("파일 열기 실패\n");
		CP_Engine_Terminate();
	}
	fseek(file, 0, SEEK_END); 
	long filesize = ftell(file); // 파일의 끝으로 이동 후 바이트 크기 받아오기 -> str 크기를 알기 위해
	rewind(file);
	//파일 string에 집어넣기
	
	buffer = (char*)malloc(filesize+1);
	fread(buffer, sizeof(char), filesize, file);
	buffer[filesize] = '\0';

	fclose(file);	

	//json 객체로 파싱

	cJSON *root = cJSON_Parse(buffer);
    if (!root) {
        printf("파싱 실패\n");
        free(buffer);
		CP_Engine_Terminate();
    }

	//json 파일에서 불러온 값 아래 함수에 삽입


    //플레이어
	cJSON* player_cJSON = cJSON_GetObjectItem(root, "player");
	cJSON* player_start_cJSON = cJSON_GetObjectItem(player_cJSON, "startPosition");
	game_Manager.player.position = CP_Vector_Set((float)cJSON_GetObjectItem(player_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(player_start_cJSON, "y")->valuedouble);
	init_Player(&(game_Manager.player), game_Manager.player.position);

	//탈출구
	cJSON* exitPlace_cJSON = cJSON_GetObjectItem(root, "exit_place");
	CP_Vector position_Exit_Place = CP_Vector_Set((float)cJSON_GetObjectItem(exitPlace_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(exitPlace_cJSON, "y")->valuedouble);
	init_Exit_Place(&(game_Manager.exit_Place), position_Exit_Place);

	//아이템 박스
	cJSON* itemBoxes_cJSON = cJSON_GetObjectItem(root, "item_boxes");
	game_Manager.itemCount = cJSON_GetArraySize(itemBoxes_cJSON);
	game_Manager.item_Boxes = (ITEM_BOX*)malloc(game_Manager.itemCount * sizeof(ITEM_BOX));

	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		cJSON* itemBox_cJSON = cJSON_GetArrayItem(itemBoxes_cJSON, i);
		cJSON* itemBox_start_cJSON = cJSON_GetObjectItem(itemBox_cJSON, "startPosition");

		CP_Vector itemPosition = CP_Vector_Set((float)cJSON_GetObjectItem(itemBox_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(itemBox_start_cJSON, "y")->valuedouble);
		int itemInBox = cJSON_GetObjectItem(itemBox_cJSON, "item")->valueint;

		init_itemBox(game_Manager.item_Boxes + i, itemInBox, itemPosition);
	}

	//장애물

	cJSON* obstacles_cJSON = cJSON_GetObjectItem(root, "obstacles");
	game_Manager.obstacleCount = cJSON_GetArraySize(obstacles_cJSON);
	game_Manager.obstacles = (OBSTACLE*)malloc(sizeof(OBSTACLE) * game_Manager.obstacleCount);

	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		cJSON* obstacle_cJSON = cJSON_GetArrayItem(obstacles_cJSON, i);
		cJSON* obstacle_start_cJSON = cJSON_GetObjectItem(obstacle_cJSON, "startPosition");
		//cJSON* obstacle_type_cJSON = cJSON_GetObjectItem(obstacle_cJSON, "type");

		CP_Vector position_Wall = CP_Vector_Set((float)cJSON_GetObjectItem(obstacle_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(obstacle_start_cJSON, "y")->valuedouble);
		init_Obstacle(game_Manager.obstacles + i, position_Wall, WALL);
	}
	

	//에너미
	cJSON* enemies_cJSON = cJSON_GetObjectItem(root, "enemies");
	game_Manager.enemyCount = cJSON_GetArraySize(enemies_cJSON); 

	// JSON의 enemies 배열의 크기로 에너미 수 감지 후, 동적할당
	startPositionEnemies = (CP_Vector*)malloc(sizeof(CP_Vector)* game_Manager.enemyCount);
	patrolPointEnemies = (int*)malloc(sizeof(int)* game_Manager.enemyCount);
	game_Manager.enemies = (ENEMY*)malloc(game_Manager.enemyCount * sizeof(ENEMY));

	for (int i = 0; i < game_Manager.enemyCount; i++)
	{
		cJSON* enemy_cJSON	= cJSON_GetArrayItem(enemies_cJSON, i);

		cJSON* enemy_start_cJSON = cJSON_GetObjectItem(enemy_cJSON, "startPosition");
		startPositionEnemies[i] = CP_Vector_Set((float)cJSON_GetObjectItem(enemy_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(enemy_start_cJSON, "y")->valuedouble);

		init_Enemy(game_Manager.enemies + i, startPositionEnemies[i]);

		// enemies 배열 속 각 에너미의 배열 크기로 패트롤포인츠 감지 후, 동적할당
		patrolPointEnemies[i] = cJSON_GetObjectItem(enemy_cJSON, "patrolPoints")->valueint;

		destinationsEnemies = (CP_Vector*)malloc(patrolPointEnemies[i]*sizeof(CP_Vector));
		cJSON* enemy_destination_cJSON = cJSON_GetObjectItem(enemy_cJSON, "destinations");

		for (int j = 0; j < patrolPointEnemies[i]; j++)
		{	
			cJSON* enemy_destination_j_cJSON = cJSON_GetArrayItem(enemy_destination_cJSON, j);
			destinationsEnemies[j] = CP_Vector_Set((float)cJSON_GetObjectItem(enemy_destination_j_cJSON, "x")->valuedouble , (float)cJSON_GetObjectItem(enemy_destination_j_cJSON, "y")->valuedouble);
		}

		init_Enemy_Patrol(game_Manager.enemies + i, startPositionEnemies[i], destinationsEnemies, patrolPointEnemies[i]);
	}


	//맵 사이즈, 미니맵
    cJSON* mapSize_cJSON = cJSON_GetObjectItem(root, "mapsize");
    CP_Vector initVector = init_Camera(&(game_Manager.map_Bounds), CP_Vector_Set((float)cJSON_GetObjectItem(mapSize_cJSON, "w")->valuedouble, (float)cJSON_GetObjectItem(mapSize_cJSON, "h")->valuedouble));
    init_Minimap(&(game_Manager.minimap), CP_Vector_Set((float)cJSON_GetObjectItem(mapSize_cJSON, "w")->valuedouble, (float)cJSON_GetObjectItem(mapSize_cJSON, "h")->valuedouble), initVector);
	
	init_Result_Screen(&(game_Manager.result_Screen));

	init_Light(&(game_Manager.light));

	char* directoryImage = "./Assets/Map_data/Background/Dirt_02.png";
	//char* directoryImage = "./Assets/Map_data/Background/Dirt_02_Full.png";

	init_Background(&(game_Manager.background), directoryImage, (int)cJSON_GetObjectItem(mapSize_cJSON, "w")->valuedouble, (int)cJSON_GetObjectItem(mapSize_cJSON, "h")->valuedouble, game_Manager.map_Bounds.minX + initVector.x, game_Manager.map_Bounds.minY + initVector.y);

	cJSON_Delete(root);  // root를 지우면 내부 모든 것도 같이 해제됨
}

// Update Game Objects
void update_Game_Manager(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 0, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	if (game_Manager.result_Screen.isScreenOn == RESULT_SCREEN_OFF) {
		// get WASD Vector
		CP_Vector inputVector = get_InputVector();

		// get Space Bar = BatteryUse
		use_Battery(&(game_Manager.player));

		// Update plyer's position when input WASD
		CP_Vector inputVectorNoraml = CP_Vector_Normalize(inputVector);



		if (checkCameraTrigger(&(game_Manager.player), inputVectorNoraml))
		{
			update_Camera(&(game_Manager.map_Bounds), inputVectorNoraml, dt);
		}
		else {
			update_Player(&(game_Manager.player), inputVectorNoraml, dt);
		}

		rotate_Player(&(game_Manager.player));

		// TO DO Fix Shoot Animation
		if (shootingBullet_Player(&(game_Manager.player), KEY_J, MOUSE_BUTTON_LEFT)) {
			changeAnimation_BodyPart(&(game_Manager.player.body), SHOOT);
			if (CP_Vector_Length(inputVectorNoraml) > 0) {
				changeAnimation_BodyPart(&(game_Manager.player.feet), MOVE);
			}
			else {
				changeAnimation_BodyPart(&(game_Manager.player.feet), IDLE);
			}
		}
		else {
			if (CP_Vector_Length(inputVectorNoraml) > 0) {
				changeAnimation_BodyPart(&(game_Manager.player.body), MOVE);
				changeAnimation_BodyPart(&(game_Manager.player.feet), MOVE);
			}
			else {
				changeAnimation_BodyPart(&(game_Manager.player.body), IDLE);
				changeAnimation_BodyPart(&(game_Manager.player.feet), IDLE);
			}
		}

		update_BodyPart(&(game_Manager.player.body), dt * 100);
		update_BodyPart(&(game_Manager.player.feet), dt * 100);

		checkAiming_Player(&(game_Manager.player), KEY_K, MOUSE_BUTTON_RIGHT);

		update_Gun(&(game_Manager.player.gun), game_Manager.player.position, game_Manager.player.shooting_Vector, dt);


		turn_On_Light(&(game_Manager.light), game_Manager.player.isLampOn);

		update_Light(&(game_Manager.light), dt);

		update_Minimap(&(game_Manager.minimap), inputVectorNoraml, dt);
		change_Minimap_State(&(game_Manager.minimap));
		change_Minimap_Alpha(&(game_Manager.minimap), &(game_Manager.result_Screen), dt);

		// Check Enemy Detected Player
		for (int i = 0; i < game_Manager.enemyCount; i++) {
			check_DetectPlayer_Enemy(game_Manager.enemies + i, game_Manager.player.position, game_Manager.player.radius);
			update_Enemy(game_Manager.enemies + i, game_Manager.player.position, dt);
		}

		// Block Movement of Player when collision
		for (int i = 0; i < game_Manager.enemyCount; i++) {
			if (check_Collision_Player_Enemy(&(game_Manager.player), game_Manager.enemies + i)) {
				getDamage_Player(&(game_Manager.player), game_Manager.enemies[i].attackPoint);
				rollback_Player_Position(&(game_Manager.player), inputVectorNoraml, dt * 3);
				rollback_Player_Icon_Position(&(game_Manager.minimap), inputVectorNoraml, dt * 3);
			}
		}

			for (int i = 0; i < game_Manager.itemCount; i++) {
			if (!isEmptyBox(game_Manager.item_Boxes + i) && check_Collision_Player_Item(&(game_Manager.player), game_Manager.item_Boxes + i)) {
				collide_itemBox(game_Manager.item_Boxes + i);
				get_Item(&(game_Manager.player), get_Item_Type(game_Manager.item_Boxes + i));
			}
		}


		for (int i = 0; i < game_Manager.obstacleCount; i++) {
			if (check_Is_Obstacle_In_Players_Sight(&(game_Manager.player), game_Manager.obstacles + i)) {
				game_Manager.obstacles[i].isCollided = 1;
			}
		}

		if (check_Collision_Player_Obstacles(&(game_Manager.player), game_Manager.obstacles, game_Manager.obstacleCount) == 1) {
			rollback_Player_Position(&(game_Manager.player), inputVectorNoraml, dt);
			rollback_Player_Icon_Position(&(game_Manager.minimap), inputVectorNoraml, dt);
		}

		for (int i = 0; i < game_Manager.enemyCount; i++) {
			if (check_Collision_Enemy_Obstacles(game_Manager.enemies + i, game_Manager.obstacles, game_Manager.obstacleCount) == 1) {
				rollback_Move_Enemy_Position(game_Manager.enemies + i, game_Manager.enemies[i].vector_Sight, dt * 3);
			}
		}

		check_Collsion_Bullet_Enemy(&(game_Manager.player.gun), game_Manager.enemies, game_Manager.enemyCount);
		check_Collsion_Bullet_Obstacles(&(game_Manager.player.gun), game_Manager.obstacles, game_Manager.obstacleCount);


		if (check_Player_Win()) {
			update_Result_Screen(&(game_Manager.result_Screen), GAME_STATE_WIN);
		}

		if (check_Player_Lose(&(game_Manager.player))) {
			update_Result_Screen(&(game_Manager.result_Screen), GAME_STATE_LOSE);
		}
	}

	
		if (game_Manager.result_Screen.isScreenOn == RESULT_SCREEN_ON) {

			float animationTotalTime = 2;
			static float elapsedTime = 0;

			update_Player(&(game_Manager.player), CP_Vector_Set(0, 0), dt);
			
			if (game_Manager.result_Screen.animationState == ANIMATION_LOSE) {
				elapsedTime += dt;

				printf("Death Animation! %d\n", getAnimationEnded_Bloodpool(&(game_Manager.player.bloodpool)));
				//사망시 애니메이션 재생


				if (elapsedTime > animationTotalTime)
				{
					game_Manager.result_Screen.animationState = ANIMATION_GAME_OVER;
					elapsedTime = 0;
				}

			}


			if (game_Manager.result_Screen.animationState == ANIMATION_GAME_OVER) {
				elapsedTime += dt;
				change_Player_Alpha(&(game_Manager.player), &(game_Manager.result_Screen), dt);
				change_Minimap_Alpha(&(game_Manager.minimap), &(game_Manager.result_Screen), dt);
				game_Manager.light.lightState = end;
				update_Light(&(game_Manager.light), dt);

				if (elapsedTime > animationTotalTime)
				{
					game_Manager.result_Screen.animationState = ANIMATION_NONE;
					elapsedTime = 0;
				}
			}

			if (game_Manager.result_Screen.animationState == ANIMATION_NONE)
			{
				update_Result_Screen_Button(&(game_Manager.result_Screen));

			}
			


		}
		
		print_GameObjects(&game_Manager);
}


int check_Collision_Player_Enemy(PLAYER* player, ENEMY* enemy)
{
	if (enemy->life > 0) {
		return checkCollision_Circle_to_Circle(player->position, player->radius, enemy->position, enemy->radius);
	}
	else {
		return 0;
	}
}

int check_Collision_Player_Item(PLAYER* player, ITEM_BOX* item_box)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, item_box->position, item_box->radius);
}


int check_Is_Obstacle_In_Players_Sight(PLAYER* player, OBSTACLE* obstacles)
{
	if (game_Manager.player.isLampOn == 1) {
		if (CP_Vector_Distance(player->position, obstacles->position) <= 400) {
			return 1;
		}
	}
	else {
		if (CP_Vector_Distance(player->position, obstacles->position) <= 200) {
			return 1;
		}
	}

	return 0;
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

int check_Collision_Enemy_Obstacles(ENEMY* enemy, OBSTACLE* obstacles, int count_Obstacles)
{
	for (int i = 0; i < count_Obstacles; i++) {
		if (check_Collision_Enemy_Object(enemy, obstacles[i].position, obstacles[i].radius)) {
			return 1;
		}
	}
	return 0;
}

void check_Collsion_Bullet_Enemy(GUN* gun, ENEMY* enemy, int count_Enemy)
{
	for (int i = 0; i < MAX_BULLET;i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			for (int j = 0; j < count_Enemy; j++) {
				if (enemy[j].life > 0) {
					if (checkCollision_Circle_to_Circle(gun->position_Bullet[i], gun->radius_Bullet, enemy[j].position, enemy[j].radius)) {
						endBullet(gun, i);
						getDamage_Enemy(&(enemy[j]), gun->attackPoint);
						if (enemy[j].life <= 0) {
							init_Bloodpool(&enemy[j].bloodpool, enemy[j].position, 10);
						}
						
					}
				}
			}
		}
	}
}

void check_Collsion_Bullet_Obstacles(GUN* gun, OBSTACLE* obstacles, int count_Obstacles)
{
	for (int i = 0; i < MAX_BULLET;i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			for (int j = 0; j < count_Obstacles; j++) {
				if (checkCollision_Circle_to_Circle(gun->position_Bullet[i], gun->radius_Bullet, obstacles[j].position, obstacles[j].radius)) {
					endBullet(gun, i);
				}
				
			}
		}
	}
}

void print_GameObjects(GAME_MANAGER* gameManager)
{
	print_Background(&(game_Manager.background));

	print_Exit_Place(&(gameManager->exit_Place));
	
	for (int i = 0; i < gameManager->enemyCount; i++) {
		print_Enemy(gameManager->enemies + i);
	}

	for (int i = 0; i < gameManager->itemCount; i++) {
		print_itemBox(&(gameManager->item_Boxes[i]));
	}

	//printBullet(&(gameManager->player.gun));

	print_Player(&(gameManager->player));

	print_Obstacles(gameManager->obstacles, gameManager->obstacleCount);

	printVisionblocker(&(game_Manager.light));

	print_Minimap(&(game_Manager.minimap)); // 게임 종료시 미니맵 알파 낮춰서 0으로

	print_Result_Screen(&(gameManager->result_Screen));
}


// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void exit_Game_Manager(void)
{
	CP_Image_Free(&menu_Ui_Image_File);
	CP_Image_Free(&round_Button_Image_File);
	CP_Image_Free(&round_Button_Pressed_Image_File);
	CP_Image_Free(&next_Icon_Image_File);
	CP_Image_Free(&repeat_Icon_Image_File);
	CP_Image_Free(&select_Icon_Image_File);
	CP_Image_Free(&screen_Black_Image_File);
	CP_Image_Free(&exit_Icon_Image_File);
	CP_Image_Free(&obstacle_Icon_Image_File);
	CP_Image_Free(&chest_Icon_Image_File);
	CP_Image_Free(&player_Icon_Image_File);
	CP_Image_Free(&minimap_Frame_Icon_Image_File);
	CP_Image_Free(&minimap_Background_Image_File);
	CP_Image_Free(&minimap_Black_Image_File);
	CP_Image_Free(&game_Manager.light.lightImage);
	CP_Image_Free(&vision_line_icon_Image_File);

	CP_Sound_Free(&gunshot_SFX_File);
	CP_Sound_Free(&player_Hit_SFX_File);
	CP_Sound_Free(&chest_Open_SFX_File);
	CP_Sound_Free(&result_Click_SFX_File);
	
	free(buffer);
	free(game_Manager.player.body.animation);
	free(game_Manager.player.feet.animation);
	free(game_Manager.item_Boxes);
	for (int i = 0; i < game_Manager.enemyCount; i++) {
		CP_Image_Free(&game_Manager.enemies[i].footprint.imageFootLeft);
		CP_Image_Free(&game_Manager.enemies[i].footprint.imageFootRight);
	}
	free(game_Manager.enemies);
	free(game_Manager.obstacles)
		;
	free(game_Manager.minimap.normal.itemIconPosition);
	free(game_Manager.minimap.normal.obstacleIconPosition);
	free(game_Manager.minimap.expanded.itemIconPosition);
	free(game_Manager.minimap.expanded.obstacleIconPosition);

	free(startPositionEnemies);
	free(patrolPointEnemies);
	free(destinationsEnemies);


	stage_Number_State = 1;

	// shut down the gamestate and cleanup any dynamic memory
}

// to do 해당 함수들 int 형으로, 조건 만족시 true 리턴 -> 각 조건 만족시 win, lose 값 입력으로 보내서 result_screen에 반영.
int check_Player_Win(void)
{
	if (check_Collision_Player_Enter_Exit_Place(&(game_Manager.player), &(game_Manager.exit_Place))) {
		return 1;
	}
	
	return 0;
}

int check_Player_Lose(PLAYER* player)
{
	if (player->life <= 0) {
		return 1;
	}

	return 0;
}