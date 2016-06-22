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
		mModelManager->initObject("ground", "Ground.mesh", 4510.0f);
		mModelManager->getModel("ground")->rotate(Vector3(0.0f, 1.0f, 0.0f), Radian(-45.0f), Node::TS_WORLD);
	}

	// ���� �ʱ�ȭ
	void _initMonster(string _monsterName, int _mobAmount)
	{
		// ���� ���� ����
		string tMonsterName = _monsterName;

		// �� ���� ��ŭ �ݺ�
		for (int i = 0; i < _mobAmount; ++i)
		{
			switch (rand() % 2)
			{
			case 0:
				// ���� ����
				mModelManager->initMonster(_monsterName, "mob1.mesh", 45.0f);
				break;
			case 1:
				// ���� ����
				mModelManager->initMonster(_monsterName, "mob2.mesh", 58.0f);
				break;
			}
		}
	}
};

