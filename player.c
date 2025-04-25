
#include "player.h"
#include "utility.h"

CP_Sound player_Hit_SFX_File;

void init_Player(PLAYER* player, CP_Vector startPosition) {
	player->position.x = startPosition.x;
	player->position.y = startPosition.y;
	player->speed = 200;
	player->life = 3;
	player->radius = 50;
	player->getKey = 0;
	player->battery = 80;
	player->isLampOn = 0;
	player->time_Hit = 0;
	player->shooting_Vector = CP_Vector_Normalize(CP_Vector_Subtract(getMousePosition(), player->position));

	player_Hit_SFX_File = CP_Sound_Load("Assets/SFX/hit_Sound.wav");
	
	init_Gun(&(player->gun));

	init_Body_BodyPart(&(player->body), 3);
	init_Feet_BodyPart(&(player->feet), 2);
}

void update_Player(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	//player->position = CP_Vector_Add(player->position, dPoistion);
	player->position.x = clamp(player->position.x + dPoistion.x, 0, (float)CP_System_GetWindowWidth());
	player->position.y = clamp(player->position.y + dPoistion.y, 0, (float)CP_System_GetWindowHeight());

	//if (CP_Vector_Length(updateVector) >= 1) {
	//	update_BodyPart(&(player->body), MOVE, dt);
	//	update_BodyPart(&(player->feet), MOVE, dt);
	//}

}

void rollback_Player_Position(PLAYER* player, CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Subtract(player->position, dPoistion);
}

int check_Collision_Player_Object(PLAYER* player, CP_Vector position_Object, float radius_Object)
{
	return checkCollision_Circle_to_Circle(player->position, player->radius, position_Object, radius_Object);
}


int isInvincibility(PLAYER* player, float dt)
{
	if (dt - player->time_Hit <= TIME_INVINCIBILITY) {
		return 1;
	}
	else {
		return 0;
	}
}

void rotate_Player(PLAYER* player)
{
	player->shooting_Vector = CP_Vector_Normalize(CP_Vector_Subtract(getMousePosition(), player->position));
	//printf("Shooting Vector X: %f,  Y: %f\n", player->shooting_Vector.x, player->shooting_Vector.y);
	//printf("Shooting Vector Angle %f\n", getAngle_Vector_AxisX(player->shooting_Vector));
}

void getDamage_Player(PLAYER* player, int attackPoint) {
	float time_Present = CP_System_GetSeconds();
	if (isInvincibility(player, time_Present) == 0) {
		CP_Sound_Play(player_Hit_SFX_File);

		player->life -= attackPoint;
		player->time_Hit = time_Present;
	}
	
}

void use_Battery(PLAYER* player) {
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		player->battery -= 10;
	}
	int useBattery = get_InputSpace();
	
	if (useBattery > 0 && player->battery > 0)
	{
		player->isLampOn = 1;
	}
	else {
		player->isLampOn = 0;
	}

	if (player->battery > useBattery) {
		player->battery -= useBattery;
	}
	else {
		player->battery = 0;
	}
}

void checkAiming_Player(PLAYER* player, CP_KEY key, CP_KEY mouse)
{
	if (CP_Input_KeyTriggered(key) || CP_Input_MouseTriggered(mouse)) {
		if (player->isAiming == 0) {
			player->isAiming = 1;
		}
		else  {
			player->isAiming = 0;
		}
	}

	//printf("is Aiming? %d\n", player->gun.isAiming);
}

int shootingBullet_Player(PLAYER* player, CP_KEY key, CP_KEY mouse)
{	
	int checkShooting = 0;
	if (CP_Input_KeyTriggered(key) || CP_Input_MouseTriggered(mouse)) {
		int bulletIndex = getIndexEmptyBullet(&(player->gun));
		if (player->gun.count_Bullet > 0 && bulletIndex != -1) {			
			addBullet_Gun(&(player->gun), player->position, player->shooting_Vector, bulletIndex);
			player->gun.count_Bullet--;
			//printf("Bullet Index! %d\n", bulletIndex);
			
			checkShooting = 1;
		}
	}
	return checkShooting;
}

void get_Item(PLAYER* player, EItemType item_type) {
	printf("Get Item! %d\n", item_type);
	if (item_type == KEY_Item)
	{
		player->getKey = 1;
		printf("Get Key! %d\n", player->getKey);
	}
	else if (item_type == BULLET_Item)
	{
		if (player->gun.count_Bullet + 6 > MAX_BULLET) {
			player->gun.count_Bullet = MAX_BULLET;
		}
		else {
			player->gun.count_Bullet += 6;
			printf("Get Bullets! %d\n", player->gun.count_Bullet);
		}
	}
	else if (item_type == BATTERY_Item)
	{
		if (player->battery + 50 > MAX_BATTERY) {
			player->battery = MAX_BATTERY;
		}
		else {
			player->battery += 40;
			printf("Get Battery! %d\n", player->battery);
		}
	}
}

void print_Player(PLAYER* player) {
	
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 150));
	float angle_player = getAngle_Vector_AxisX(player->shooting_Vector);
	//CP_Graphics_DrawRectAdvanced(player->position.x + player->shooting_Vector.x*10,player->position.y + player->shooting_Vector.y*10, 10, 100, angle_player,0);

	float time_present = CP_System_GetSeconds();
	if ((int)((time_present - player->time_Hit) * 10) % 2 != 1 && time_present - player->time_Hit <= TIME_INVINCIBILITY) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle(player->position.x, player->position.y, player->radius);
	}
	else {
		//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	}

	/*CP_Image_DrawAdvanced(player->imageFeet_Player, player->position.x, player->position.y, 
		(float)CP_Image_GetWidth(player->imageFeet_Player) * 3 / 5, (float)CP_Image_GetHeight(player->imageFeet_Player) * 3 / 5, 
		255, angle_player - 90);
	CP_Image_DrawAdvanced(player->imageBody_Player, player->position.x, player->position.y, 
		(float)CP_Image_GetWidth(player->imageBody_Player)*3/5, (float)CP_Image_GetHeight(player->imageBody_Player)*3/5,
		255, angle_player-90);*/

	print_Feet_BodyPart(&(player->feet), player->position, angle_player - 90);
	print_Body_BodyPart(&(player->body), player->position, angle_player - 90);


	print_Player_Life(player->life);
	print_Player_Battery(player->battery);
	print_Player_Bulltet_UI(player->gun.count_Bullet);
	
	print_Player_Aiming(player);
}


void print_Player_Life(int life) {
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	int gap = 100;

	for (int i = 0; i < life; i++) {
		CP_Graphics_DrawCircle(50+(float)i*gap, 50, 80);
	}
}

void print_Player_Battery(int battery)
{
	CP_Settings_RectMode(CP_POSITION_CORNER);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(30,100,202,32);

	//CP_Settings_Fill(CP_Color_Create(255, 0, 255, 0));
	//CP_Graphics_DrawRect(31, 101, 200, 30);

	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Graphics_DrawRect(31, 101, (float)battery*2, 30);

	CP_Settings_RectMode(CP_POSITION_CENTER);

}

void print_Player_Bulltet_UI(int count_Bullet)
{
	CP_Settings_Fill(CP_Color_Create(205, 127, 50, 255));
	int gap = 15;

	for (int i = 0; i < count_Bullet; i++) {
		CP_Graphics_DrawRect((float)35+i*gap, 200, 10, 50);
	}
}


void print_Player_Aiming(PLAYER* player)
{
	// print Aiming
	if (player->isAiming) {
		CP_Settings_Fill(CP_Color_Create(205, 127, 50, 255));
		for (int i = 0; i < 8; i++) {
			CP_Graphics_DrawRectAdvanced(player->position.x + i * player->shooting_Vector.x * 40, player->position.y + i * player->shooting_Vector.y * 40, 4, 20, getAngle_Vector_AxisX(player->shooting_Vector), 0);
		}
	}
}
