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

typedef enum item {
	key,
	bullet,
	battery
} EItemType;

typedef struct item_box {
	EItemType type;
	CP_Vector position;
	float radius;
}Item_box;