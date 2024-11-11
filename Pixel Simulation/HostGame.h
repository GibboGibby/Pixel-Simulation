#pragma once
#include "windowsstuff.h"
#include "Game.h"
#include <mutex>
#include <thread>

class HostGame : public Game
{
public:
	HostGame();
	~HostGame();

	void Init();
	void Cleanup();

	void Update();
	void Render();

	void SetPort(std::string port) { serverPort = port; }

private:
	std::vector<GibWindows::Client> clients;
	int serverSocket;
	std::mutex serverMutex;
	std::thread clientAcceptingThread;
	bool threadRunning = false;
	Timer timer;

	std::string serverPort;
};