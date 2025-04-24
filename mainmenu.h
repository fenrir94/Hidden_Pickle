#pragma once

//이미지 구조체
typedef struct Image {
    float x;
    float y;
    float width;
    float height;
    int alpha;
    float timeForAlpha; // 인트로 투명도 조절용
} IMAGE;

void Init_Main_Menu(void);

void Update_Main_Menu(void);

void Exit_Main_Menu(void);

void Update_Main_Menu(void);

void Print_Main_Menu_Intro(void);

void Print_Main_Menu(void);