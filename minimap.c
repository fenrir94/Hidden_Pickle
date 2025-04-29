#include "gameManager.h"
#include "utility.h"
#include "minimap.h"
#include <stdlib.h>

float mapWidth;
float mapHeight;
float minimapWidth;
float minimapHeight;

   
CP_Vector centerPosition;
CP_Vector minimapPosition;

void init_Minimap(MINIMAP* minimap, CP_Vector map_size, CP_Vector initVector)
// 플레이어 초기 좌표 오류 수정해야함
{
	mapWidth = map_size.x;
	mapHeight = map_size.y;

	centerPosition = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	minimapPosition = CP_Vector_Set((float)CP_System_GetWindowWidth() - 250, 125);
	minimapWidth = 400;
	minimapHeight = 200;
	//float widthScale = minimapWidth / mapWidth;
	//float heightScale = minimapHeight / mapHeight;

	minimap->playerIconPosition.x = minimapPosition.x + (game_Manager.player.position.x - centerPosition.x - initVector.x) * (minimapWidth / mapWidth);
	minimap->playerIconPosition.y = minimapPosition.y + (game_Manager.player.position.y - centerPosition.y - initVector.y) * (minimapHeight / mapHeight);

	minimap->exitIconPosition.x = minimapPosition.x + (game_Manager.exit_Place.position.x - centerPosition.x - initVector.x) * (minimapWidth / mapWidth);
	minimap->exitIconPosition.y = minimapPosition.y + (game_Manager.exit_Place.position.y - centerPosition.y - initVector.y) * (minimapHeight / mapHeight);

	minimap->itemIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.itemCount);
	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		minimap->itemIconPosition[i].x = minimapPosition.x + (game_Manager.item_Boxes[i].position.x - centerPosition.x - initVector.x) * (minimapWidth / mapWidth);
		minimap->itemIconPosition[i].y = minimapPosition.y + (game_Manager.item_Boxes[i].position.y - centerPosition.y - initVector.y) * (minimapHeight / mapHeight);
	}

	minimap->obstacleIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.obstacleCount);
	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		minimap->obstacleIconPosition[i].x = minimapPosition.x + (game_Manager.obstacles[i].position.x - centerPosition.x - initVector.x) * (minimapWidth / mapWidth);
		minimap->obstacleIconPosition[i].y = minimapPosition.y + (game_Manager.obstacles[i].position.y - centerPosition.y - initVector.y) * (minimapHeight / mapHeight);
	}

	minimap->alpha = 255;
	
}
/*
입력으로 맵 사이즈 벡터를 받고, 게임매니저에 존재하는 플레이어 포지션, 아이템 카운트, 장애물 카운트 사용

아이템, 플레이어, 탈출구, 장애물의 초기 위치를 읽어옴. 
-> initcamera 함수가 위치를 이동시키기 때문에 그보다 먼저 불려야함

읽어온 초기 좌표를 미니맵 이미지 위 좌표로 올려야함. 미니맵 사이즈에 맞게 스케일을 줄인 뒤, 좌표를 이동시켜야함.
-> 맵 사이즈는 JSON 파일에서 지정하기 때문에 그때마다 미니맵 이미지 사이즈 및, 초기 좌표에 맞게 스케일을 조정 할 수 있어야함.
-> 우상단에 위치시키도록, 미니맵 사이즈 mw x mh 일때 맵 사이즈 w x h에 비율에 맞춰 스케일 조절이 필요함.
-> dx + dy -> dx * (mw / w) + dy * (mh / h)로 변환.
-> 각 오브젝트의 초기 좌표를 읽어옴. (ox, oy) 라고 가정. 미니맵 좌표 (mx,my)
-> 중심 좌표 (GWW, GWH)를 통해 벡터 (ox - GWW, oy - GWH)를 얻어 (ox- GWW * (mw / w) , oy - GWH * (mh / h))로 스케일링.
-> 오브젝트의 아이콘 좌표는 (mx,my) + (ox- GWW * (mw / w) , oy - GWH * (mh / h))
*/

void update_Minimap(MINIMAP* minimap, CP_Vector updateVector, float dt)
// 충돌 시 움직이지 않아야함.
{
	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (game_Manager.player.speed));
	dPoistion.x = dPoistion.x * (minimapWidth / mapWidth);
	dPoistion.y = dPoistion.y * (minimapHeight / mapHeight);

	minimap->playerIconPosition.x = clamp(minimap->playerIconPosition.x + dPoistion.x, minimapPosition.x - minimapWidth / 2, minimapPosition.x + minimapWidth / 2);
	minimap->playerIconPosition.y = clamp(minimap->playerIconPosition.y + dPoistion.y, minimapPosition.y - minimapHeight / 2, minimapPosition.y + minimapHeight / 2);

}
/*

플레이어가 이동하면 미니맵의 플레이어 아이콘 또한 이동해야함.
-> 기존 무빙벡터 이용해서 이동 시킴. 미니맵 사이즈에 맞게 벡터 사이즈를 줄여야함.
-> dx + dy -> dx * (mw / w) + dy * (mh / h)로 변환.

플레이어 아이콘이 미니맵 바깥으로 나가지 않게 해야함
-> clamp 사용. mx - mw / 2 < x < mx + mw / 2, my - mh / 2 < y < my + mh / 2의 범위를 지키도록 만듬.

플레이어와 일정 거리 이상 가까워진 장애물의 아이콘이 나타나야함. 나타난 후론 미니맵에 계속 표시됨.
장애물과 플레이어의 좌표를 비교해 일정 거리 이상에 한번이라도 들어오면 state 1
-> checkCollision_Circle_to_Circle 함수 사용
*/

void change_Minimap_Alpha(MINIMAP* minimap, float dt)
{
	minimap->alpha -= 255 * (int)(dt * 1000) / 1000;
}

void print_Minimap(MINIMAP* minimap)
{

	CP_Settings_Fill(CP_Color_Create(80, 80, 80, minimap->alpha));
	CP_Graphics_DrawRect(minimapPosition.x, minimapPosition.y, minimapWidth, minimapHeight);

	CP_Settings_Fill(CP_Color_Create(0, 255, 0, minimap->alpha));
	CP_Graphics_DrawCircle(minimap->playerIconPosition.x, minimap->playerIconPosition.y, 5);	

	CP_Settings_Fill(CP_Color_Create(255, 255, 0, minimap->alpha));
	CP_Graphics_DrawCircle(minimap->exitIconPosition.x, minimap->exitIconPosition.y, 10);	

	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		
		if (game_Manager.item_Boxes[i].isCollided == 0) {


			CP_Settings_Fill(CP_Color_Create(255, 255, 0, minimap->alpha));
			CP_Graphics_DrawCircle(minimap->itemIconPosition[i].x, minimap->itemIconPosition[i].y, 5);

			/*
			if (game_Manager.item_Boxes[i].item_type == KEY_Item)
			{
				CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
				CP_Graphics_DrawCircle(minimap->itemIconPosition[i].x, minimap->itemIconPosition[i].y, 5);

			}
			else if (game_Manager.item_Boxes[i].item_type == BULLET_Item)
			{
				CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
				CP_Graphics_DrawCircle(minimap->itemIconPosition[i].x, minimap->itemIconPosition[i].y, 5);

			}
			else if (game_Manager.item_Boxes[i].item_type == BATTERY_Item)
			{
				CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
				CP_Graphics_DrawCircle(minimap->itemIconPosition[i].x, minimap->itemIconPosition[i].y, 5);
			}
			*/
		
		}
		
}

	CP_Settings_Fill(CP_Color_Create(165, 42, 42, minimap->alpha));
	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		if (game_Manager.obstacles[i].isCollided == 1)
		{
			CP_Graphics_DrawCircle(minimap->obstacleIconPosition[i].x, minimap->obstacleIconPosition[i].y, 10);
		}
	}


}

void rollback_Player_Icon_Position(MINIMAP* minimap, CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(CP_Vector_Scale(updateVector, dt * (game_Manager.player.speed)), minimapWidth / mapWidth);

	minimap->playerIconPosition = CP_Vector_Subtract(minimap->playerIconPosition, dPoistion);
} 
/*
각 프린트된 오브젝트의 좌표 및 카운트를 사용해 미니맵 이미지를 그려냄.
장애물의 경우 state가 1일 때만 이미지를 출력시킴
*/