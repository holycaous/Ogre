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
	}

	// 씬 셋팅
	void setScene()
	{
		// 포스트 이펙트
		mPostEffect->setMainState();
	}
};

