#pragma once
#include "GameStateSave.h"
#include "MainState.h"
#include "PlayState.h"

class GameStateManager : public cSingleton<GameStateManager>
{
	//���� ���ӻ���
	GameState *mGameState;

public:
	// �⺻ ���� ����
	void init();
	void clearClass();

	// ���ӻ��� ����
	void changeState(GameState* _NewState);

	//-------------------------------------//
	// ���ӻ��� ����
	//-------------------------------------//
	// �׸���
	void draw();

	// ������Ʈ
	void update(float dt);

	// ���������� ����Ǿ����� üũ �� ����
	void stageCheck();
};
