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
		mModelManager->addModel("Ninja", "ninja.mesh", 0.0f, 0.0f, 100.0f);

		// �� �ִϸ��̼� �߰�
		mModelManager->addAni("Professor", "Idle");
		mModelManager->addAni("Professor", "Run");

		// �÷��̾� ����
		mModelManager->setPlayer("Professor");

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

		// ���õ� ��
		SceneNode* tSelectModel;

		// �׽�Ʈ�� �ڵ�
		static float ninjaVelocity = 100.0f;

		// �� ����
		tSelectModel = mModelManager->getModel("Ninja");

		// �����̵� 
		if (tSelectModel->getPosition().x < -400.f || tSelectModel->getPosition().x > 400.0f)
			ninjaVelocity *= -1;
		tSelectModel->translate(ninjaVelocity * dt, 0, 0);

	}

	// �� ����
	void setScene()
	{
		// �⺻ ����Ʈ
		mLightManager->setDefaultLight();

		// ��� �� ����& �� ��� ����
		mModelManager->applyModel();
	}
};

