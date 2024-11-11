#pragma once
#include "Game.h"

class ClientGame : public Game
{
public:
	ClientGame();
	~ClientGame();

	void Init();
	void Cleanup();

	void Update();
	void Render();

	void SetIPAndPort(std::string ip, std::string port) { serverIp = ip; serverPort = port; }

private:
	int clientSocket;
	Timer timer;

	std::string serverIp;
	std::string serverPort;
};