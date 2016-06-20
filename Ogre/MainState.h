#pragma once
#include "GameState.h"

class MainState : public GameState
{

public:
	// �ʱ�ȭ
	void init()
	{
		// ������ ����
		mModelManager->clearModel();

		// �� �߰�
		mModelManager->addModel("Professor", "DustinBody.mesh");

		// �� ����
		setScene();
	}

	// ����
	void clearClass()
	{

	}

	// ������Ʈ
	void update(float dt)
	{
		// �� ������Ʈ
		mModelManager->update(dt);
	}

	// �� ����
	void setScene()
	{
		// ����Ʈ ����Ʈ
		mPostEffect->setMainState();
	}
};

