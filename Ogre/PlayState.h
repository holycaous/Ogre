#pragma once
#include "GameState.h"

class PlayState : public GameState
{


public:
	// 초기화
	void init()
	{
		// 기존모델 삭제
		mModelManager->clearModel();

		// 모델 추가
		mModelManager->addModel("Professor", "DustinBody.mesh");
	}

	// 제거
	void clearClass()
	{

	}

	// 업데이트
	void update(float dt)
	{

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

