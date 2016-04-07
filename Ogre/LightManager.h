#pragma once

class LightManager : public cSingleton<LightManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

public:
	void init()
	{

	}

	void clearClass()
	{

	}

	void setDefaultLight()
	{
		// ¶óÀÌÆ®
		mCoreStorage->mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
	}
};

