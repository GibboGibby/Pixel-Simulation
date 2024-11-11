#pragma once
#include <vector>
#include <mutex>

namespace GibWindows
{
	struct HiddenClient;
	struct Client
	{
		uint32_t clientAddr;
		unsigned short clientPort;
		int clientSocket;
		HiddenClient* client;
	};

	void Test();


	void InitServer(int& serverSocket, std::string port);

	void InitClient(int& clientSocket);

	void CloseSocketAndCleanup(int socket);

	void SendDataToClient(int serverSocket, Client client, char* data, uint32_t sizeOfData);

	bool ReceiveData(int socket, char* data, uint32_t sizeOfData);

	void SendData(int socket, char* data, uint32_t sizeOfData, std::string ip, std::string port);

	void JoinServerClients(int socket, std::string ip, std::string port);

	void ClientAcceptThread(int serverSocket, std::vector<Client>& clients, std::mutex& mutex, bool& threadRunning);

	void SetSocketToNonBlocking(int socket);
}