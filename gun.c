
#include "gun.h"

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
		if (!isBulletShooting(gun->time_Shooting[i])) {
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
			endBullet(gun, i);
		}
	}

	return checkCollision;
}


int isBulletShooting(float time_Shooting)
{
	return CP_System_GetSeconds() - time_Shooting < TIME_BULLLET;
}

void printBullet(GUN* gun)
{
	// print bullet
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 150));

	for (int i = 0; i < MAX_BULLET; i++) {
		if (isBulletShooting(gun->time_Shooting[i])) {
			CP_Graphics_DrawCircle(gun->position_Bullet[i].x, gun->position_Bullet[i].y, gun->radius_Bullet);
		}
	}
}

void endBullet(GUN* gun, int indexBullet)
{
	gun->time_Shooting[indexBullet] = 0;
}
