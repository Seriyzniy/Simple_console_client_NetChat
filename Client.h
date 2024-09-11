#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <conio.h>
#include <thread>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7770

using namespace std;

class Client
{
	SOCKET connection_socket;
	sockaddr_in server_socket_info;
public:
	Client();
	~Client();

	void Connect(SOCKET connection, sockaddr_in server_socket_info, int size_server_info);
	char* Recv(SOCKET s, int flags);
	int SendToAUTO(SOCKET s, string msg, int flags, sockaddr* dest, int dest_len);

	void ClientHandler(SOCKET s);
	void Start();
};

