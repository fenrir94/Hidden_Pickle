#include "resultScreen.h"

void init_Result_Screen(RESULT_SCREEN* result_screen)
{
	result_screen->gameState = GAME_STATE_PLAYING;
	result_screen->isScreenOn = RESULT_SCREEN_OFF;
}

void update_Result_Screen(RESULT_SCREEN* result_screen, int gameResult)
{
	result_screen->gameState = gameResult;
	result_screen->isScreenOn = RESULT_SCREEN_ON;
}

void print_Result_Screen(RESULT_SCREEN* result_screen)
{
	// ������ ���� ȭ�� ��� ���� ���İ� ������

	// �������� Ŭ���� ȭ�� ���
	// �¸� �� ����Ʈ �޴�, ���� ��������, �ٽ��ϱ� ��ư ���
	// + stagenum == maxstage -> ���� �������� ��ư ��Ȱ��ȭ
	// �й� �� ����Ʈ �޴�, ���� ��������(off), �ٽ��ϱ� ��ư ��� 
}

/*
game_Manager.light.lightState = end;
update_Light(game_Manager.light.lightState);
*/
