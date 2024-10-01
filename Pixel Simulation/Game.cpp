#include "Game.h"
#include "raygui.h"
#include <iostream>

Game::Game()
{
	simulation = new Simulation();
}

Game::~Game()
{
	//delete simulation;
}

void Game::Update()
{
	if (IsKeyPressed(KEY_A))
	{
		std::cout << "A Pressed" << std::endl;
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		simulation->TogglePause();
	}
}

void Game::Render()
{
}

void Game::Cleanup()
{
	delete simulation;
}

void Game::Pause(bool shouldPuase)
{
	gamePaused = shouldPuase;
}
