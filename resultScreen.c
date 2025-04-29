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
	// 반투명 검은 화면 출력 점점 알파값 높여서

	// 스테이지 클리어 화면 출력
	// 승리 시 셀렉트 메뉴, 다음 스테이지, 다시하기 버튼 출력
	// + stagenum == maxstage -> 다음 스테이지 버튼 비활성화
	// 패배 시 셀렉트 메뉴, 다음 스테이지(off), 다시하기 버튼 출력 
}

/*
game_Manager.light.lightState = end;
update_Light(game_Manager.light.lightState);
*/
