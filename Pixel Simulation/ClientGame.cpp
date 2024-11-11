#include "windowsstuff.h"

#include "ClientGame.h"



ClientGame::ClientGame()
{
	Game::Game();
	gameType = CLIENT;
	timer.Reset();
}

ClientGame::~ClientGame()
{
	Game::~Game();
}

void ClientGame::Init()
{
	Game::Init();
	GibWindows::InitClient(clientSocket);
	timer.Reset();
}

void ClientGame::Cleanup()
{
	Game::Cleanup();
}

void ClientGame::Update()
{
	if (timer.Elapsed() >= NETWORK_WAIT_TIME)
	{
		//Receive Data

		// Reset Timer
		timer.Reset();
	}
	//Game::Update();
}

void ClientGame::Render()
{
	Game::Render();
}