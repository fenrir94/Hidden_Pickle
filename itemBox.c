
#include "itemBox.h"

CP_Sound chest_Open_SFX_File;

void init_itemBox(ITEM_BOX* item_box, EItemType itemType, CP_Vector position_itemBox)
{
	item_box->item_type = itemType;
	item_box->position = CP_Vector_Set(position_itemBox.x, position_itemBox.y);
	item_box->radius = 50;
	item_box->isCollided = 0;

	chest_Open_SFX_File = CP_Sound_Load("Assets/SFX/chest_Open.ogg");
}

// To DO with Collision
// Need to Call this function with Collision
// Need to Change
// Call get_item
// Check not to display item box
void collide_itemBox(ITEM_BOX* item_box)
{
	CP_Sound_PlayAdvanced(chest_Open_SFX_File, 1, 1, FALSE, CP_SOUND_GROUP_0);
		
	item_box->isCollided = 1;
}

void print_itemBox(ITEM_BOX* item_box)
{
	//printf("%d\n", item_box->isCollided);
	if (item_box->isCollided == 0) {
		if (item_box->item_type == KEY_Item)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
		}
		else if (item_box->item_type == BULLET_Item)
		{
			CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
		}
		else if (item_box->item_type == BATTERY_Item)
		{
			CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));

		}

		CP_Graphics_DrawCircle(item_box->position.x, item_box->position.y, item_box->radius);
	}

}

int get_Item_Type(ITEM_BOX* item_box)
{
	return item_box->item_type;
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


