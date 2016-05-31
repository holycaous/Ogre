#pragma once

class GameState
{
protected:
	CoreStorage * mCoreStorage  = CoreStorage ::getInstance();
	LightManager* mLightManager = LightManager::getInstance();
	ModelManager* mModelManager = ModelManager::getInstance();

public:
	virtual void init()            = 0;
	virtual void clearClass()      = 0;
	virtual void setScene()            = 0;
	virtual void update(float dt) = 0;
};

