#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// ��ƼƼ & �����
	std::map<string, Model> mObjectStorage;

	// �÷��̾� ����
	string mPlayer;
	std::list<string> mMonsterList;
	std::list<string> mItemList;

	// �÷��̾� ��(�����ϱ� ����)
	SceneNode* mSelectPlayerModel;

#ifdef DEBUG_MODE
	// ��ǥ�� ����
	Entity   * mAxis;
	SceneNode* mAxisNode;

	// �׸��� ����
	Ogre::ManualObject* gridPlane;
	Ogre::SceneNode   * gridPlaneNode;
	Ogre::MaterialPtr   gridPlaneMaterial;
#endif
public:
	void init()
	{
		// ���ҽ� �ʱ�ȭ
		ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
		ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

#ifdef DEBUG_MODE
		// �⺻ �Ž� �ʱ�ȭ
		_initDefaultMesh();
#endif
	}

	void clearClass()
	{
		// ���� ����
		mObjectStorage.clear();
	}

	// �� Ŭ����
	void clearModel()
	{
		// ���ʿ��� �۾��� ���ϱ� ���� �˻�.
		if (mObjectStorage.size() > 0)
		{
			// �÷��̾� �����
			mPlayer.clear();

			// ���� �����
			mMonsterList.clear();

			// ������ ��� �����
			mItemList.clear();

			// ���� ����
			mObjectStorage.clear();

			// �� Ŭ����
			mCoreStorage->mSceneMgr->clearScene();

			// �⺻ �Ž� �ٽ� �ʱ�ȭ
			_initDefaultMesh();
		}
	}

	// �� ��������
	SceneNode* getModel(string _name)
	{
		return mCoreStorage->mRoot->getSceneManager("main")->getSceneNode(_name.c_str());
	}

	// �� �߰�
	void addModel(string _objName, string _meshDataName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// �� �ӽ� �������
		Model tModel;

		// �� �ʱ�ȭ
		tModel.initModel(_objName, _meshDataName, _x, _y, _z);

		// �� ����
		mObjectStorage[_objName] = tModel;
	}

	// �ִϸ��̼� �߰�
	void addAni(string _objName, string _aniName)
	{
		mObjectStorage[_objName].initAni(_objName, _aniName);
	}

	// ������ �ִ°� �� �� ����
	void applyModel()
	{
#ifdef DEBUG_MODE
		// �׸��� ǥ��
		gridPlaneNode->attachObject(gridPlane);

		// ��ǥ�� ǥ��
		mAxisNode->attachObject(mAxis);
#endif
		// �Էµ� ��������, �� �𵨿� ����
		for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
			itor->second.applyModel();
	}

	// ������Ʈ
	void update(float& dt)
	{
		//// ��ü�� �ִϸ��̼� ������Ʈ
		//for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
		//	itor->second.update(dt);

		// �÷��̾� ������Ʈ
		mObjectStorage[mPlayer].update(dt);

		// ���� ������Ʈ
		_updateMonster(dt);
	}

	// ���� ����
	void setMonster(string _monsterName)
	{
		mMonsterList.push_back(_monsterName);
	}

	// �÷��̾� ����
	void setPlayer(string _playerName)
	{
		mPlayer = _playerName;

		// �÷��̾� �� ����(�����ϱ� ����)
		mSelectPlayerModel = getModel(_playerName.c_str());
	}

	// �÷��̾� �ִ� ����
	void playrSetAni(string _aniName)
	{
		mObjectStorage[mPlayer].setAni(_aniName);
	}

	// �÷��̾� �̵�
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
	
	// �÷��̾� ����
	void playerAttack()
	{
		_playerAttack();
		//playrSetAni("Attack"); // ���� �̷� �ൿ ���� @@@@@@@@@
	}

private:
	// �÷��̾� ���� ����
	void _playerAttack()
	{
		for (auto itor = mMonsterList.begin(); itor != mMonsterList.end(); ++itor)
		{
			// ���õ� ��
			Model& tModel = mObjectStorage[*itor];

			// �浹�� ��ٸ�, ���� ������
			if (tModel.mCrush)
			{
				// ���� ���̱� @@@@@@@@@


			}
		}
	}

	// ���� ������Ʈ
	void _updateMonster(float& dt)
	{
		// ���� ������Ʈ(���� �ൿ)
		for (auto itor = mMonsterList.begin(); itor != mMonsterList.end(); ++itor)
		{
			// ���� FSM
			_monsterFSM(dt, itor);
		}
	}

	// ���� FSM
	void _monsterFSM(float dt, std::list<string>::iterator _itor)
	{
		// ���� �÷��̾� ��ġ
		Vector3 mPlayerPos = mSelectPlayerModel->getPosition();

		// ���õ� ��
		SceneNode* tSelectModel;

		// ���� ����
		tSelectModel = getModel(*_itor);
		Model& tModel = mObjectStorage[*_itor];

		// ���� ��ǥ ����
		Vector3 tMobModelPos = tSelectModel->getPosition();

		// ���ǵ� ��������
		float tSpeed = tModel.mSpeed;

		// �浹üũ Ȯ��
		_monsterCrushCheck(tModel, mPlayerPos, tMobModelPos);

		// �浹�� �Ǿ��ٸ�?
		if (tModel.mCrush)
		{
			// �����Ѵ�.


			// �ִϸ��̼� ����
			tModel.setAni("Idle");
		}
		// �浹�� �ȉ�ٸ�?
		else 
		{
			// �÷��̾ ���� �����̱�
			Real tPosX = 0.0f;
			Real tPosZ = 0.0f;

			// ����
			int _tLenghtX = (int)_ptLengh(mPlayerPos.x, tMobModelPos.x);
			int _tLenghtZ = (int)_ptLengh(mPlayerPos.z, tMobModelPos.z);

			// X�� �� ŭ?
			if (_tLenghtX * 24 > _tLenghtZ)
			{
				// X �̵�
				if (!(mPlayerPos.x + 10.0f > tMobModelPos.x && mPlayerPos.x - 10.0f < tMobModelPos.x))
				{
					// �ӵ� * ����
					tPosX = (Real)((mPlayerPos.x > tMobModelPos.x) ? tSpeed : -tSpeed);
					tPosX *= dt;

					// ���� �ٶ󺸴� ����
					tModel.lookModelX(tPosX);
				}
			}
			// Z�� �� ŭ?
			else
			{
				// Z �̵�
				if (!(mPlayerPos.z + 10.0f > tMobModelPos.z && mPlayerPos.z - 10.0f < tMobModelPos.z))
				{
					// �ӵ� * ����
					tPosZ = (Real)((mPlayerPos.z > tMobModelPos.z) ? tSpeed : -tSpeed);
					tPosZ *= dt;

					// ���� �ٶ󺸴� ����
					tModel.lookModelZ(tPosZ);
				}
			}

			// �� ��ġ �̵�
			tSelectModel->translate(tPosX, (Real)0, tPosZ);

			// �ִϸ��̼� ����
			tModel.setAni("Run");
		}

		// �� ������Ʈ
		tModel.update(dt);
	}

	// ���� ���üũ
	void _monsterCrushCheck(Model& _MobModelPos, Vector3 _PlayerPos, Vector3 _MonsetPos)
	{
		// �浹üũ (�÷��̾�� 30.0f��� ����)
		_MobModelPos.mCrush = _ptToPt(_MobModelPos.mDist + 30.0f, _PlayerPos, _MonsetPos) ? true : false;
	}

	// �� �������� �Ÿ�
	bool _ptToPt(float _dist, Vector3 _pos1, Vector3 _pos2)
	{
		float _result = (_pos2.x - _pos1.x) * (_pos2.x - _pos1.x) + (_pos2.z - _pos1.z) * (_pos2.z - _pos1.z);
		return _dist * _dist >= _result;
	}

	// �������� ����
	float _ptLengh(float _pos1, float _pos2)
	{
		return (_pos2 - _pos1) * (_pos2 - _pos1);
	}


#ifdef DEBUG_MODE
	// �⺻ �Ž� �ʱ�ȭ
	void _initDefaultMesh()
	{
		// ��ǥ�� �Ž� �ʱ�ȭ
		_initAxis();

		// �׸��� �ʱ�ȭ
		_initGrid();

		// �� �ʱ�ȭ
		_initGround();
	}

	// ��ǥ�� �Ž� �ʱ�ȭ
	void _initAxis()
	{
		mAxis     = mCoreStorage->mSceneMgr->createEntity("Axis", "axes.mesh");
		mAxisNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("Axis", Vector3(0.0f, 0.0f, 0.0f));
		mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Axis")->setScale(5, 5, 5);
	}

	// �׸��� �ʱ�ȭ
	void _initGrid()
	{
		// �׸��� ���� & ��忡 ���
		gridPlane     = mCoreStorage->mSceneMgr->createManualObject("GridPlane");
		gridPlaneNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

		// ���� ����
		gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
		gridPlaneMaterial->setReceiveShadows(false);
		gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

		// �׸��� ��ǥ ���
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

	// �� �ʱ�ȭ
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
		ground->setMaterialName("KPU_LOGO"); // �ִϸ��̼��ִ� ���׸�����
		//mGround->setCastShadows(false);
	}
#endif
};

