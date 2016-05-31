#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// ��ƼƼ & �����
	std::vector<Entity*>    mEntityStorage;
	std::vector<SceneNode*> mSceneNode;

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
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

#ifdef DEBUG_MODE
		// �⺻ �Ž� �ʱ�ȭ
		_initDefaultMesh();
#endif
	}

	void clearClass()
	{

	}

	// �� Ŭ����
	void clearModel()
	{
		// ���ʿ��� �۾��� ���ϱ� ���� �˻�.
		// ���� ���� 1:1 �����̹Ƿ�, ���� �˻��ص� �������.
		if (mEntityStorage.size() > 0)
		{
			// �׸��� ����
			_resetShadow();

			// ���� ����
			mEntityStorage.clear();
			mSceneNode.clear();

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
	void addModel(char* _objName, char* _meshName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// ��ƼƼ & ��� �߰�
		mEntityStorage.push_back(mCoreStorage->mSceneMgr->createEntity(_objName, _meshName));
		mSceneNode.push_back(mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName, Vector3(_x, _y, _z)));
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
		// �� ���� �� ������Ʈ ���̱� ( 1:1 ���� )
		for (unsigned int i = 0; i < mSceneNode.size(); ++i)
		{
			mSceneNode[i]->attachObject(mEntityStorage[i]);
		}

		// �׸����ѱ�
		_setShadow();
	}

private:

	// �׸��� �ѱ�
	void _setShadow()
	{
		for (unsigned int i = 0; i < mEntityStorage.size(); ++i)
			mEntityStorage[i]->setCastShadows(true);
	}

	// �׸��� ����
	void _resetShadow()
	{
		for (unsigned int i = 0; i < mEntityStorage.size(); ++i)
			mEntityStorage[i]->setCastShadows(false);
	}

#ifdef DEBUG_MODE
	// �⺻ �Ž� �ʱ�ȭ
	void _initDefaultMesh()
	{
		// ��ǥ�� �Ž� �ʱ�ȭ
		_initAxis();

		// ���� �׸��� �ʱ�ȭ
		_initGrid();
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
#endif
};

