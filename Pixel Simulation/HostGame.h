#pragma once
#include "Game.h"

class HostGame : public Game
{
public:
	HostGame();
	~HostGame();

	void Init();
	void Cleanup();

	void Update();
	void Render();

private:
	
};