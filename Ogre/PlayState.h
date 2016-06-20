#pragma once
#include "GameState.h"

class PlayState : public GameState
{
// 맵 사이즈
#define mMapSize 1024


public:
	// 초기화
	void init()
	{
		// 기존모델 삭제
		mModelManager->clearModel();

		// 플레이어& 몬스터 초기화
		initPlayer("Player");
		initMonster("Monster", 20, mMapSize);

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
	void initPlayer(string _playerName)
	{
		// 플레이어 모델 추가
		mModelManager->addModel(_playerName.c_str(), "DustinBody.mesh");
		mModelManager->setPlayer(_playerName);

		// 플레이어 애니메이션 추가
		mModelManager->addAni(_playerName.c_str(), "Idle");
		mModelManager->addAni(_playerName.c_str(), "Run");
	}

	// 몬스터 초기화
	void initMonster(string _monsterName, int _mobAmount, int _mapSize)
	{
		// 임시버퍼
		char tBuf[512];
		char tSwapItoa[512];

		// 몬스터 네임 저장
		string tMonsterName = _monsterName;

		// 몹 갯수 만큼 반복
		for (int i = 0; i < _mobAmount; ++i)
		{
			// 버퍼 초기화
			memset(tBuf, '\0', sizeof(tBuf));
			memset(tSwapItoa, '\0', sizeof(tBuf));

			// itoa 치환 & 버퍼에 저장
			itoa10(i, tSwapItoa);
			tMonsterName += tSwapItoa;

			// 최종 이름 버퍼에 저장
			wsprintf(tBuf, tMonsterName.c_str());

			// 맵 사이즈 크기
			int mMaxMapSize = _mapSize * 2;

			// 몬스터 랜덤배치
			float tPosX = (float)(rand() % mMaxMapSize) - _mapSize;
			float tPosZ = (float)(rand() % mMaxMapSize) - _mapSize;

			// 몬스터 모델 추가 ( y굴곡 없음) 
			mModelManager->addModel(tBuf, "DustinBody.mesh", tPosX, 0.0f, tPosZ);
			mModelManager->setMonster(tMonsterName);

			// 몬스터 애니메이션 추가
			mModelManager->addAni(tMonsterName.c_str(), "Idle");
			mModelManager->addAni(tMonsterName.c_str(), "Run");
		}
	}

	// 10 진수 itoa
	void itoa10(int n, char *buf)
	{
		char temp[10];                // 최대 10 진수
		int  rem, i = 0;

		if (n == 0)
			temp[i++] = '0';
		while (n != 0) {
			rem = n % 10;             // 나머지 구하기 
			temp[i++] = rem + '0';
			n = n / 10;               // 몫 나누기
		}

		while (--i >= 0)              // 결과 반전
			*buf++ = temp[i];
		*buf = '\0';                  // eof 문자
	}

};

