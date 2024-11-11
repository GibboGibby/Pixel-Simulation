#include "windowsstuff.h"

#include "HostGame.h"



HostGame::HostGame()
{
	Game::Game();
	gameType = HOST;
	
	timer.Reset();
}

HostGame::~HostGame()
{
	Game::~Game();
}

void HostGame::Init()
{
	Game::Init();
	GibWindows::InitServer(serverSocket);
	threadRunning = true;
	clientAcceptingThread = std::thread(&GibWindows::ClientAcceptThread, serverSocket, std::ref(clients), std::ref(serverMutex), std::ref(threadRunning));
	clientAcceptingThread.detach();
	timer.Reset();
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

	// Server Stuff 1/50ms
	if (timer.Elapsed() >= NETWORK_WAIT_TIME)
	{
		// Get data as char*
		

		// Send to all Clients
		for (int i = 0; i < clients.size(); i++)
		{
			
		}

		// Reset Timer
		timer.Reset();
	}
	
}

void HostGame::Render()
{
	Game::Render();
}