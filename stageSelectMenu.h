#include "mainmenu.h"
#pragma once

void Init_Stage_Select_Menu(void);

void Update_Stage_Select_Menu(void);

void Exit_Stage_Select_Menu(void);

void Init_Button(IMAGE* Button, CP_Vector startPosition, float width, float height);

void Print_Button(IMAGE* stageSelect_Button, int stageNumber);

void Print_Exit_Button(IMAGE* exit_Button);