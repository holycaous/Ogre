#pragma once

// 스테이지
enum
{
	e_MainState = 0,
	e_PlayState = 1
};

// 엔티티 데이터
class Model
{
public:
	// 모델 정보
	Entity   * mObject;

	// 월드 매트릭스
	SceneNode* mWdMtx;

	// 방향 벡터
	Vector3 mLookDir;

	// 애니메이션 저장정보
	std::map<string, AnimationState*> mAniStorage;

	// 현재 실행되는 에니메이션
	AnimationState* mSelctAni;

	// 델타 타임
	float mDeltaTime;

	// 스피드
	float mSpeed;

	// 체력
	int mHP;

	// 충돌 여부
	bool mCrush;

	// 반지름
	float mDist;

public:
	~Model()
	{
		// 씬에서 떼기
		_clearClass();
	}

	// 모델 초기화
	void initModel(string _objName, string _meshDataName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		mLookDir = Vector3(0.0f, 0.0f, -1.0f);
		mObject  = CoreStorage::getInstance()->mSceneMgr->createEntity(_objName.c_str(), _meshDataName.c_str());
		mWdMtx   = CoreStorage::getInstance()->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName.c_str(), Vector3(_x, _y, _z));

		// 변수 초기화
		mSpeed = (float)((rand() % 150) + 100);
		mHP    = 60;
		mCrush = false;
		mDist  = 50.0f;

		// 강제로 키우기
		float tSize = 45.0f;
		mWdMtx->setScale(Vector3(tSize, tSize, tSize));
	}

	// 애니메이션 초기화
	void initAni(string _objName, string _aniName)
	{
		// 애니메이션 추가
		AnimationState* tNewAni = CoreStorage::getInstance()->mRoot->getSceneManager("main")->getEntity(_objName.c_str())->getAnimationState(_aniName.c_str());

		// 애니메이션 저장 (애니메이션 이름으로 찾아야함)
		mAniStorage[_aniName] = tNewAni;
	}

	void applyModel()
	{
		// 입력된 모델 붙이기
		mWdMtx->attachObject(mObject);

		// 애니메이션 켜기
		_initAni("Move");

		// 그림자켜기
		_setShadow();
	}

	// 좀 뗍시다 거 ㅡㅡ
	void detachObj()
	{
		mWdMtx->detachObject(mObject);
	}
	
	// 업데이트
	void update(float& dt)
	{
		// 델타 타임
		mDeltaTime = dt;

		// 애니메이션 업데이트
		_aniUpdate(dt);
	}

	// 모델 이동시키기
	void moveModelX(float& _power)
	{
		// 방향
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(tDir, 0.0f, 0.0f);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// 이동
		Vector3 tPos = mWdMtx->getPosition();
		if (tPos.x > -MAP_SIZE && tPos.x < MAP_SIZE)
			mWdMtx->translate(_power * mDeltaTime, 0.0f, 0.0f);
		else
			mWdMtx->setPosition(0.0f, 0.0f, 0.0f);
	}

	void moveModelY(float& _power)
	{
		// 방향
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(0.0f, tDir, 0.0f);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// 이동
		Vector3 tPos = mWdMtx->getPosition();
		if (tPos.y > -MAP_SIZE && tPos.y < MAP_SIZE)
			mWdMtx->translate(0.0f, _power * mDeltaTime, 0.0f);
		else
			mWdMtx->setPosition(0.0f, 0.0f, 0.0f);
	}

	void moveModelZ(float& _power)
	{
		// 방향
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(0.0f, 0.0f, tDir);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// 이동
		Vector3 tPos = mWdMtx->getPosition();
		if (tPos.z > -MAP_SIZE && tPos.z < MAP_SIZE)
			mWdMtx->translate(0.0f, 0.0f, _power * mDeltaTime);
		else
			mWdMtx->setPosition(0.0f, 0.0f, 0.0f);
	}

	// 바라보는 방향
	void lookModelX(float& _power)
	{
		// 방향
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(tDir, 0.0f, 0.0f);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);
	}

	// 바라보는 방향
	void lookModelZ(float& _power)
	{
		// 방향
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(0.0f, 0.0f, tDir);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);
	}

	// 애니메이션 선택
	void setAni(string _aniName)
	{
		// 애니메이션이 있다면,
		if (mAniStorage.size() != 0)
		{
			// 기존 애니 끄기
			mSelctAni->setLoop(false);
			mSelctAni->setEnabled(false);

			// 애니메이션 선택
			mSelctAni = mAniStorage[_aniName];

			// 새로운 애니메이션 가동
			mSelctAni->setLoop(true);
			mSelctAni->setEnabled(true);
		}
	}

	// 위치 지정
	void setPosition(Real _x, Real _z)
	{
		mWdMtx->setPosition(_x, (Real)0, _z);
	}

private:
	// 클래스 삭제
	void _clearClass()
	{
		// 애니메이션 창고 제거
		mAniStorage.clear();
	}

	// 그림자 켜기
	void _setShadow()
	{
		mObject->setCastShadows(true);
	}

	// 그림자 끄기
	void _resetShadow()
	{
		mObject->setCastShadows(false);
	}

	// 초기화 전용
	void _initAni(string _aniName)
	{
		// 애니메이션이 있다면,
		if (mAniStorage.size() != 0)
		{
			// 애니메이션 선택
			mSelctAni = mAniStorage[_aniName];

			// 새로운 애니메이션 가동
			mSelctAni->setLoop(true);
			mSelctAni->setEnabled(true);
		}
	}

	// 애니메이션 업데이트
	void _aniUpdate(float& dt)
	{
		// 애니메이션이 있다면,
		if (mAniStorage.size() != 0)
			mSelctAni->addTime(dt);
	}
};