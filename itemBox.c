
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
void collide_itemBox(ITEM_BOX* item_box)
{
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
			CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));	}
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


void init_Gun(GUN* gun)
{
	gun->count_Bullet = 2;
	gun->attackPoint = 1;
	gun->radius_Bullet = 10;
	gun->speed_Bullet = 800;
	for (int i = 0; i < MAX_BULLET; i++) {
		gun->position_Bullet[i] = CP_Vector_Set(0, 0);
		gun->vector_Shooting[i] = CP_Vector_Set(0, 0);
		gun->time_Shooting[i] = 0;
	}
}

int getIndexEmptyBullet(GUN* gun) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!isBulletShooting(gun->time_Shooting[i]) ) {
			return i;
		}
	}

	return -1; // FULL
}

void addBullet_Gun(GUN* gun, CP_Vector startPosition, CP_Vector vectorShooting, int indexEmpty) {
	gun->position_Bullet[indexEmpty] = CP_Vector_Add(startPosition, CP_Vector_Scale(vectorShooting, 100));
	gun->vector_Shooting[indexEmpty] = vectorShooting;
	gun->time_Shooting[indexEmpty] = CP_System_GetSeconds();

	printf("Shoot! %f %f\n", vectorShooting.x, vectorShooting.y);
}

void update_Gun(GUN* gun, float dt)
{
	for (int i = 0; i < MAX_BULLET; i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			gun->position_Bullet[i].x += gun->vector_Shooting[i].x * dt * gun->speed_Bullet;
			gun->position_Bullet[i].y += gun->vector_Shooting[i].y * dt * gun->speed_Bullet;
		} 
	}
}

int checkCollision_Bullet_Object(GUN* gun, CP_Vector positionObject, float radius)
{
	int checkCollision = 0;
	for (int i = 0; i < MAX_BULLET; i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			checkCollision = checkCollision_Circle_to_Circle(gun->position_Bullet[i], gun->radius_Bullet, positionObject, radius);
		}
	}

	return checkCollision;
}


int isBulletShooting(float time_Shooting)
{
	return CP_System_GetSeconds() - time_Shooting  < TIME_BULLLET;
}

void printBullet(GUN* gun)
{
	// print bullet
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 150));

	for (int i = 0; i < MAX_BULLET; i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			CP_Graphics_DrawCircle(gun->position_Bullet[i].x, gun->position_Bullet[i].y, gun->radius_Bullet );
		}
	}
}
