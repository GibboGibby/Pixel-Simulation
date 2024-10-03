#include "Game.h"
#include "raygui.h"
#include <iostream>
#include "Timer.h"

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
}

void Game::Update()
{
	if (IsKeyPressed(KEY_A))
	{
		std::cout << "A Pressed" << std::endl;
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
