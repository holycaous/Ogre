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

		// 플레이어& 몬스터 초기화
		_initPlayer("Player");
		_initMonster("Monster", MOB_MIN_AMOUNT);

		// 오브젝트 초기화
		_initObject();

		// 기본 셋
		setScene();
	}

	// 제거
	void clearClass()
	{

	}

	// 업데이트
	void update(float dt)
	{
		// 모델 업데이트 (애니메이션을 위한)
		mModelManager->update(dt);

		// 포스트 이펙트 업데이트
		mPostEffect->update();
	}

	// 씬 셋팅
	void setScene()
	{
		// 기본 라이트
		mLightManager->setDefaultLight();

		// 모든 모델 적용& 씬 노드 연결
		mModelManager->applyModel();

		// 포스트 이펙트
		mPostEffect->setPlayState();
	}
private:
	// 플레이어 초기화
	void _initPlayer(string _playerName)
	{
		// 플레이어 모델 추가
		mModelManager->addModel(_playerName.c_str(), "mob1.mesh");
		mModelManager->setPlayer(_playerName);

		// 플레이어 애니메이션 추가
		mModelManager->addAni(_playerName.c_str(), "Attack");
		mModelManager->addAni(_playerName.c_str(), "Move");
	}

	// 오브젝트 초기화
	void _initObject()
	{
		mModelManager->initObject("ground", "Ground.mesh", 4510.0f);
		mModelManager->getModel("ground")->rotate(Vector3(0.0f, 1.0f, 0.0f), Radian(-45.0f), Node::TS_WORLD);
	}

	// 몬스터 초기화
	void _initMonster(string _monsterName, int _mobAmount)
	{
		// 몬스터 네임 저장
		string tMonsterName = _monsterName;

		// 몹 갯수 만큼 반복
		for (int i = 0; i < _mobAmount; ++i)
		{
			switch (rand() % 2)
			{
			case 0:
				// 몬스터 생성
				mModelManager->initMonster(_monsterName, "mob1.mesh", 45.0f);
				break;
			case 1:
				// 몬스터 생성
				mModelManager->initMonster(_monsterName, "mob2.mesh", 58.0f);
				break;
			}
		}
	}
};

