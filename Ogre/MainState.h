#pragma once
#include "GameState.h"

class MainState : public GameState
{
	// 테스트용 코드
	SceneNode *mProfessorNode, *mNinjaNode;

public:
	// 초기화
	void init()
	{
		// 기존모델 삭제
		mModelManager->clearModel();

		// 모델 추가
		mModelManager->addModel("Professor", "DustinBody.mesh");
		mModelManager->addModel("Ninja", "ninja.mesh", 0.0f, 0.0f, 100.0f);




		// 테스트용 코드
		mProfessorNode = mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Professor");
		mNinjaNode     = mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Ninja");
	}

	// 제거
	void clearClass()
	{

	}

	// 업데이트
	void update(float dt)
	{
		// 테스트용 코드
		static float ninjaVelocity = 100.0f;

		if (mNinjaNode->getPosition().x < -400.f || mNinjaNode->getPosition().x > 400.0f)
			ninjaVelocity *= -1;
		mNinjaNode->translate(ninjaVelocity * dt, 0, 0);

	}

	// 그리기
	void draw()
	{
		// 기본 라이트
		mLightManager->setDefaultLight();

		// 모든 노드 연결 시키기
		mModelManager->DrawAll();
	}
};

