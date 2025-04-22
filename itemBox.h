#pragma once

/*
* 
* This is a header file about item boxes in a map
* 
* Declare struct of itemBox and functions.
* 
* Item Box contains vector position and enum itemType
* 
* if player co
* 
*/

#include <stdio.h>
#include "cprocessing.h"
#include "utility.h"
#include "stdlib.h"

#define MAX_BULLET 6
#define MAX_BATTERY 100
#define TIME_BULLLET 2

typedef enum item {
	KEY_Item,
	BULLET_Item, // Resource of Gun
	BATTERY_Item // Resource of Lamp
} EItemType;

typedef struct gun {
	CP_Vector position_Bullet[MAX_BULLET];
	CP_Vector vector_Shooting[MAX_BULLET];
	float time_Shooting[MAX_BULLET];
	int count_Bullet;
	float radius_Bullet;
	float speed_Bullet;
	int attackPoint;
	//float range; // Shooting Range
} GUN;


typedef struct item_box {
	EItemType item_type;
	CP_Vector position;
	float radius;
	int isCollided; // Use with Array. Remove with List
}ITEM_BOX;

void init_itemBox(ITEM_BOX* item_box, EItemType itemType, CP_Vector position_itemBox);

// Need to Check Collision with player
void collide_itemBox(ITEM_BOX* item_box);

void print_itemBox(ITEM_BOX* item_box);

int get_Item_Type(ITEM_BOX* item_box);

int isEmptyBox(ITEM_BOX* item_box);

void init_Gun(GUN* gun);

int getIndexEmptyBullet(GUN* gun);

void addBullet_Gun(GUN* gun, CP_Vector startPosition, CP_Vector vectorShooting, int indexEmpty);

void update_Gun(GUN* gun, float dt);

int checkCollision_Bullet_Object(GUN* gun, CP_Vector positionObject, float radius);

//void endBullet(GUN* gun);

int isBulletShooting(float time_Shooting); 

void printBullet(GUN* gun);