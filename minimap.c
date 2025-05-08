#include "gameManager.h"
#include "utility.h"
#include "minimap.h"
#include "resultScreen.h"
#include <stdlib.h>

float mapWidth;
float mapHeight;

float vision_Line_Width;
float vision_Line_Height;

float vision_Line_Expanded_Width;
float vision_Line_Expanded_Height;
   
CP_Vector centerPosition;

CP_Image exit_Icon_Image_File;
CP_Image obstacle_Icon_Image_File;
CP_Image chest_Icon_Image_File;
CP_Image player_Icon_Image_File;
CP_Image minimap_Frame_Icon_Image_File;
CP_Image minimap_Background_Image_File;
CP_Image minimap_Black_Image_File;
CP_Image vision_line_icon_Image_File;

void init_Minimap(MINIMAP* minimap, CP_Vector map_size, CP_Vector initVector)
// 플레이어 초기 좌표 오류 수정해야함
{
	mapWidth = map_size.x;
	mapHeight = map_size.y;

	minimap->minimapState = MINIMAP_ON;

	minimap->normal.minimapUiSize = 300;

	if (mapWidth > mapHeight)
	{
		minimap->normal.minimapWidth = minimap->normal.minimapUiSize;
		minimap->normal.minimapHeight = minimap->normal.minimapWidth * mapHeight / mapWidth;
	}
	else if (mapHeight > mapWidth)
	{
		minimap->normal.minimapHeight = minimap->normal.minimapUiSize;
		minimap->normal.minimapWidth = minimap->normal.minimapHeight * mapWidth / mapHeight;
	}
	else if (mapHeight == mapWidth)
	{
		minimap->normal.minimapWidth = minimap->normal.minimapUiSize;
		minimap->normal.minimapHeight = minimap->normal.minimapUiSize;
	}

	centerPosition = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	minimap->normal.minimapPosition = CP_Vector_Set((float)CP_System_GetWindowWidth() - 30 - minimap->normal.minimapUiSize / 2, 30 + minimap->normal.minimapUiSize / 2);

	//float widthScale = minimapWidth / mapWidth;
	//float heightScale = minimapHeight / mapHeight;

	minimap->normal.playerIconPosition.x = minimap->normal.minimapPosition.x + (game_Manager.player.position.x - centerPosition.x - initVector.x) * (minimap->normal.minimapWidth / mapWidth);
	minimap->normal.playerIconPosition.y = minimap->normal.minimapPosition.y + (game_Manager.player.position.y - centerPosition.y - initVector.y) * (minimap->normal.minimapHeight / mapHeight);
	 
	minimap->normal.exitIconPosition.x = minimap->normal.minimapPosition.x + (game_Manager.exit_Place.position.x - centerPosition.x - initVector.x) * (minimap->normal.minimapWidth / mapWidth);
	minimap->normal.exitIconPosition.y = minimap->normal.minimapPosition.y + (game_Manager.exit_Place.position.y - centerPosition.y - initVector.y) * (minimap->normal.minimapHeight / mapHeight);

	minimap->normal.itemIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.itemCount);

	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		minimap->normal.itemIconPosition[i].x = minimap->normal.minimapPosition.x + (game_Manager.item_Boxes[i].position.x - centerPosition.x - initVector.x) * (minimap->normal.minimapWidth / mapWidth);
		minimap->normal.itemIconPosition[i].y = minimap->normal.minimapPosition.y + (game_Manager.item_Boxes[i].position.y - centerPosition.y - initVector.y) * (minimap->normal.minimapHeight / mapHeight);
	}

	minimap->normal.obstacleIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.obstacleCount);

	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		minimap->normal.obstacleIconPosition[i].x = minimap->normal.minimapPosition.x + (game_Manager.obstacles[i].position.x - centerPosition.x - initVector.x) * (minimap->normal.minimapWidth / mapWidth);
		minimap->normal.obstacleIconPosition[i].y = minimap->normal.minimapPosition.y + (game_Manager.obstacles[i].position.y - centerPosition.y - initVector.y) * (minimap->normal.minimapHeight / mapHeight);
	}

	minimap->normal.alpha = 255;

	minimap->normal.vision_Line_size = CP_Vector_Set(200 * minimap->normal.minimapWidth / mapWidth, 200 * minimap->normal.minimapHeight / mapHeight);

	vision_Line_Width = minimap->normal.vision_Line_size.x;
	vision_Line_Height = minimap->normal.vision_Line_size.y;

	init_Minimap_Expanded(minimap, initVector);

	exit_Icon_Image_File = CP_Image_Load("Assets/Icon/exit.png");
	obstacle_Icon_Image_File = CP_Image_Load("Assets/Icon/obstacle.png");
	chest_Icon_Image_File = CP_Image_Load("Assets/Icon/chest.png");
	player_Icon_Image_File = CP_Image_Load("Assets/Icon/player.png");
	minimap_Frame_Icon_Image_File = CP_Image_Load("Assets/Icon/minimap_frame.png");
	minimap_Background_Image_File = CP_Image_Load("Assets/Map_data/Background/Dirt_02_Full.png");
	minimap_Black_Image_File = CP_Image_Load("Assets/Image/black.png");
	vision_line_icon_Image_File = CP_Image_Load("Assets/Icon/vision_line_icon.png");
	
}

void init_Minimap_Expanded(MINIMAP* minimap, CP_Vector initVector)
// 플레이어 초기 좌표 오류 수정해야함
{
	minimap->expanded.minimapUiSize = 800;

	if (mapWidth > mapHeight)
	{
		minimap->expanded.minimapWidth = minimap->expanded.minimapUiSize;
		minimap->expanded.minimapHeight = minimap->expanded.minimapWidth * mapHeight / mapWidth;
	}
	else if (mapHeight > mapWidth)
	{
		minimap->expanded.minimapHeight = minimap->expanded.minimapUiSize;
		minimap->expanded.minimapWidth = minimap->expanded.minimapHeight * mapWidth / mapHeight;
	}
	else if (mapHeight == mapWidth)
	{
		minimap->expanded.minimapWidth = minimap->expanded.minimapUiSize;
		minimap->expanded.minimapHeight = minimap->expanded.minimapUiSize;
	}

	minimap->expanded.minimapPosition = centerPosition;

	minimap->expanded.playerIconPosition.x = minimap->expanded.minimapPosition.x + (game_Manager.player.position.x - centerPosition.x - initVector.x) * (minimap->expanded.minimapWidth / mapWidth);
	minimap->expanded.playerIconPosition.y = minimap->expanded.minimapPosition.y + (game_Manager.player.position.y - centerPosition.y - initVector.y) * (minimap->expanded.minimapHeight / mapHeight);

	minimap->expanded.exitIconPosition.x = minimap->expanded.minimapPosition.x + (game_Manager.exit_Place.position.x - centerPosition.x - initVector.x) * (minimap->expanded.minimapWidth / mapWidth);
	minimap->expanded.exitIconPosition.y = minimap->expanded.minimapPosition.y + (game_Manager.exit_Place.position.y - centerPosition.y - initVector.y) * (minimap->expanded.minimapHeight / mapHeight);

	minimap->expanded.itemIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.itemCount);

	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		minimap->expanded.itemIconPosition[i].x = minimap->expanded.minimapPosition.x + (game_Manager.item_Boxes[i].position.x - centerPosition.x - initVector.x) * (minimap->expanded.minimapWidth / mapWidth);
		minimap->expanded.itemIconPosition[i].y = minimap->expanded.minimapPosition.y + (game_Manager.item_Boxes[i].position.y - centerPosition.y - initVector.y) * (minimap->expanded.minimapHeight / mapHeight);
	}

	minimap->expanded.obstacleIconPosition = (CP_Vector*)malloc(sizeof(CP_Vector) * game_Manager.obstacleCount);

	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		minimap->expanded.obstacleIconPosition[i].x = minimap->expanded.minimapPosition.x + (game_Manager.obstacles[i].position.x - centerPosition.x - initVector.x) * (minimap->expanded.minimapWidth / mapWidth);
		minimap->expanded.obstacleIconPosition[i].y = minimap->expanded.minimapPosition.y + (game_Manager.obstacles[i].position.y - centerPosition.y - initVector.y) * (minimap->expanded.minimapHeight / mapHeight);
	}

	minimap->expanded.vision_Line_size = CP_Vector_Set(200 * minimap->expanded.minimapWidth / mapWidth, 200 * minimap->expanded.minimapHeight / mapHeight);

	vision_Line_Expanded_Width = minimap->expanded.vision_Line_size.x;
	vision_Line_Expanded_Height = minimap->expanded.vision_Line_size.y;

	minimap->expanded.alpha = 0; // to do 추후 수정

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
	CP_Vector dPoistion_normal = CP_Vector_Set(dPoistion.x * (minimap->normal.minimapWidth / mapWidth), dPoistion.y * (minimap->normal.minimapHeight / mapHeight));
	CP_Vector dPoistion_expanded = CP_Vector_Set(dPoistion.x * (minimap->expanded.minimapWidth / mapWidth), dPoistion.y * (minimap->expanded.minimapHeight / mapHeight));

	minimap->normal.playerIconPosition.x = clamp(minimap->normal.playerIconPosition.x + dPoistion_normal.x, minimap->normal.minimapPosition.x - minimap->normal.minimapWidth / 2, minimap->normal.minimapPosition.x + minimap->normal.minimapWidth / 2);
	minimap->normal.playerIconPosition.y = clamp(minimap->normal.playerIconPosition.y + dPoistion_normal.y, minimap->normal.minimapPosition.y - minimap->normal.minimapHeight / 2, minimap->normal.minimapPosition.y + minimap->normal.minimapHeight / 2);
	
	minimap->expanded.playerIconPosition.x = clamp(minimap->expanded.playerIconPosition.x + dPoistion_expanded.x, minimap->expanded.minimapPosition.x - minimap->expanded.minimapWidth / 2, minimap->expanded.minimapPosition.x + minimap->expanded.minimapWidth / 2);
	minimap->expanded.playerIconPosition.y = clamp(minimap->expanded.playerIconPosition.y + dPoistion_expanded.y, minimap->expanded.minimapPosition.y - minimap->expanded.minimapHeight / 2, minimap->expanded.minimapPosition.y + minimap->expanded.minimapHeight / 2);

	update_Vision_Line(minimap, dt);
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

void change_Minimap_Alpha(MINIMAP* minimap, RESULT_SCREEN* result_screen, float dt)
{ 
	if (result_screen->isScreenOn == RESULT_SCREEN_ON)
	{
		minimap->normal.alpha = (int)clamp((float)minimap->normal.alpha - 255 * (int)(dt * 1000) / 1000, 0, 255);
		minimap->expanded.alpha = (int)clamp((float)minimap->expanded.alpha - 255 * (int)(dt * 1000) / 1000, 0, 255);
	}
	else
	{
		if (minimap->minimapState == MINIMAP_ON)
		{
			minimap->normal.alpha = 255;
			minimap->expanded.alpha = 0;
		}
		else if (minimap->minimapState == MINIMAP_OFF)
		{
			minimap->normal.alpha = 0;
			minimap->expanded.alpha = 0;
		}
		else if (minimap->minimapState == MINIMAP_EXPANDED)
		{
			minimap->normal.alpha = 0;
			minimap->expanded.alpha = 255;
		}
	}
}

void change_Minimap_State(MINIMAP* minimap)
{
	if (CP_Input_KeyTriggered(KEY_TAB)) {
		if (minimap->minimapState == MINIMAP_OFF)
		{
			minimap->minimapState = 0;
		}
		else
		{
			minimap->minimapState += 1;
		}
	}
}

void print_Minimap(MINIMAP* minimap)
{

	CP_Image_Draw(minimap_Frame_Icon_Image_File, minimap->normal.minimapPosition.x, minimap->normal.minimapPosition.y, minimap->normal.minimapUiSize + 10, minimap->normal.minimapUiSize + 10, minimap->normal.alpha);
	CP_Image_Draw(minimap_Frame_Icon_Image_File, minimap->expanded.minimapPosition.x, minimap->expanded.minimapPosition.y, minimap->expanded.minimapUiSize + 10, minimap->expanded.minimapUiSize + 10, minimap->expanded.alpha);

	CP_Image_Draw(minimap_Background_Image_File, minimap->normal.minimapPosition.x, minimap->normal.minimapPosition.y, minimap->normal.minimapUiSize, minimap->normal.minimapUiSize, minimap->normal.alpha);
	CP_Image_Draw(minimap_Background_Image_File, minimap->expanded.minimapPosition.x, minimap->expanded.minimapPosition.y, minimap->expanded.minimapUiSize, minimap->expanded.minimapUiSize, minimap->expanded.alpha);



	CP_Image_Draw(exit_Icon_Image_File, minimap->normal.exitIconPosition.x, minimap->normal.exitIconPosition.y, 18, 18, minimap->normal.alpha);
	CP_Image_Draw(exit_Icon_Image_File, minimap->expanded.exitIconPosition.x, minimap->expanded.exitIconPosition.y, 48, 48, minimap->expanded.alpha);

	for (int i = 0; i < game_Manager.itemCount; i++)
	{
		
		if (game_Manager.item_Boxes[i].isCollided == 0) {

			CP_Image_Draw(chest_Icon_Image_File, minimap->normal.itemIconPosition[i].x, minimap->normal.itemIconPosition[i].y, 9, 9, minimap->normal.alpha);
			CP_Image_Draw(chest_Icon_Image_File, minimap->expanded.itemIconPosition[i].x, minimap->expanded.itemIconPosition[i].y, 24, 24, minimap->expanded.alpha);

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

	CP_Settings_NoStroke();

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, minimap->normal.alpha));

	if (minimap->normal.minimapWidth > minimap->normal.minimapHeight)
	{
		CP_Graphics_DrawRect(minimap->normal.minimapPosition.x, minimap->normal.minimapPosition.y - minimap->normal.minimapHeight / 2 - (minimap->normal.minimapUiSize - minimap->normal.minimapHeight) / 4, minimap->normal.minimapWidth, (minimap->normal.minimapUiSize - minimap->normal.minimapHeight) / 2);
		CP_Graphics_DrawRect(minimap->normal.minimapPosition.x, minimap->normal.minimapPosition.y + minimap->normal.minimapHeight / 2 + (minimap->normal.minimapUiSize - minimap->normal.minimapHeight) / 4, minimap->normal.minimapWidth, (minimap->normal.minimapUiSize - minimap->normal.minimapHeight) / 2);
	}
	else if (minimap->normal.minimapWidth < minimap->normal.minimapHeight)
	{
		CP_Graphics_DrawRect(minimap->normal.minimapPosition.x - minimap->normal.minimapWidth / 2 - (minimap->normal.minimapUiSize - minimap->normal.minimapWidth) / 4, minimap->normal.minimapPosition.y, (minimap->normal.minimapUiSize - minimap->normal.minimapWidth) / 2, minimap->normal.minimapHeight);
		CP_Graphics_DrawRect(minimap->normal.minimapPosition.x + minimap->normal.minimapWidth / 2 + (minimap->normal.minimapUiSize - minimap->normal.minimapWidth) / 4, minimap->normal.minimapPosition.y, (minimap->normal.minimapUiSize - minimap->normal.minimapWidth) / 2, minimap->normal.minimapHeight);
	}

	
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, minimap->expanded.alpha));

	if (minimap->expanded.minimapWidth > minimap->expanded.minimapHeight)
	{
		CP_Graphics_DrawRect(minimap->expanded.minimapPosition.x, minimap->expanded.minimapPosition.y - minimap->expanded.minimapHeight / 2 - (minimap->expanded.minimapUiSize - minimap->expanded.minimapHeight) / 4, minimap->expanded.minimapWidth, (minimap->expanded.minimapUiSize - minimap->expanded.minimapHeight) / 2);
		CP_Graphics_DrawRect(minimap->expanded.minimapPosition.x, minimap->expanded.minimapPosition.y + minimap->expanded.minimapHeight / 2 + (minimap->expanded.minimapUiSize - minimap->expanded.minimapHeight) / 4, minimap->expanded.minimapWidth, (minimap->expanded.minimapUiSize - minimap->expanded.minimapHeight) / 2);
	}
	else if (minimap->expanded.minimapWidth < minimap->expanded.minimapHeight)
	{
		CP_Graphics_DrawRect(minimap->expanded.minimapPosition.x - minimap->expanded.minimapWidth / 2 - (minimap->expanded.minimapUiSize - minimap->expanded.minimapWidth) / 4, minimap->expanded.minimapPosition.y, (minimap->expanded.minimapUiSize - minimap->expanded.minimapWidth) / 2, minimap->expanded.minimapHeight);
		CP_Graphics_DrawRect(minimap->expanded.minimapPosition.x + minimap->expanded.minimapWidth / 2 + (minimap->expanded.minimapUiSize - minimap->expanded.minimapWidth) / 4, minimap->expanded.minimapPosition.y, (minimap->expanded.minimapUiSize - minimap->expanded.minimapWidth) / 2, minimap->expanded.minimapHeight);
	}

	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

	CP_Image_Draw(player_Icon_Image_File, minimap->normal.playerIconPosition.x, minimap->normal.playerIconPosition.y, 9, 9, minimap->normal.alpha);
	CP_Image_Draw(player_Icon_Image_File, minimap->expanded.playerIconPosition.x, minimap->expanded.playerIconPosition.y, 24, 24, minimap->expanded.alpha);

	for (int i = 0; i < game_Manager.obstacleCount; i++)
	{
		if (game_Manager.obstacles[i].isCollided == 1)
		{
			CP_Image_Draw(obstacle_Icon_Image_File, minimap->normal.obstacleIconPosition[i].x, minimap->normal.obstacleIconPosition[i].y, 18, 18, minimap->normal.alpha);
			CP_Image_Draw(obstacle_Icon_Image_File, minimap->expanded.obstacleIconPosition[i].x, minimap->expanded.obstacleIconPosition[i].y, 48, 48, minimap->expanded.alpha);
		}
	}

	CP_Image_Draw(vision_line_icon_Image_File, minimap->normal.playerIconPosition.x, minimap->normal.playerIconPosition.y, minimap->normal.vision_Line_size.x, minimap->normal.vision_Line_size.y, minimap->normal.alpha);
	CP_Image_Draw(vision_line_icon_Image_File, minimap->expanded.playerIconPosition.x, minimap->expanded.playerIconPosition.y, minimap->expanded.vision_Line_size.x, minimap->expanded.vision_Line_size.y, minimap->expanded.alpha);


}

void update_Vision_Line(MINIMAP* minimap, float dt)
{

	if (game_Manager.light.lightState == off)
	{
		minimap->normal.vision_Line_size.x = clamp(minimap->normal.vision_Line_size.x - vision_Line_Width * (dt * 10), vision_Line_Width, (vision_Line_Width * 2));
		minimap->normal.vision_Line_size.y = clamp(minimap->normal.vision_Line_size.y - vision_Line_Height * (dt * 10), vision_Line_Height, (vision_Line_Height * 2));

		minimap->expanded.vision_Line_size.x = clamp(minimap->expanded.vision_Line_size.x - vision_Line_Expanded_Width * (dt * 10), vision_Line_Expanded_Width, (vision_Line_Expanded_Width * 2));
		minimap->expanded.vision_Line_size.y = clamp(minimap->expanded.vision_Line_size.y - vision_Line_Expanded_Height * (dt * 10), vision_Line_Expanded_Height, (vision_Line_Expanded_Height * 2));
	}
	else if (game_Manager.light.lightState == on)
	{
		minimap->normal.vision_Line_size.x = clamp(minimap->normal.vision_Line_size.x + vision_Line_Width * (dt * 10), vision_Line_Width, (vision_Line_Width * 2));
		minimap->normal.vision_Line_size.y = clamp(minimap->normal.vision_Line_size.y + vision_Line_Height * (dt * 10), vision_Line_Height, (vision_Line_Height * 2));

		minimap->expanded.vision_Line_size.x = clamp(minimap->expanded.vision_Line_size.x + vision_Line_Expanded_Width * (dt * 10), vision_Line_Expanded_Width, (vision_Line_Expanded_Width * 2));
		minimap->expanded.vision_Line_size.y = clamp(minimap->expanded.vision_Line_size.y + vision_Line_Expanded_Height * (dt * 10), vision_Line_Expanded_Height, (vision_Line_Expanded_Height * 2));
	}
}

void rollback_Player_Icon_Position(MINIMAP* minimap, CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(CP_Vector_Scale(updateVector, dt * (game_Manager.player.speed)), minimap->normal.minimapWidth / mapWidth);
	CP_Vector dPoistion_ex = CP_Vector_Scale(CP_Vector_Scale(updateVector, dt * (game_Manager.player.speed)), minimap->expanded.minimapWidth / mapWidth);

	minimap->normal.playerIconPosition = CP_Vector_Subtract(minimap->normal.playerIconPosition, dPoistion);
	minimap->expanded.playerIconPosition = CP_Vector_Subtract(minimap->expanded.playerIconPosition, dPoistion_ex);
} 
/*
각 프린트된 오브젝트의 좌표 및 카운트를 사용해 미니맵 이미지를 그려냄.
장애물의 경우 state가 1일 때만 이미지를 출력시킴
*/
