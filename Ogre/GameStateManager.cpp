#include "stdafx.h"
#include "GameStateManager.h"

// �⺻ ���� ����
void GameStateManager::init()
{
	mGameState = nullptr;
	changeState(new MainState); //���ӻ��� ����
}
void GameStateManager::clearClass()
{
	//���� ���� ���ִٸ�
	if (mGameState != nullptr)
	{
		mGameState->clearClass();
		delete mGameState;

		mGameState = nullptr;
	}
}

// ���ӻ��� ����
void GameStateManager::changeState(GameState* _NewState)
{
	clearClass();

	mGameState = _NewState;
	mGameState->init();
}

//-------------------------------------//
// ���ӻ��� ����
//-------------------------------------//
// �� ����
void GameStateManager::setScene()
{
	//���������� �����ϴ���
	if (mGameState)
		mGameState->setScene();
}

// ������Ʈ
void GameStateManager::update(float dt)
{
	//���������� ����Ǿ�����
	stageCheck();

	//���������� �����ϴ���
	if (mGameState)
		mGameState->update(dt);
}

// ���������� ����Ǿ����� üũ �� ����
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