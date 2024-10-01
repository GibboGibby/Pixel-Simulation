#pragma once
#include <raylib.h>
#include "Simulation.h"
class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

	void Cleanup();

	void Pause(bool shouldPuase);

private:
	bool gamePaused = false;
	Simulation* simulation;
};