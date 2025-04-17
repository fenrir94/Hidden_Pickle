#include "enemy.h"
#include "gameManager.h"
#include "camera.h"
#include "footprint.h"

#define visionblockerWidth 2400
#define visionblockerHeight 1500

extern GAME_MANAGER game_Manager;

void initCamera()
{

	// 플레이어의 시작 위치가 중심이 되도록 모든 오브젝트의 위치를 초기화
	CP_Vector center_xy = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	CP_Vector initVector = CP_Vector_Subtract(center_xy, (&game_Manager)->player.position);


	(&game_Manager)->player.position = CP_Vector_Add((&game_Manager)->player.position, initVector); // 플레이어 위치 초기화

	for (int i = 0; i < (&game_Manager)->enemyCount; i++) 
	// 에너미 위치 초기화
	{
		(&game_Manager)->enemies[i].position = CP_Vector_Add((&game_Manager)->enemies[i].position, initVector);

		for (int j = 0; j < (&game_Manager)->enemies[i].patrolPoints ; j++)
		{
		(&game_Manager)->enemies[i].destinations[j] = CP_Vector_Add((&game_Manager)->enemies[i].destinations[j], initVector);
		}
	}

	/*
	for (int i = 0; i < (&game_Manager)->....Count; i++) 
	// .... 위치 초기화
	{
		(&game_Manager)->....[i].position = CP_Vector_Add((&game_Manager)->....[i].position, initVector);
	}
	*/

}

void updateCamera(CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (&game_Manager)->player.speed);

	CP_Vector movingVector = CP_Vector_Negate(dPoistion);

	for (int i = 0; i < (&game_Manager)->enemyCount; i++) 
	// 에너미 위치 변경
	{
		(&game_Manager)->enemies[i].position = CP_Vector_Add((&game_Manager)->enemies[i].position, movingVector);

		for (int j = 0; j < (&game_Manager)->enemies[i].patrolPoints ; j++)
		{
			(&game_Manager)->enemies[i].destinations[j] = CP_Vector_Add((&game_Manager)->enemies[i].destinations[j], movingVector);
		}

		int footprintCnt = (&game_Manager)->enemies[i].footprint.front;

		while (footprintCnt != (&game_Manager)->enemies[i].footprint.rear) {

			footprintCnt = (footprintCnt + 1) % COUNT_FOOTPRINT;

			(&game_Manager)->enemies[i].footprint.position[footprintCnt].x = (&game_Manager)->enemies[i].footprint.position[footprintCnt].x + movingVector.x;
			(&game_Manager)->enemies[i].footprint.position[footprintCnt].y = (&game_Manager)->enemies[i].footprint.position[footprintCnt].y + movingVector.y;
		}


	}

	/*
	for (int i = 0; i < (&game_Manager)->....Count; i++) 
	// .... 위치 변경
	{
		(&game_Manager)->enemies[i].position = CP_Vector_Add((&game_Manager)->....[i].position, movingVector);
	}
	*/
}

int checkCameraTrigger(PLAYER* player, CP_Vector updateVector)
// 카메라 동작 여부 감지
{

	float centerX = (float)CP_System_GetWindowWidth() / 2;
	float centerY = (float)CP_System_GetWindowHeight() / 2;
	float dx = player->position.x - centerX;
	float dy = player->position.y - centerY;

	/* 맵 경계에서 2d 카메라 동작 중지 시키는 코드 -> 맵 경계값들을 배열에 저장해서 플레이어나 카메라 이동할때 좌표 변동시키는 방식으로 동작시켜야할듯함.
	if (player->position.x < centerX * 2 - mapWidth / 2 || centerX * 2 < player->position.x || 
		player->position.y < centerY * 2 - mapHeight / 2 || centerY * 2 < player->position.y)
	{
		return 0;
	}
	*/

	if (dx * dx + dy * dy < 300 * 300)
	{
		return 0;
	}
	else
	{
		CP_Vector player_xy = CP_Vector_Set(player->position.x, player->position.y);
		CP_Vector center_xy = CP_Vector_Set(centerX, centerY);
		CP_Vector player_vector = CP_Vector_Subtract(player_xy, center_xy);

		if (CP_Vector_DotProduct(player_vector, updateVector) <= 0)
		{
			return 0;
		}
		else
		{	
			return 1;
		}
	}
}


void printVisionblocker(CP_Image* visionblockerOff, CP_Image* visionblockerOn)
{

	if (CP_Input_KeyDown(KEY_SPACE)) // to do 랜턴 추가하고 수정
	{
		CP_Image_Draw(*visionblockerOn , (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, visionblockerWidth, visionblockerHeight, 255);
	}
	else
	{
		CP_Image_Draw(*visionblockerOff, (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, visionblockerWidth, visionblockerHeight, 255);
	}
}
