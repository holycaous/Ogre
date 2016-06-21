#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage  * mCoreStorage   = CoreStorage  ::getInstance();

	// 엔티티 & 씬노드
	std::map<string, Model> mObjectStorage;

	// 플레이어 지정
	string mPlayer;
	std::list<string> mMonsterList;
	std::list<string> mItemList;

	// 플레이어 모델(제어하기 위해)
	SceneNode* mSelectPlayerModel;

	// 몬스터 갯수
	int mMobAmount;

	// 처치 몬스터
	int mKillMobCount;

	// 게임끝(원래 여깄음 안되는데 순환참조때문에..)
	bool mGameState;

#ifdef DEBUG_MODE
	// 좌표계 전용
	Entity   * mAxis;
	SceneNode* mAxisNode;

	// 그리드 전용
	Ogre::ManualObject* gridPlane;
	Ogre::SceneNode   * gridPlaneNode;
	Ogre::MaterialPtr   gridPlaneMaterial;
#endif
public:
	void init()
	{
		// 리소스 초기화
		ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
		ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		// 변수 초기화
		mMobAmount = 0;
		mKillMobCount = 0;
		mGameState = false;

#ifdef DEBUG_MODE
		// 기본 매쉬 초기화
		_initDefaultMesh();
#endif
	}

	void clearClass()
	{
		// 버퍼 비우기
		mObjectStorage.clear();
	}

	// 모델 클리어
	void clearModel()
	{
		// 불필요한 작업은 안하기 위해 검사.
		if (mObjectStorage.size() > 0)
		{
			// 플레이어 지우기
			mPlayer.clear();

			// 몬스터 지우기
			mMonsterList.clear();

			// 아이템 목록 지우기
			mItemList.clear();

			// 버퍼 비우기
			mObjectStorage.clear();

			// 씬 클리어
			mCoreStorage->mSceneMgr->clearScene();

			// 기본 매쉬 다시 초기화
			_initDefaultMesh();
		}
	}

	// 모델 가져오기
	SceneNode* getModel(string _name)
	{
		return mCoreStorage->mRoot->getSceneManager("main")->getSceneNode(_name.c_str());
	}

	// 모델 추가
	void addModel(string _objName, string _meshDataName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// 모델 임시 저장공간
		Model tModel;

		// 모델 초기화
		tModel.initModel(_objName, _meshDataName, _x, _y, _z);

		// 모델 저장
		mObjectStorage[_objName] = tModel;
	}

	// 애니메이션 추가
	void addAni(string _objName, string _aniName)
	{
		mObjectStorage[_objName].initAni(_objName, _aniName);
	}

	// 무작정 있는거 다 씬 셋팅
	void applyModel()
	{
#ifdef DEBUG_MODE
		// 그리드 표시
		gridPlaneNode->attachObject(gridPlane);

		// 좌표계 표시
		mAxisNode->attachObject(mAxis);
#endif
		// 입력된 정보들을, 각 모델에 적용
		for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
			itor->second.applyModel();
	}

	// 업데이트
	void update(float& dt)
	{
		//// 전체모델 애니메이션 업데이트
		//for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
		//	itor->second.update(dt);

		// 플레이어 업데이트
		mObjectStorage[mPlayer].update(dt);

		// 몬스터 업데이트
		_updateMonster(dt);
	}

	// 몬스터 지정
	void setMonster(string _monsterName)
	{
		mMonsterList.push_back(_monsterName);
	}

	// 플레이어 지정
	void setPlayer(string _playerName)
	{
		mPlayer = _playerName;

		// 플레이어 모델 선택(제어하기 위해)
		mSelectPlayerModel = getModel(_playerName.c_str());
	}

	// 플레이어 애니 변경
	void playrSetAni(string _aniName)
	{
		mObjectStorage[mPlayer].setAni(_aniName);
	}

	// 플레이어 이동
	void playerMoveX(float _power)
	{
		mObjectStorage[mPlayer].moveModelX(_power);
		playrSetAni("Move");
	}

	void playerMoveY(float _power)
	{
		mObjectStorage[mPlayer].moveModelY(_power);
		playrSetAni("Move");

	}

	void playerMoveZ(float _power)
	{
		mObjectStorage[mPlayer].moveModelZ(_power);
		playrSetAni("Move");
	}
	
	// 플레이어 공격
	void playerAttack()
	{
		playrSetAni("Attack");
		_playerAttack();
	}

	// 플레이어 hp
	int getPlayerHP()
	{
		return mObjectStorage[mPlayer].mHP;
	}

	// 몬스터 추가하기(이후 생성 전용)
	void addMonster(string _monsterName, string _meshName)
	{
		// 임시버퍼
		char tBuf[512];
		char tSwapItoa[512];

		// 몬스터 네임 저장
		string tMonsterName = _monsterName;

		// 몹 갯수 만큼 반복
		// 버퍼 초기화
		memset(tBuf, '\0', sizeof(tBuf));
		memset(tSwapItoa, '\0', sizeof(tBuf));

		// itoa 치환 & 버퍼에 저장
		itoa10(++mMobAmount, tSwapItoa);
		tMonsterName += tSwapItoa;

		// 최종 이름 버퍼에 저장
		wsprintf(tBuf, tMonsterName.c_str());

		// 맵 사이즈 크기
		int mMaxMapSize = MAP_SIZE * 2;

		// 몬스터 랜덤배치
		float tPosX = (float)(rand() % mMaxMapSize) - MAP_SIZE;
		float tPosZ = (float)(rand() % mMaxMapSize) - MAP_SIZE;

		// 몬스터 모델 추가 ( y굴곡 없음) 
		addModel(tBuf, _meshName.c_str(), tPosX, 0.0f, tPosZ);
		setMonster(tMonsterName);

		// 몬스터 애니메이션 추가
		addAni(tBuf, "Attack");
		addAni(tBuf, "Move");

		// 몬스터 추가
		mObjectStorage[tBuf].applyModel();
	}

	// 몬스터 추가하기(첫 생성 전용)
	void initMonster(string _monsterName, string _meshName)
	{
		// 임시버퍼
		char tBuf[512];
		char tSwapItoa[512];

		// 몬스터 네임 저장
		string tMonsterName = _monsterName;

		// 몹 갯수 만큼 반복
		// 버퍼 초기화
		memset(tBuf, '\0', sizeof(tBuf));
		memset(tSwapItoa, '\0', sizeof(tBuf));

		// itoa 치환 & 버퍼에 저장
		itoa10(++mMobAmount, tSwapItoa);
		tMonsterName += tSwapItoa;

		// 최종 이름 버퍼에 저장
		wsprintf(tBuf, tMonsterName.c_str());

		// 맵 사이즈 크기
		int mMaxMapSize = MAP_SIZE * 2;

		// 몬스터 랜덤배치
		float tPosX = (float)(rand() % mMaxMapSize) - MAP_SIZE;
		float tPosZ = (float)(rand() % mMaxMapSize) - MAP_SIZE;

		// 몬스터 모델 추가 ( y굴곡 없음) 
		addModel(tBuf, _meshName.c_str(), tPosX, 0.0f, tPosZ);
		setMonster(tMonsterName);

		// 몬스터 애니메이션 추가
		addAni(tBuf, "Attack");
		addAni(tBuf, "Move");
	}

	// 오브젝트 추가하기(첫 생성 전용)
	void initObject(string _ObjectName, string _meshName)
	{
		addModel(_ObjectName.c_str(), _meshName.c_str());
	}

	// 게임 종료됬나?
	bool gameEnd()
	{
		return mGameState;
	}

	// 게임 종료 초기화
	void initGameEnd()
	{
		mGameState = false;
	}
private:
	// 플레이어 몬스터 공격
	void _playerAttack()
	{
		for (auto itor = mMonsterList.begin(); itor != mMonsterList.end(); ++itor)
		{
			// 선택된 모델
			Model tModel = mObjectStorage[*itor];

			// 충돌이 됬다면, 공격 범위임
			if (tModel.mCrush)
			{
				// 플레이어 카운트 증가 
				++mKillMobCount;
			
				// 몬스터 죽이기(...는 척하기), 새로운 지점에 몬스터 생성하기
				int mMaxMapSize = MAP_SIZE * 2;

				// 몬스터 랜덤배치
				Real tPosX = (Real)(rand() % mMaxMapSize) - MAP_SIZE;
				Real tPosZ = (Real)(rand() % mMaxMapSize) - MAP_SIZE;

				// 모델 이동시키기
				mObjectStorage[*itor].setPosition(tPosX, tPosZ);
			}
		}

		// 10마리이상 죽일때마다 상승
		if (!(mKillMobCount % 10))
		{
			// 몬스터 추가
			addMonster("Monster", "mob1.mesh");
		}
	}

	// 몬스터 업데이트
	void _updateMonster(float& dt)
	{
		// 몬스터 업데이트(개별 행동)
		for (auto itor = mMonsterList.begin(); itor != mMonsterList.end(); ++itor)
		{
			// 몬스터 FSM
			_monsterFSM(dt, itor);
		}
	}

	// 몬스터 FSM
	void _monsterFSM(float dt, std::list<string>::iterator _itor)
	{
		// 현재 플레이어 위치
		Vector3 tPlayerPos = mSelectPlayerModel->getPosition();

		// 선택된 모델
		SceneNode* tSelectModel;

		// 몬스터 선택
		tSelectModel = getModel(*_itor);
		Model& tModel = mObjectStorage[*_itor];

		// 몬스터 좌표 선택
		Vector3 tMobModelPos = tSelectModel->getPosition();

		// 충돌체크 확인
		_monsterCrushCheck(tModel, tPlayerPos, tMobModelPos);

		// 충돌이 되었다면?
		if (tModel.mCrush)
		{
			// 애니메이션 변경
			tModel.setAni("Attack");

			static int tAttackCount = 0;

			// 플레이어에게 데미지를 준다
			// HP가 0 이라면, 게임 종료
			if (mObjectStorage[mPlayer].mHP == 0)
			{
				mGameState = true;
			}
			//  HP가 0 이 아니라면,
			else
			{
				// 너무 빨리 달아서 ㅡㅡ;
				if (tAttackCount >= 10)
				{
					--mObjectStorage[mPlayer].mHP;
					tAttackCount = 0;
				}
				else
					++tAttackCount;
			}
		}
		// 충돌이 안됬다면?
		else 
		{
			// 애니메이션 변경
			tModel.setAni("Move");

			// 이동한다
			float tPosX = _mobMoveX(tModel, tPlayerPos, tMobModelPos);
			float tPosZ = _mobMoveZ(tModel, tPlayerPos, tMobModelPos);

			// 모델 위치 이동
			tSelectModel->translate(tPosX * dt, (Real)0, tPosZ * dt);
		}

		// 모델 업데이트
		tModel.update(dt);
	}

	// 몬스터 충돛체크
	void _monsterCrushCheck(Model& _MobModel, Vector3 _PlayerPos, Vector3 _MobPos)
	{
		// 충돌체크 (플레이어는 30.0f라고 잡음)
		_MobModel.mCrush = _ptToPt(_MobModel.mDist + 30.0f, _PlayerPos, _MobPos) ? true : false;
	}

	// 두 점사이의 거리
	bool _ptToPt(float _dist, Vector3 _pos1, Vector3 _pos2)
	{
		float _result = (_pos2.x - _pos1.x) * (_pos2.x - _pos1.x) + (_pos2.z - _pos1.z) * (_pos2.z - _pos1.z);
		return _dist * _dist >= _result;
	}

	// 두점사이 길이
	float _ptLengh(float _pos1, float _pos2)
	{
		return (_pos2 - _pos1) * (_pos2 - _pos1);
	}

#ifdef DEBUG_MODE
	// 기본 매쉬 초기화
	void _initDefaultMesh()
	{
		// 좌표계 매쉬 초기화
		_initAxis();

		// 그리드 초기화
		_initGrid();

		// 땅 초기화
		_initGround();
	}

	// 몬스터 x이동
	// 더 리펙할수 있지만, 일단 이렇게 하자 ㅡ,.ㅡ
	float _mobMoveX(Model& _MobModel, Vector3 _PlayerPos, Vector3 _MobPos)
	{
		// 플레이어를 향해 움직이기
		Real tPosX = 0.0f;

		// 스피드 가져오기
		float tSpeed = _MobModel.mSpeed;

		// X 이동
		if (!(_PlayerPos.x + 10.0f > _MobPos.x && _PlayerPos.x - 10.0f < _MobPos.x))
		{
			// 속도 * 방향
			tPosX = (Real)((_PlayerPos.x > _MobPos.x) ? tSpeed : -tSpeed);

			// 모델이 바라보는 방향
			_MobModel.lookModelX(tPosX);
		}

		return tPosX;
	}

	// 몬스터 z이동
	float _mobMoveZ(Model& _MobModel, Vector3 _PlayerPos, Vector3 _MobPos)
	{
		// 플레이어를 향해 움직이기
		Real tPosZ = 0.0f;

		// 스피드 가져오기
		float tSpeed = _MobModel.mSpeed;

		// Z 이동
		if (!(_PlayerPos.z + 10.0f > _MobPos.z && _PlayerPos.z - 10.0f < _MobPos.z))
		{
			// 속도 * 방향
			tPosZ = (Real)((_PlayerPos.z > _MobPos.z) ? tSpeed : -tSpeed);

			// 모델이 바라보는 방향
			_MobModel.lookModelZ(tPosZ);
		}

		return tPosZ;
	}

	// 좌표계 매쉬 초기화
	void _initAxis()
	{
		mAxis     = mCoreStorage->mSceneMgr->createEntity("Axis", "axes.mesh");
		mAxisNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("Axis", Vector3(0.0f, 0.0f, 0.0f));
		mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Axis")->setScale(5, 5, 5);
	}

	// 그리드 초기화
	void _initGrid()
	{
		// 그리드 생성 & 노드에 등록
		gridPlane     = mCoreStorage->mSceneMgr->createManualObject("GridPlane");
		gridPlaneNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

		// 재질 생성
		gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
		gridPlaneMaterial->setReceiveShadows(false);
		gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

		// 그리드 좌표 찍기
		gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);

		for (int i = 0; i < 21; i++)
		{
			gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
			gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

			gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
			gridPlane->position(-500.f + i * 50, 0.f, -500.f);
		}

		gridPlane->end();
	}

	// 땅 초기화
	void _initGround()
	{
		Plane plane(Vector3::UNIT_Y, 0);
		MeshManager::getSingleton().createPlane(
			"Ground",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane,
			500, 500,
			1, 1,
			true, 1, 5, 5,
			Vector3::NEGATIVE_UNIT_Z
			);

		Entity* ground = mCoreStorage->mSceneMgr->createEntity("GroundPlane", "Ground");
		mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
		ground->setMaterialName("KPU_LOGO"); // 애니메이션있는 메테리얼임
		//mGround->setCastShadows(false);
	}
#endif
};

