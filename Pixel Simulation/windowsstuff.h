#pragma once
#include <vector>
#include <mutex>

namespace GibWindows
{
	struct Client
	{
		uint32_t clientAddr;
		int clientSocket;
	};
	void Test();


	void Init(int& serverSocket);

	void CloseSocketAndCleanup(int socket);

	//bool CheckForNewClient(Client& client);

	void ClientAcceptThread(int serverSocket, std::vector<Client>& clients, std::mutex& mutex, bool& threadRunning);
}