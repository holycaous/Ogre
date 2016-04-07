#pragma once
#include "GameStateSave.h"
#include "MainState.h"
#include "PlayState.h"

class GameStateManager : public cSingleton<GameStateManager>
{
	//현재 게임상태
	GameState *mGameState;

public:
	// 기본 게임 상태
	void init();
	void clearClass();

	// 게임상태 변경
	void changeState(GameState* _NewState);

	//-------------------------------------//
	// 게임상태 변수
	//-------------------------------------//
	// 그리다
	void draw();

	// 업데이트
	void update(float dt);

	// 스테이지가 변경되었는지 체크 후 변경
	void stageCheck();
};
