#pragma once
#include <raylib.h>
#include "Simulation.h"
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Cleanup();

	void Update();
	void Render();


	void Pause(bool shouldPuase);

private:
	bool gamePaused = false;
	Simulation* simulation;
};