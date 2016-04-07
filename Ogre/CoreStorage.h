#pragma once

class CoreStorage : public cSingleton<CoreStorage>
{
public:
	Root*         mRoot;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
};

