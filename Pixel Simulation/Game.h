#pragma once
#include <raylib.h>
#include "Timer.h"
#include "Simulation.h"

#define NETWORK_WAIT_TIME 1.0f / 60.0f

#include <filesystem>

enum GameType
{
	SOLO,
	HOST,
	CLIENT
};

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

	GameType gameType = SOLO;
protected:
	bool gamePaused = false;
	bool saveScreen = false;
	Simulation* simulation;

};