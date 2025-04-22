#include "enemy.h"
#include "gameManager.h"
#include "camera.h"
#include "footprint.h"
#include "utility.h"

extern GAME_MANAGER game_Manager;

CP_Vector initCamera(MAB* mab, CP_Vector mab_size)
{

	// 플레이어의 시작 위치가 중심이 되도록 모든 오브젝트의 위치를 초기화
	CP_Vector center_xy = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	CP_Vector initVector = CP_Vector_Subtract(center_xy, (&game_Manager)->player.position);

	mab->minX = center_xy.x - mab_size.x / 2;
	mab->maxX = center_xy.x + mab_size.x / 2;
    mab->minY = center_xy.y - mab_size.y / 2;
    mab->maxY = center_xy.y + mab_size.y / 2;
	mab->cameraPos = (&game_Manager)->player.position;  

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

	for (int i = 0; i < game_Manager.itemCount; i++) {
		game_Manager.item_Boxes[i].position = CP_Vector_Add(game_Manager.item_Boxes[i].position, initVector);
	}

	for (int i = 0; i < game_Manager.obstacleCount; i++) {
		game_Manager.obstacles[i].position = CP_Vector_Add(game_Manager.obstacles[i].position, initVector);
	}

	game_Manager.exit_Place.position = CP_Vector_Add(game_Manager.exit_Place.position, initVector);

	return initVector;

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

	
	

game_Manager.map_Bounds.cameraPos.x = clamp(game_Manager.map_Bounds.cameraPos.x - movingVector.x, game_Manager.map_Bounds.minX, game_Manager.map_Bounds.maxX);
	game_Manager.map_Bounds.cameraPos.y = clamp(game_Manager.map_Bounds.cameraPos.y - movingVector.y, game_Manager.map_Bounds.minY, game_Manager.map_Bounds.maxY);
	

	//float centerX = (float)CP_System_GetWindowWidth() / 2;
	//float centerY = (float)CP_System_GetWindowHeight() / 2;

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

	for (int i = 0; i < game_Manager.itemCount; i++) {
		game_Manager.item_Boxes[i].position = CP_Vector_Add(game_Manager.item_Boxes[i].position, movingVector);
	}

	for (int i = 0; i < game_Manager.obstacleCount; i++) {
		game_Manager.obstacles[i].position = CP_Vector_Add(game_Manager.obstacles[i].position, movingVector);
	}

	game_Manager.exit_Place.position = CP_Vector_Add(game_Manager.exit_Place.position, movingVector);

	

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

	if (dx * dx + dy * dy < 300 * 300)
		return 0;

	// 카메라가 이동하려는 방향이 없다면 굳이 갱신 안함
	if (CP_Vector_DotProduct(CP_Vector_Set(dx, dy), updateVector) <= 0)
		return 0;

	// 경계 충돌 검사
	float halfW = (float)CP_System_GetWindowWidth() / 2;
	float halfH = (float)CP_System_GetWindowHeight() / 2;
	float camX = game_Manager.map_Bounds.cameraPos.x;
	float camY = game_Manager.map_Bounds.cameraPos.y;

	if ((camX - halfW <= game_Manager.map_Bounds.minX && updateVector.x < 0) ||
		(camX + halfW >= game_Manager.map_Bounds.maxX && updateVector.x > 0) ||
		(camY - halfH <= game_Manager.map_Bounds.minY && updateVector.y < 0) ||
		(camY + halfH >= game_Manager.map_Bounds.maxY && updateVector.y > 0))
	{
		return 0;
	}

	return 1;
}


void printVisionblocker(CP_Image* visionblockerOff, CP_Image* visionblockerOn, int checkLampOn)
{

	if (checkLampOn == 0) // to do 랜턴 추가하고 수정
	{
		//CP_Image_Draw(*visionblockerOn , (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, (float)CP_System_GetWindowWidth() * 2, (float)CP_System_GetWindowHeight() * 2, 255);
	}
	else
	{
		//CP_Image_Draw(*visionblockerOff, (&game_Manager)->player.position.x, (&game_Manager)->player.position.y, (float)CP_System_GetWindowWidth() * 2, (float)CP_System_GetWindowHeight() * 2, 255);
	}
}
