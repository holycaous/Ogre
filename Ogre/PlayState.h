#pragma once
#include "GameState.h"

class PlayState : public GameState
{
// �� ������
#define mMapSize 1024


public:
	// �ʱ�ȭ
	void init()
	{
		// ������ ����
		mModelManager->clearModel();

		// �÷��̾�& ���� �ʱ�ȭ
		initPlayer("Player");
		initMonster("Monster", 20, mMapSize);

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
	void initPlayer(string _playerName)
	{
		// �÷��̾� �� �߰�
		mModelManager->addModel(_playerName.c_str(), "DustinBody.mesh");
		mModelManager->setPlayer(_playerName);

		// �÷��̾� �ִϸ��̼� �߰�
		mModelManager->addAni(_playerName.c_str(), "Idle");
		mModelManager->addAni(_playerName.c_str(), "Run");
	}

	// ���� �ʱ�ȭ
	void initMonster(string _monsterName, int _mobAmount, int _mapSize)
	{
		// �ӽù���
		char tBuf[512];
		char tSwapItoa[512];

		// ���� ���� ����
		string tMonsterName = _monsterName;

		// �� ���� ��ŭ �ݺ�
		for (int i = 0; i < _mobAmount; ++i)
		{
			// ���� �ʱ�ȭ
			memset(tBuf, '\0', sizeof(tBuf));
			memset(tSwapItoa, '\0', sizeof(tBuf));

			// itoa ġȯ & ���ۿ� ����
			itoa10(i, tSwapItoa);
			tMonsterName += tSwapItoa;

			// ���� �̸� ���ۿ� ����
			wsprintf(tBuf, tMonsterName.c_str());

			// �� ������ ũ��
			int mMaxMapSize = _mapSize * 2;

			// ���� ������ġ
			float tPosX = (float)(rand() % mMaxMapSize) - _mapSize;
			float tPosZ = (float)(rand() % mMaxMapSize) - _mapSize;

			// ���� �� �߰� ( y���� ����) 
			mModelManager->addModel(tBuf, "DustinBody.mesh", tPosX, 0.0f, tPosZ);
			mModelManager->setMonster(tMonsterName);

			// ���� �ִϸ��̼� �߰�
			mModelManager->addAni(tMonsterName.c_str(), "Idle");
			mModelManager->addAni(tMonsterName.c_str(), "Run");
		}
	}

	// 10 ���� itoa
	void itoa10(int n, char *buf)
	{
		char temp[10];                // �ִ� 10 ����
		int  rem, i = 0;

		if (n == 0)
			temp[i++] = '0';
		while (n != 0) {
			rem = n % 10;             // ������ ���ϱ� 
			temp[i++] = rem + '0';
			n = n / 10;               // �� ������
		}

		while (--i >= 0)              // ��� ����
			*buf++ = temp[i];
		*buf = '\0';                  // eof ����
	}

};

