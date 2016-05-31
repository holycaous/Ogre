#pragma once

class LightManager : public cSingleton<LightManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// ����Ʈ �������
	std::map<string, Light*> mLightStorage;

	// �ֺ��� ����
	float mAmbientPower = 0.45f;
public:
	void init()
	{
		// �⺻����
		_defaultSet();

		// ����Ʈ �ʱ�ȭ
		_initLight();
	}

	void clearClass()
	{
		// ��� ����Ʈ ����
		_allOffLight();

		// ����Ʈ �ʱ�ȭ
		mLightStorage.clear();
	}

	void setDefaultLight()
	{
		// ����Ʈ ����

		// �ӽ�@@@@@@@@ ��� ����Ʈ �ѱ�
		_allOnLight();
	}

private:
	// ����Ʈ �ʱ�ȭ
	void _initLight()
	{
		// ����Ʈ �߰�
		_addLight("SunLight", Light::LT_DIRECTIONAL, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f));
	
	
	}

	// ����Ʈ �߰�
	void _addLight(string _lightName, Light::LightTypes _lightType, Vector3 _color, Vector3 _dir, Vector3 _Pos)
	{
		Light* tLight;
		tLight = mCoreStorage->mSceneMgr->createLight(_lightName.c_str());
		tLight->setType(_lightType);
		tLight->setDiffuseColour(_color.x, _color.y, _color.z);
		tLight->setDirection(_dir);
		tLight->setPosition(_Pos);
		
		// �ʿ� ����
		mLightStorage[_lightName] = tLight;
	}

	// �⺻ ����
	void _defaultSet()
	{
		// �ֺ��� ����
		mCoreStorage->mSceneMgr->setAmbientLight(ColourValue(mAmbientPower, mAmbientPower, mAmbientPower));

		// �׸��� ����
		mCoreStorage->mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	}

	// ����Ʈ �ѱ�
	void _onLight(string _lightName)
	{
		mLightStorage[_lightName]->setVisible(true);
	}

	// ����Ʈ ����
	void _offLight(string _lightName)
	{
		mLightStorage[_lightName]->setVisible(false);
	}

	// ��� ����Ʈ �ѱ�
	void _allOnLight()
	{
		for (auto itor = mLightStorage.begin(); itor != mLightStorage.end(); ++itor)
			itor->second->setVisible(true);
	}

	// ��� ����Ʈ ����
	void _allOffLight()
	{
		for (auto itor = mLightStorage.begin(); itor != mLightStorage.end(); ++itor)
			itor->second->setVisible(false);
	}
};

