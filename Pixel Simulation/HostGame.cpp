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
	GibWindows::CloseSocketAndCleanup(serverSocket);
	Game::Cleanup();
}

void HostGame::Update()
{
	Game::Update();

	// Server Stuff 1/50ms
	if (timer.Elapsed() >= NETWORK_WAIT_TIME)
	{
		std::cout << "Sending Data to Client" << std::endl;
		// Get data as char*
		char* data = simulation->GetPixelAsCharArray();

		// Send to all Clients
		for (int i = 0; i < clients.size(); i++)
		{
			GibWindows::SendDataToClient(serverSocket, clients[i], data, simulation->GetSizeInBytes());
		}
		//Cleanup data
		delete[] data;

		// Reset Timer
		timer.Reset();
	}
	
}

void HostGame::Render()
{
	Game::Render();
}