
#include "itemBox.h"

void init_itemBox(ITEM_BOX* item_box, EItemType itemType, CP_Vector position_itemBox)
{
	item_box->item_type = itemType;
	item_box->position = CP_Vector_Set(position_itemBox.x, position_itemBox.y);
	item_box->radius = 50;
	item_box->isCollided = 0;

	//FILE* p_file = fopen("item_box_data.txt", "r");

	//if (!p_file)
	//{
	//	exit(1);
	//}
	//for (int i = 0; i < BOX_CNT; i++)
	//{
	//	fscanf_s(p_file, "%d %f %f ", &(item_box[i].type), &(item_box[i].position.x), &(item_box[i].position.y));
	//	item_box[i].radius = 40;
	//	MoveCoords(&(item_box[i].position.x), &(item_box[i].position.y));
	//}

	//fclose(p_file);
}

// To DO with Collision
// Need to Call this function with Collision
// Need to Change
// Call get_item
// Check not to display item box
int collide_itemBox(ITEM_BOX* item_box)
{
	int itemGet = get_item(item_box->item_type);

	item_box->isCollided = 1;

	return itemGet;
}

void print_itemBox(ITEM_BOX* item_box)
{
	//printf("%d\n", item_box->isCollided);
	if (item_box->isCollided == 0) {
		if (item_box->item_type == KEY_Item)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
			CP_Graphics_DrawCircle(item_box->position.x, item_box->position.y, item_box->radius);

		}
		else if (item_box->item_type == BULLET_Item)
		{
			CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
			CP_Graphics_DrawCircle(item_box->position.x, item_box->position.y, item_box->radius);

		}
		else if (item_box->item_type == BATTERY_Item)
		{
			CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
			CP_Graphics_DrawCircle(item_box->position.x, item_box->position.y, item_box->radius);

		}
	}

}

int get_item(EItemType item_type)
{
	if (item_type == KEY_Item)
	{
		return 1;

	}
	else if (item_type == BULLET_Item)
	{
		return 4;
	}
	else if (item_type == BATTERY_Item)
	{
		return 50;
	}

	return 0;
}

int isEmptyBox(ITEM_BOX* item_box)
{
	if (item_box->isCollided) {
		return 1;
	}
	else {
		return 0;
	}
}

void init_Gun(GUN* gun)
{
	gun->bullets = 2;
	gun->attackPoint = 1;
}
