#pragma once

class GameState
{
public:
	virtual void init()            = 0;
	virtual void clearClass()      = 0;
	virtual void draw()            = 0;
	virtual void update(float& dt) = 0;
};

