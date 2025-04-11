#pragma once

void mainmenu_init(void);

void mainmenu_update(void);

void mainmenu_exit(void);

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
// 사각형 범위 클릭 감지 함수

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
// 원형 범위 클릭 감지 함수

void MoveCoords(float *x, float *y);
/* 좌표 이동 함수 (0,0)이 중심이 되도록 
x = [-(float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowWidth() / 2]
-800 ~ 800
y = [-(float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowHeight() / 2]
-450 ~ 450
*/