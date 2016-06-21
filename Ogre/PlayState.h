#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	// �ʱ�ȭ
	void init()
	{
		// ������ ����
		mModelManager->clearModel();

		// �÷��̾�& ���� �ʱ�ȭ
		_initPlayer("Player");
		_initMonster("Monster", MOB_MIN_AMOUNT);

		// ������Ʈ �ʱ�ȭ
		_initObject();

		// �⺻ ��
		setScene();
	}

	// ����
	void clearClass()
	{

	}

	// ������Ʈ
	void update(float dt)
	{
		// �� ������Ʈ (�ִϸ��̼��� ����)
		mModelManager->update(dt);

		// ����Ʈ ����Ʈ ������Ʈ
		mPostEffect->update();
	}

	// �� ����
	void setScene()
	{
		// �⺻ ����Ʈ
		mLightManager->setDefaultLight();

		// ��� �� ����& �� ��� ����
		mModelManager->applyModel();

		// ����Ʈ ����Ʈ
		mPostEffect->setPlayState();
	}
private:
	// �÷��̾� �ʱ�ȭ
	void _initPlayer(string _playerName)
	{
		// �÷��̾� �� �߰�
		mModelManager->addModel(_playerName.c_str(), "mob1.mesh");
		mModelManager->setPlayer(_playerName);

		// �÷��̾� �ִϸ��̼� �߰�
		mModelManager->addAni(_playerName.c_str(), "Attack");
		mModelManager->addAni(_playerName.c_str(), "Move");
	}

	// ������Ʈ �ʱ�ȭ
	void _initObject()
	{
		mModelManager->initObject("testObj", "testObj.mesh");
	}

	// ���� �ʱ�ȭ
	void _initMonster(string _monsterName, int _mobAmount)
	{
		// ���� ���� ����
		string tMonsterName = _monsterName;

		// �� ���� ��ŭ �ݺ�
		for (int i = 0; i < _mobAmount; ++i)
		{
			// ���� ����
			mModelManager->initMonster(_monsterName, "mob1.mesh");
		}
	}
};

