#pragma once

//�̹��� ����ü
typedef struct Image {
    float x;
    float y;
    float width;
    float height;
    int alpha;
    float timeForAlpha; // ��Ʈ�� ���� ������
} IMAGE;

void Init_Main_Menu(void);

void Update_Main_Menu(void);

void Exit_Main_Menu(void);

void Update_Main_Menu(void);

void Print_Main_Menu_Intro(void);

void Print_Main_Menu(void);