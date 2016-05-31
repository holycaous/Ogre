#pragma once

class LightManager : public cSingleton<LightManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// 라이트 보관장소
	std::map<string, Light*> mLightStorage;

	// 주변광 세기
	float mAmbientPower = 0.45f;
public:
	void init()
	{
		// 기본셋팅
		_defaultSet();

		// 라이트 초기화
		_initLight();
	}

	void clearClass()
	{
		// 모든 라이트 끄기
		_allOffLight();

		// 라이트 초기화
		mLightStorage.clear();
	}

	void setDefaultLight()
	{
		// 라이트 설정

		// 임시@@@@@@@@ 모든 라이트 켜기
		_allOnLight();
	}

private:
	// 라이트 초기화
	void _initLight()
	{
		// 라이트 추가
		_addLight("SunLight", Light::LT_DIRECTIONAL, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f));
	
	
	}

	// 라이트 추가
	void _addLight(string _lightName, Light::LightTypes _lightType, Vector3 _color, Vector3 _dir, Vector3 _Pos)
	{
		Light* tLight;
		tLight = mCoreStorage->mSceneMgr->createLight(_lightName.c_str());
		tLight->setType(_lightType);
		tLight->setDiffuseColour(_color.x, _color.y, _color.z);
		tLight->setDirection(_dir);
		tLight->setPosition(_Pos);
		
		// 맵에 저장
		mLightStorage[_lightName] = tLight;
	}

	// 기본 셋팅
	void _defaultSet()
	{
		// 주변광 셋팅
		mCoreStorage->mSceneMgr->setAmbientLight(ColourValue(mAmbientPower, mAmbientPower, mAmbientPower));

		// 그림자 셋팅
		mCoreStorage->mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	}

	// 라이트 켜기
	void _onLight(string _lightName)
	{
		mLightStorage[_lightName]->setVisible(true);
	}

	// 라이트 끄기
	void _offLight(string _lightName)
	{
		mLightStorage[_lightName]->setVisible(false);
	}

	// 모든 라이트 켜기
	void _allOnLight()
	{
		for (auto itor = mLightStorage.begin(); itor != mLightStorage.end(); ++itor)
			itor->second->setVisible(true);
	}

	// 모든 라이트 끄기
	void _allOffLight()
	{
		for (auto itor = mLightStorage.begin(); itor != mLightStorage.end(); ++itor)
			itor->second->setVisible(false);
	}
};

