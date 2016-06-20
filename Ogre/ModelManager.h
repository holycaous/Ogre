#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// 엔티티 & 씬노드
	std::map<string, Model> mObjectStorage;

	// 플레이어 지정
	string mPlayer;
	std::list<string> mMonsterList;
	std::list<string> mItemList;

	// 플레이어 모델(제어하기 위해)
	SceneNode* mSelectPlayerModel;

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
		playrSetAni("Run");
	}

	void playerMoveY(float _power)
	{
		mObjectStorage[mPlayer].moveModelY(_power);
		playrSetAni("Run");

	}

	void playerMoveZ(float _power)
	{
		mObjectStorage[mPlayer].moveModelZ(_power);
		playrSetAni("Run");
	}
	
	// 플레이어 공격
	void playerAttack()
	{
		_playerAttack();
		//playrSetAni("Attack"); // 아직 이런 행동 없음 @@@@@@@@@
	}

private:
	// 플레이어 몬스터 공격
	void _playerAttack()
	{
		for (auto itor = mMonsterList.begin(); itor != mMonsterList.end(); ++itor)
		{
			// 선택된 모델
			Model& tModel = mObjectStorage[*itor];

			// 충돌이 됬다면, 공격 범위임
			if (tModel.mCrush)
			{
				// 몬스터 죽이기 @@@@@@@@@


			}
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
		Vector3 mPlayerPos = mSelectPlayerModel->getPosition();

		// 선택된 모델
		SceneNode* tSelectModel;

		// 몬스터 선택
		tSelectModel = getModel(*_itor);
		Model& tModel = mObjectStorage[*_itor];

		// 몬스터 좌표 선택
		Vector3 tMobModelPos = tSelectModel->getPosition();

		// 스피드 가져오기
		float tSpeed = tModel.mSpeed;

		// 충돌체크 확인
		_monsterCrushCheck(tModel, mPlayerPos, tMobModelPos);

		// 충돌이 되었다면?
		if (tModel.mCrush)
		{
			// 공격한다.


			// 애니메이션 변경
			tModel.setAni("Idle");
		}
		// 충돌이 안됬다면?
		else 
		{
			// 플레이어를 향해 움직이기
			Real tPosX = 0.0f;
			Real tPosZ = 0.0f;

			// 길이
			int _tLenghtX = (int)_ptLengh(mPlayerPos.x, tMobModelPos.x);
			int _tLenghtZ = (int)_ptLengh(mPlayerPos.z, tMobModelPos.z);

			// X가 더 큼?
			if (_tLenghtX * 24 > _tLenghtZ)
			{
				// X 이동
				if (!(mPlayerPos.x + 10.0f > tMobModelPos.x && mPlayerPos.x - 10.0f < tMobModelPos.x))
				{
					// 속도 * 방향
					tPosX = (Real)((mPlayerPos.x > tMobModelPos.x) ? tSpeed : -tSpeed);
					tPosX *= dt;

					// 모델이 바라보는 방향
					tModel.lookModelX(tPosX);
				}
			}
			// Z가 더 큼?
			else
			{
				// Z 이동
				if (!(mPlayerPos.z + 10.0f > tMobModelPos.z && mPlayerPos.z - 10.0f < tMobModelPos.z))
				{
					// 속도 * 방향
					tPosZ = (Real)((mPlayerPos.z > tMobModelPos.z) ? tSpeed : -tSpeed);
					tPosZ *= dt;

					// 모델이 바라보는 방향
					tModel.lookModelZ(tPosZ);
				}
			}

			// 모델 위치 이동
			tSelectModel->translate(tPosX, (Real)0, tPosZ);

			// 애니메이션 변경
			tModel.setAni("Run");
		}

		// 모델 업데이트
		tModel.update(dt);
	}

	// 몬스터 충돛체크
	void _monsterCrushCheck(Model& _MobModelPos, Vector3 _PlayerPos, Vector3 _MonsetPos)
	{
		// 충돌체크 (플레이어는 30.0f라고 잡음)
		_MobModelPos.mCrush = _ptToPt(_MobModelPos.mDist + 30.0f, _PlayerPos, _MonsetPos) ? true : false;
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

