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

#define MAX_BULLET 6
#define MAX_BATTERY 20

typedef enum item {
	KEY_Item,
	BULLET_Item, // Resource of Gun
	BATTERY_Item // Resource of Lamp
} EItemType;

typedef struct gun {
	int bullets;
	int attackPoint;
} GUN;

typedef struct item_box {
	EItemType item_type;
	CP_Vector position;
	float radius;
	int isCollided; // Use with Array. Remove with List
}ITEM_BOX;

void init_itemBox(ITEM_BOX* item_box, EItemType itemType, CP_Vector position_itemBox);

// Need to Check Collision with player
int collide_itemBox(ITEM_BOX* item_box);


void print_itemBox(ITEM_BOX* item_box);


int get_item(EItemType item_type);

int isEmptyBox(ITEM_BOX* item_box);

void init_Gun(GUN* gun);