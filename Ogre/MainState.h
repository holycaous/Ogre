#pragma once
#include "GameState.h"

class MainState : public GameState
{
	// �׽�Ʈ�� �ڵ�
	SceneNode *mProfessorNode, *mNinjaNode;

public:
	// �ʱ�ȭ
	void init()
	{
		// ������ ����
		mModelManager->clearModel();

		// �� �߰�
		mModelManager->addModel("Professor", "DustinBody.mesh");
		mModelManager->addModel("Ninja", "ninja.mesh", 0.0f, 0.0f, 100.0f);




		// �׽�Ʈ�� �ڵ�
		mProfessorNode = mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Professor");
		mNinjaNode     = mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Ninja");
	}

	// ����
	void clearClass()
	{

	}

	// ������Ʈ
	void update(float dt)
	{
		// �׽�Ʈ�� �ڵ�
		static float ninjaVelocity = 100.0f;

		if (mNinjaNode->getPosition().x < -400.f || mNinjaNode->getPosition().x > 400.0f)
			ninjaVelocity *= -1;
		mNinjaNode->translate(ninjaVelocity * dt, 0, 0);

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

