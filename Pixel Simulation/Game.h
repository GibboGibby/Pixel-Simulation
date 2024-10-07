#pragma once
#include <raylib.h>
#include "Simulation.h"
#include <filesystem>

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

	void SaveGame(std::string filePath);
	void LoadGame(std::string filePath);

private:
	bool gamePaused = false;
	bool saveScreen = false;
	Simulation* simulation;
};