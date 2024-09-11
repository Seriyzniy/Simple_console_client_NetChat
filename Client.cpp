#include "Client.h"

Client::Client() {
	//�������� ���������� �������
	server_socket_info.sin_family = AF_INET;
	server_socket_info.sin_addr.s_addr = inet_addr(SERVER_IP);
	server_socket_info.sin_port = htons(SERVER_PORT);

	int size_server_info = sizeof(server_socket_info);

	//�������� ������ ��� �����������
	connection_socket = socket(AF_INET, SOCK_STREAM, 0);
};
Client::~Client() {
	closesocket(connection_socket);
}

void Client::Connect(SOCKET connection_socket, sockaddr_in server_socket_info, int size_server_info) {
	//����������� � �������
	if (connect(connection_socket, (SOCKADDR*)&server_socket_info, size_server_info) == SOCKET_ERROR) {
		cout << "connection_socket error " << WSAGetLastError() << endl;
		closesocket(connection_socket);
		WSACleanup();
		exit(1);
	}
	cout << "Connected to server!" << endl;
}
char* Client::Recv(SOCKET s, int flags) {
	int size_msg = 0;
	int recv_block = 0;
	//�������� ����� ���������
	recv_block = recv(s, (char*)&size_msg, sizeof(int), 0);
	size_msg = atoi((char*)&size_msg);

	//���������� ������ ��� �������� ���������
	char* buff = new char[size_msg + 1];
	buff[size_msg] = '\0';

	//�������� ���������
	recv_block = recv(s, buff, size_msg, flags);
	if (recv_block == SOCKET_ERROR || recv_block == 0) {
		return nullptr;
	}
	return buff;
}
int Client::SendToAUTO(SOCKET s, string msg, int flags, sockaddr* dest, int dest_len) {
	int res;
	int msg_size = msg.size();

	//�������� ����� ���������
	sendto(s, to_string(msg_size).c_str(), sizeof(int), flags, dest, dest_len);
	//�������� ���������
	res = sendto(s, msg.c_str(), msg_size, flags, dest, dest_len);

	if (res == SOCKET_ERROR) {
		cout << "Disconnect client: " << s << endl;
		closesocket(s);
		shutdown(s, 2);
		return res;
	}
	return res;
}
void Client::ClientHandler(SOCKET s) {
	int send_block = 0;
	int get_bates = 0;
	char* buff = new char[256];
	while (true)
	{
		buff = Recv(s, 0);
		if (buff == nullptr || buff == 0) {
			break;
		}
		puts(buff);
	}

}

void Client::Start() {
	cout << "Connected to server?" << endl;
	_getch();

	//����������� � �������
	Connect(connection_socket, server_socket_info, sizeof(server_socket_info));

	//�������� ������ �� ����� ���������
	thread t(&Client::ClientHandler, this, connection_socket);

	//�������� ���������
	string buff = "Client 2";
	int size_buff = 0;

	while (1) {
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << ">>";
		getline(std::cin, buff);
		size_buff = buff.size();
		if (SendToAUTO(connection_socket, buff, 0, 0, 0) == SOCKET_ERROR) {
			break;
		}
	}
	t.detach();
}