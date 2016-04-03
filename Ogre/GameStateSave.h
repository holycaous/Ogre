#pragma once
class GameStateSave : public cSingleton<GameStateSave>
{
public:
	bool stateChangeCheck = false;
	int  stateChaneNumber = 0;
};
