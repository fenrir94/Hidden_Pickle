#include "bodyPart.h"
#include "stdlib.h"

//void init_Body_Part(BODY_PART* body_Part, int count_Animation )
//{
//	body_Part->count_Animation = count_Animation;
//	for (int i = 0; i < body_Part->count_Animation; i++) {
//		init_Animation(&(body_Part->animation[i]));
//	}
//}

void init_Body_BodyPart(BODY_PART* body_Part, int count_Animation)
{
	body_Part->count_Animation = count_Animation;
	body_Part->animation = malloc(body_Part->count_Animation * sizeof(ANIMATION));
	init_Animation(&(body_Part->animation[0]),"Assets/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_",20);
	init_Animation(&(body_Part->animation[1]),"Assets/Top_Down_Survivor/handgun/move/survivor-move_handgun_",20);
	init_Animation(&(body_Part->animation[2]), "Assets/Top_Down_Survivor/handgun/shoot/survivor-shoot_handgun_",3);
	body_Part->animation_Type = IDLE;
}

void init_Feet_BodyPart(BODY_PART* body_Part, int count_Animation)
{
	body_Part->count_Animation = count_Animation;
	body_Part->animation = malloc(body_Part->count_Animation * sizeof(ANIMATION));
	init_Animation(&(body_Part->animation[0]), "Assets/Top_Down_Survivor/feet/idle/survivor-idle_",1);
	init_Animation(&(body_Part->animation[1]), "Assets/Top_Down_Survivor/feet/run/survivor-run_",20);
	body_Part->animation_Type = IDLE;
}

void changeAnimation_BodyPart(BODY_PART* body_Part, EAnimationType animation_Type)
{
	if (body_Part->animation_Type != animation_Type) {
		body_Part->animation[body_Part->animation_Type].currentFrame = 0;
		body_Part->animation[body_Part->animation_Type].frameTimer = 0;
		body_Part->animation_Type = animation_Type;
	}
}

void update_BodyPart(BODY_PART* body_Part, float df)
{
	update_Animation(&(body_Part->animation[body_Part->animation_Type]), df);
}

void print_Body_BodyPart(BODY_PART* body_Part, CP_Vector position, float angle)
{
	switch (body_Part->animation_Type) {
	case IDLE:
		print_Animation(&(body_Part->animation[IDLE]), position, angle);
		break;
	case MOVE:
		print_Animation(&(body_Part->animation[MOVE]), position, angle);
		break;
	default:
		print_Animation(&(body_Part->animation[IDLE]), position, angle);
	}
}

void print_Feet_BodyPart(BODY_PART* body_Part, CP_Vector position, float angle)
{
	switch (body_Part->animation_Type) {
	case IDLE:
		print_Animation(&(body_Part->animation[IDLE]), position, angle);
		break;
	case MOVE:
		print_Animation(&(body_Part->animation[MOVE]), position, angle);
		break;
	default:
		print_Animation(&(body_Part->animation[IDLE]), position, angle);
	}
}
