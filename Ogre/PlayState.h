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

		// �� �߰�
		mModelManager->addModel("Professor", "DustinBody.mesh");
	}

	// ����
	void clearClass()
	{

	}

	// ������Ʈ
	void update(float dt)
	{

	}

	// �׸���
	void draw()
	{
		// �⺻ ����Ʈ
		mLightManager->setDefaultLight();

		// ��� ��� ���� ��Ű��
		mModelManager->DrawAll();
	}
};

