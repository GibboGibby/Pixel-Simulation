#include "Game.h"
#include "raygui.h"
#include <iostream>
#include "Timer.h"
//#include "ShlObj.h"
#include <sstream>


Game::Game()
{
	
}

Game::~Game()
{
	//delete simulation;
}

void Game::Init()
{
	simulation = new Simulation();


	const char* str = getenv("APPDATA");
	std::stringstream ss;
	ss << str << "\\GoobyGames\\PixelSimulation\\Saves\\";
	if (!DirectoryExists(ss.str().c_str()))
	{
		std::filesystem::create_directories(ss.str().c_str());
	}
}

void Game::Update()
{
	if (IsKeyPressed(KEY_A))
	{
		std::cout << "A Pressed" << std::endl;
	}

	if (IsKeyPressed(KEY_F6))
	{
		SaveGame("save_data.gib");
	}
	if (IsKeyPressed(KEY_F7))
	{
		LoadGame("save_data.gib");
	}

	// Simulation Section
	if (simulation == nullptr) return;
	if (IsKeyPressed(KEY_SPACE))
	{
		simulation->TogglePause();
	}

	Timer timer;
	simulation->Update();
	std::cout << "Time taken for update: " << timer.ElapsedMillis() << "ms" << std::endl;
}

void Game::Render()
{
	Timer timer;
	simulation->Render();
	std::cout << "Time taken for render: " << timer.ElapsedMillis() << "ms" << std::endl;

}

void Game::Cleanup()
{
	delete simulation;
	simulation = nullptr;
}

void Game::Pause(bool shouldPuase)
{
	gamePaused = shouldPuase;
}

void Game::SaveGame(std::string filePath)
{

	const char* str = getenv("APPDATA");
	std::stringstream ss;
	ss << str << "\\GoobyGames\\PixelSimulation\\Saves\\" << filePath;
	std::cout << ss.str() << std::endl;
	simulation->SaveSimulation(ss.str());
}

void Game::LoadGame(std::string filePath)
{
	const char* str = getenv("APPDATA");

	std::stringstream ss;
	ss << str << "\\GoobyGames\\PixelSimulation\\Saves\\" << filePath;
	std::cout << ss.str() << std::endl;
	simulation->LoadSimulation(ss.str());
}
