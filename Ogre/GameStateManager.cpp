#include "stdafx.h"
#include "GameStateManager.h"

// 기본 게임 상태
void GameStateManager::init()
{
	mGameState = nullptr;
	changeState(new MainState); //게임상태 변경
}
void GameStateManager::clearClass()
{
	//무언가 값이 들어가있다면
	if (mGameState != nullptr)
	{
		mGameState->clearClass();
		delete mGameState;

		mGameState = nullptr;
	}
}

// 게임상태 변경
void GameStateManager::changeState(GameState* _NewState)
{
	clearClass();

	mGameState = _NewState;
	mGameState->init();
}

//-------------------------------------//
// 게임상태 변수
//-------------------------------------//
// 씬 셋팅
void GameStateManager::setScene()
{
	//스테이지가 존재하는지
	if (mGameState)
		mGameState->setScene();
}

// 업데이트
void GameStateManager::update(float dt)
{
	//스테이지가 변경되었는지
	stageCheck();

	//스테이지가 존재하는지
	if (mGameState)
		mGameState->update(dt);
}

// 스테이지가 변경되었는지 체크 후 변경
void GameStateManager::stageCheck()
{
	if (GameStateSave::getInstance()->stateChangeCheck)
	{
		switch (GameStateSave::getInstance()->stateChaneNumber)
		{
		case e_MainState:
			changeState(new MainState);
			break;

		case e_PlayState:
			changeState(new PlayState);
			break;

		default:
			break;
		}
		GameStateSave::getInstance()->stateChangeCheck = false;
	}
}