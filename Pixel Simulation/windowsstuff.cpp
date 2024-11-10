#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "windowsstuff.h"
namespace GibWindows
{

	void Test() {
		std::cout << "Test Run!" << std::endl;
	}


	void Init(int& serverSocket)
	{
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "Winsock initialization failed" << std::endl;
			return;
		}

		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == -1)
		{
			std::cerr << "Error creating socket" << std::endl;
			CloseSocketAndCleanup(serverSocket);
			return;
		}

		struct sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(12345);
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		{
			std::cerr << "Error binding socket!" << std::endl;
			CloseSocketAndCleanup(serverSocket);
			return;
		}

		if (listen(serverSocket, SOMAXCONN) == -1)
		{
			std::cerr << "Error listening for connections" << std::endl;
			CloseSocketAndCleanup(serverSocket);
			return;
		}
	}

	void CloseSocketAndCleanup(int socket)
	{
		closesocket(socket);
		WSACleanup();
	}

	void ClientAcceptThread(int serverSocket, std::vector<Client>& clients, std::mutex& mutex, bool& threadRunning)
	{
		while (threadRunning)
		{
			struct sockaddr_in clientAddress;
			socklen_t clientAddressSize = sizeof(clientAddress);
			int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
			if (clientSocket == -1) {
			}
			else
			{
				std::cout << "Connection Receieved" << std::endl;
				mutex.lock();
				Client client;

				//client.clientAddr = static_cast<int>((&clientAddress)->sin_addr.S_un.S_addr);
				client.clientAddr = clientAddress.sin_addr.S_un.S_addr;
				client.clientSocket = clientSocket;
				clients.push_back(client);
				mutex.unlock();
			}
		}
	}

	bool CheckForNewClient(int serverSocket, Client& client)
	{
		struct sockaddr_in clientAddress;
		socklen_t clientAddressSize = sizeof(clientAddress);
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
		if (clientSocket == -1) {
			return false;
		}
		else
		{
			std::cout << "Connection Receieved" << std::endl;
			return true;

		}
	}

	void 



}