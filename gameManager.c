
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "gameManager.h"
#include "camera.h"
#include "player.h"
#include "cJSON.h"

// GLOBAL
GAME_MANAGER game_Manager;

CP_Image visionblockerOff;
CP_Image visionblockerOn;

CP_Vector* startPositionEnemies;
int* patrolPointEnemies;
CP_Vector* destinationsEnemies;

//to do fix -> to .
void init_Game_Manager(void)
{
	//파일 읽어오기
	FILE* file = fopen("./Assets/Map_data/map_data.JSON", "rb");
	if (!file) {
		printf("파일 열기 실패\n");
		CP_Engine_Terminate();
	}
	fseek(file, 0, SEEK_END); 
	long filesize = ftell(file); // 파일의 끝으로 이동 후 바이트 크기 받아오기 -> str 크기를 알기 위해
	rewind(file);
	//파일 string에 집어넣기

	char* buffer = (char*)malloc(filesize+1);
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

	cJSON* player_cJSON = cJSON_GetObjectItem(root, "player");
	cJSON* player_start_cJSON = cJSON_GetObjectItem(player_cJSON, "startPosition");
	game_Manager.player.position = CP_Vector_Set((float)cJSON_GetObjectItem(player_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(player_start_cJSON, "y")->valuedouble);
	init_Player(&(game_Manager.player), game_Manager.player.position);

	cJSON* enemies_cJSON = cJSON_GetObjectItem(root, "enemies");
	game_Manager.enemyCount = cJSON_GetArraySize(enemies_cJSON);

	startPositionEnemies = (CP_Vector*)malloc(sizeof(CP_Vector)* game_Manager.enemyCount);
	patrolPointEnemies = (int*)malloc(sizeof(int)* game_Manager.enemyCount);

	game_Manager.enemies = (ENEMY*)malloc(game_Manager.enemyCount * sizeof(ENEMY));

	for (int i = 0; i < game_Manager.enemyCount; i++)
	{
		cJSON* enemy_cJSON	= cJSON_GetArrayItem(enemies_cJSON, i);

		cJSON* enemy_start_cJSON = cJSON_GetObjectItem(enemy_cJSON, "startPosition");
		startPositionEnemies[i] = CP_Vector_Set((float)cJSON_GetObjectItem(enemy_start_cJSON, "x")->valuedouble, (float)cJSON_GetObjectItem(enemy_start_cJSON, "y")->valuedouble);

		init_Enemy(game_Manager.enemies + i, startPositionEnemies[i]);

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

	visionblockerOff = CP_Image_Load("./Assets/transparent_center_200.png");
	visionblockerOn = CP_Image_Load("./Assets/transparent_center_400.png");

	initCamera();
	cJSON_Delete(root);  // root를 지우면 내부 모든 것도 같이 해제됨
}

// Update Game Objects
void update_Game_Manager(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 0));
	// check input, update simulation, render etc.
	float dt = CP_System_GetDt();

	// TO DO change function name
	CP_Vector uVector = getKeyVector();
	
	
	// Update plyer's position when input WASD
	CP_Vector uVectorNoraml = CP_Vector_Normalize(uVector);

	if (checkCameraTrigger(&(game_Manager.player), uVectorNoraml))
	{
		updateCamera(uVectorNoraml, dt);
	}
	else
	{
		update_Player(&(game_Manager.player), uVectorNoraml, dt);
	}

	for (int i = 0; i < game_Manager.enemyCount; i++) {
		update_Enemy(game_Manager.enemies+i, dt);
	}

	//update_Enemy(game_Manager.enemies + 2, dt);

	print_GameObjects(&game_Manager);

}


void print_GameObjects(GAME_MANAGER* gameManager)
{
	print_Player(&(gameManager->player));

	for (int i = 0; i < gameManager->enemyCount; i++) {
		print_Enemy(gameManager->enemies + i);
	}

	printVisionblocker(&visionblockerOff, &visionblockerOn);
}


// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void exit_Game_Manager(void)
{
	CP_Image_Free(&visionblockerOff);
	CP_Image_Free(&visionblockerOn);


	free(startPositionEnemies);
	free(patrolPointEnemies);
	free(game_Manager.enemies);
	free(destinationsEnemies);
	// shut down the gamestate and cleanup any dynamic memory
}