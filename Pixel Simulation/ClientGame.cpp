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
	GibWindows::SetSocketToNonBlocking(clientSocket);
	GibWindows::JoinServerClients(clientSocket, serverIp, serverPort);
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
		// Receive Data
		char* data = new char[SCREEN_HEIGHT * SCREEN_WIDTH];
		//memset(data, 0, SCREEN_HEIGHT * SCREEN_WIDTH);
		if (GibWindows::ReceiveData(clientSocket, data, SCREEN_HEIGHT * SCREEN_WIDTH))
		{
			if (IsKeyDown(KEY_M))
			{
				std::cout << "First few data" << std::endl;
				std::string thing;
				for (int i = 0; i < 100; i++)
				{
					thing += GetNameByPixelType((PixelType)data[i]) + " ";
				}
				std::cout << thing << std::endl;
			}
			std::cout << "Data has been recieved" << std::endl;
			simulation->SetPixelFromCharArray(data);
		}
		// Cleanup Data
		delete[] data;

		// Reset Timer
		timer.Reset();
	}
	//Game::Update();
}

void ClientGame::Render()
{
	Game::Render();
}