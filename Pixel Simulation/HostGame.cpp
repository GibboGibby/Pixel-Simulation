#include "windowsstuff.h"

#include "HostGame.h"



HostGame::HostGame()
{
	Game::Game();
	gameType = HOST;
}

HostGame::~HostGame()
{
	Game::~Game();
}

void HostGame::Init()
{
	Game::Init();
	threadRunning = true;
	clientAcceptingThread = std::thread(&GibWindows::ClientAcceptThread, serverSocket, std::ref(clients), std::ref(serverMutex), std::ref(threadRunning));
	clientAcceptingThread.detach();
}

void HostGame::Cleanup()
{
	threadRunning = false;
	clientAcceptingThread.join();
	Game::Cleanup();
}

void HostGame::Update()
{
	Game::Update();

	for (int i = 0; i < clients.size(); i++)
	{

	}
}

void HostGame::Render()
{
	Game::Render();
}