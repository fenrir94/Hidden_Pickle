
#include "player.h"
#include "gameManager.h"
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
	
	init_Gun(&(player->gun), player->shooting_Vector);

	init_Body_BodyPart(&(player->body), 3);
	init_Feet_BodyPart(&(player->feet), 2);
}

void update_Player(PLAYER* player, CP_Vector updateVector, float dt) {

	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));


	game_Manager.player.worldPos.x = clamp(game_Manager.player.worldPos.x + dPoistion.x, game_Manager.map_Bounds.minX, game_Manager.map_Bounds.maxX);
	game_Manager.player.worldPos.y = clamp(game_Manager.player.worldPos.y + dPoistion.y, game_Manager.map_Bounds.minY, game_Manager.map_Bounds.maxY);

	if (game_Manager.player.worldPos.x <= game_Manager.map_Bounds.minX && updateVector.x < 0)
	{
		dPoistion.x = 0;
	}
	if (game_Manager.player.worldPos.x >= game_Manager.map_Bounds.maxX && updateVector.x > 0)
	{
		dPoistion.x = 0;
	}
	if (game_Manager.player.worldPos.y <= game_Manager.map_Bounds.minY && updateVector.y < 0)
	{
		dPoistion.y = 0;
	}
	if (game_Manager.player.worldPos.y >= game_Manager.map_Bounds.maxY && updateVector.y > 0)
	{
		dPoistion.y = 0;
	}
	
	player->position.x += dPoistion.x;
	player->position.y += dPoistion.y;

	//if (CP_Vector_Length(updateVector) >= 1) {
	//	update_BodyPart(&(player->body), MOVE, dt);
	//	update_BodyPart(&(player->feet), MOVE, dt);
	//}
	if (player->life <= 0) {
		update_Bloodpool(&player->bloodpool);
	}
}

void rollback_Player_Position(PLAYER* player, CP_Vector updateVector, float dt)
{
	CP_Vector dPoistion = CP_Vector_Scale(updateVector, dt * (player->speed));

	player->position = CP_Vector_Subtract(player->position, dPoistion);

	game_Manager.player.worldPos.x = clamp(game_Manager.player.worldPos.x - dPoistion.x, game_Manager.map_Bounds.minX, game_Manager.map_Bounds.maxX);
	game_Manager.player.worldPos.y = clamp(game_Manager.player.worldPos.y - dPoistion.y, game_Manager.map_Bounds.minY, game_Manager.map_Bounds.maxY);
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
	if (isInvincibility(player, time_Present) == 0 ) {
		if (player->life > 0) {
			CP_Sound_Play(player_Hit_SFX_File);
		}

		player->life -= attackPoint;
		player->time_Hit = time_Present;
	}
	
	if (player->life == 0) {
		init_Bloodpool(&player->bloodpool, player->position, 5);
		CP_Sound_StopGroup(CP_SOUND_GROUP_2);
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
	float angle_player = getAngle_Vector_AxisX(player->shooting_Vector);

	if (player->life > 0) {
		print_Feet_BodyPart(&(player->feet), player->position, angle_player - 90);
		print_Body_BodyPart(&(player->body), player->position, angle_player - 90);
	}
	else {
		print_Bloodpool(&player->bloodpool);
	}

	CP_Settings_RectMode(CP_POSITION_CORNER);

	print_Player_Life(player, player->life);
	print_Player_Battery(player, player->battery);
	print_Player_Bulltet_UI(player, player->gun.count_Bullet);
	
	CP_Settings_RectMode(CP_POSITION_CENTER);
	printBullet(&(player->gun), player->position, angle_player - 90);

	print_Player_Aiming(player, player->gun.position_Gun);
}


void print_Player_Life(PLAYER* player, int life) {

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(player->position.x - 50, player->position.y - 90, 100, 20);

	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	float gap = (float)100 / BASIC_LIFE;

	for (int i = 0; i < life; i++) {
		//CP_Graphics_DrawCircle(50+(float)i*gap, 50, 80);
		//CP_Graphics_DrawCircle(player->position.x+(float)i*gap-50, player->position.y - 100, 40);
		CP_Graphics_DrawRect(player->position.x + (float)i * gap - 50, player->position.y -90, gap, 10);

	}

	
}

void print_Player_Battery(PLAYER* player, int battery)
{
	

	/*CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(player->position.x - 100, player->position.y - 80,200,6);*/

	//CP_Settings_Fill(CP_Color_Create(255, 0, 255, 0));
	//CP_Graphics_DrawRect(31, 101, 200, 30);

	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Graphics_DrawRect(player->position.x - 50, player->position.y - 80, (float)battery, 10);

}

void print_Player_Bulltet_UI(PLAYER* player, int count_Bullet)
{
	CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
	float gap = (float)100 / MAX_BULLET;
	
	//TO DO 
	//CP_Image imageBullet = CP_Image_Load("./Assets/Image/Bullet_2.png");

	
	for (int i = 0; i < count_Bullet; i++) {
		CP_Graphics_DrawRect(player->position.x - 50 + i * gap, player->position.y - 70, gap, 5);
		//CP_Image_Draw(imageBullet, player->position.x - 95 + i*gap , player->position.y - 60, 30, 30, 255);
	}

	
}

void print_Player_Aiming(PLAYER* player, CP_Vector vector_Gun)
{
	// print Aiming
	if (player->isAiming) {
		CP_Settings_Fill(CP_Color_Create(205, 127, 50, 255));
		for (int i = 0; i < 7; i++) {
			/*CP_Graphics_DrawRectAdvanced(player->position.x + i * player->shooting_Vector.x * 40,
				player->position.y + i * player->shooting_Vector.y * 40, 
				4, 20, getAngle_Vector_AxisX(player->shooting_Vector), 0);*/
			CP_Graphics_DrawRectAdvanced(player->gun.position_Gun.x + i * player->shooting_Vector.x * 30,player->gun.position_Gun.y + i * player->shooting_Vector.y * 30,
				4, 20, getAngle_Vector_AxisX(player->shooting_Vector), 0);

		}
	}
}

//To Do 
// check radius and distance to rollback player position
int checkPosition_inOtherObject_Player(PLAYER* player, CP_Vector position, float radius)
{
	float distance = CP_Vector_Distance(player->position, position);

	if (distance < radius/2) {
		return 1;
	}
	else {
		return 0;
	}
}
