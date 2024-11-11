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
	GibWindows::JoinServerClients(clientSocket);
	timer.Reset();
}

void ClientGame::Cleanup()
{
	Game::Cleanup();
	GibWindows::CloseSocketAndCleanup(clientSocket);
}

void ClientGame::Update()
{
	if (timer.Elapsed() >= NETWORK_WAIT_TIME)
	{
		//Receive Data
		char* data = new char[SCREEN_HEIGHT * SCREEN_WIDTH];
		GibWindows::ReceiveData(clientSocket, data, simulation->GetSizeInBytes());
		simulation->SetPixelFromCharArray(data);
		// Reset Timer
		timer.Reset();
	}
	//Game::Update();
}

void ClientGame::Render()
{
	Game::Render();
}