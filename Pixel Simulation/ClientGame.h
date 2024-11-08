#pragma once
#include "Game.h"

class ClientGame : public Game
{
public:
	ClientGame();
	~ClientGame();

	void Init();
	void Cleanup();

	void Update();
	void Render();
};