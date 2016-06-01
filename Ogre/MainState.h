#pragma once
#include "GameState.h"

class MainState : public GameState
{
public:
	// 초기화
	void init()
	{
		// 기존모델 삭제
		mModelManager->clearModel();

		// 모델 추가
		mModelManager->addModel("Professor", "DustinBody.mesh");
		mModelManager->addModel("Ninja", "ninja.mesh", 0.0f, 0.0f, 100.0f);

		// 모델 애니메이션 추가
		mModelManager->addAni("Professor", "Idle");
		mModelManager->addAni("Professor", "Run");

		// 플레이어 지정
		mModelManager->setPlayer("Professor");

		// 씬 셋팅
		setScene();
	}

	// 제거
	void clearClass()
	{

	}

	// 업데이트
	void update(float dt)
	{
		// 모델 업데이트
		mModelManager->update(dt);

		// 선택된 모델
		SceneNode* tSelectModel;

		// 테스트용 코드
		static float ninjaVelocity = 100.0f;

		// 모델 선택
		tSelectModel = mModelManager->getModel("Ninja");

		// 닌자이동 
		if (tSelectModel->getPosition().x < -400.f || tSelectModel->getPosition().x > 400.0f)
			ninjaVelocity *= -1;
		tSelectModel->translate(ninjaVelocity * dt, 0, 0);

	}

	// 씬 셋팅
	void setScene()
	{
		// 기본 라이트
		mLightManager->setDefaultLight();

		// 모든 모델 적용& 씬 노드 연결
		mModelManager->applyModel();
	}
};

