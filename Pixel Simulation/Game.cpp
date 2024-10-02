#include "Game.h"
#include "raygui.h"
#include <iostream>

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

	simulation->Update();
}

void Game::Render()
{
	simulation->Render();
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
