#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// ��ƼƼ & �����
	std::vector<Entity*>    mEntity;
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
		// �⺻ �ʱ�ȭ
		_initDefault();
#endif
	}

	void clearClass()
	{

	}

	// �� Ŭ����
	void clearModel()
	{
		mEntity.clear();
		mSceneNode.clear();
	}

	// �� �߰�
	void addModel(char* _objName, char* _meshName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// ��ƼƼ & ��� �߰�
		mEntity   .push_back(mCoreStorage->mSceneMgr->createEntity(_objName, _meshName));
		mSceneNode.push_back(mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName, Vector3(_x, _y, _z)));
	}

	// ������ �ִ°� �� �׸���
	void DrawAll()
	{
#ifdef DEBUG_MODE
		// �׸��� ǥ��
		gridPlaneNode->attachObject(gridPlane);
#endif

		// ��� ������Ʈ ���̱�
		for (unsigned int i = 0; i < mSceneNode.size(); ++i)
			mSceneNode[i]->attachObject(mEntity[i]);
	}

private:
#ifdef DEBUG_MODE
	// �⺻ �ʱ�ȭ
	void _initDefault()
	{
		// ��ǥ�� �Ž� �ʱ�ȭ
		mAxis     = mCoreStorage->mSceneMgr->createEntity("Axis", "axes.mesh");
		mAxisNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("Axis", Vector3(0.0f, 0.0f, 0.0f));
		mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Axis")->setScale(5, 5, 5);

		// ���� �׸��� �ʱ�ȭ
		_initGrid();
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

