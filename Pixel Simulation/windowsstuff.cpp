#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "windowsstuff.h"
#include <string>
namespace GibWindows
{
	struct HiddenClient
	{
		sockaddr_in client_sockaddr;
	};

	void Test() {
		std::cout << "Test Run!" << std::endl;
	}


	void InitServer(int& serverSocket, std::string port)
	{
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "Winsock initialization failed" << std::endl;
			return;
		}

		serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if (serverSocket == -1)
		{
			std::cerr << "Error creating socket" << std::endl;
			CloseSocketAndCleanup(serverSocket);
			return;
		}

		int new_port = std::stoi(port);

		struct sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(new_port);
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		{
			std::cerr << "Error binding socket!" << std::endl;
			CloseSocketAndCleanup(serverSocket);
			return;
		}
	}

	void InitClient(int& clientSocket)
	{
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			std::cerr << "Winsock initialization failed" << std::endl;
			return;
		}

		clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if (clientSocket == -1)
		{
			std::cerr << "Error creating socket" << std::endl;
			CloseSocketAndCleanup(clientSocket);
			return;
		}
	}

	void CloseSocketAndCleanup(int socket)
	{
		closesocket(socket);
		WSACleanup();
	}

	void SendDataToClient(int serverSocket, Client client, char* data, uint32_t sizeOfData)
	{
		int slen = sizeof(sockaddr_in);
		if (sendto(serverSocket, data, sizeOfData, 0, (sockaddr*)client.client, slen) == SOCKET_ERROR)
		{
			std::cout << "sendto error. Error code: " << WSAGetLastError() << std::endl;
		}
		else
		{
			std::cout << "data sent" << std::endl;
		}
	}

	bool ReceiveData(int socket, char* data, uint32_t sizeOfData)
	{
		sockaddr_in sender;
		int slen = sizeof(sockaddr_in);
		if (recvfrom(socket, data, sizeOfData, 0, (struct sockaddr*)&sender, &slen) == SOCKET_ERROR)
		{
			std::cout << "Recvfrom error. Error code: " << WSAGetLastError() << std::endl;
			return false;
		}
		else
		{
			
			std::cout << "Data receieved" << std::endl;
			return true;
		}
		return false;
	}

	void SendData(int socket, char* data, uint32_t sizeOfData, std::string ip, std::string port)
	{
		int slen = sizeof(sockaddr_in);
		sockaddr_in server;

		memset((char*)&server, 0, sizeof(server));
		

		int new_port = std::stoi(port);
		// Set server info that has been specified in the arguments supplied to the program
		server.sin_family = AF_INET;
		server.sin_port = htons(new_port);
		//_server.sin_addr.s_addr = inet_addr(ip.c_str());
		inet_pton(AF_INET, (ip.c_str()), &server.sin_addr.s_addr);

		sendto(socket, data, sizeOfData, 0, (struct sockaddr*)&server, slen);
	}

	void JoinServerClients(int socket, std::string ip, std::string port)
	{
		char* data = new char;
		*data = true;

		SendData(socket, data, sizeof(char), ip, port);
		std::cout << "Server join sent" << std::endl;
	}

	void ClientAcceptThread(int serverSocket, std::vector<Client>& clients, std::mutex& mutex, bool& threadRunning)
	{
		int slen = sizeof(sockaddr_in);
		while (threadRunning)
		{
			sockaddr_in newClient;
			char sentByte;
			if (recvfrom(serverSocket, &sentByte, sizeof(bool), 0, (sockaddr*)&newClient, &slen))
			{
				std::cout << "Client accepted" << std::endl;
				Client client;
				HiddenClient* hidClient = new HiddenClient;
				hidClient->client_sockaddr = newClient;
				client.client = hidClient;
				client.clientAddr = newClient.sin_addr.S_un.S_addr;
				client.clientPort = newClient.sin_port;
				client.clientSocket = 0;
				mutex.lock();
				clients.push_back(client);
				mutex.unlock();
			}
			
		}
	}

	void SetSocketToNonBlocking(int socket)
	{
		unsigned long int noBlock = 1;
		ioctlsocket(socket, FIONBIO, &noBlock);
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

	



}