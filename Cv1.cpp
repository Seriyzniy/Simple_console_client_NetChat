#include "Client.h"

int main()
{
	//Инициализация библиотеки
	WSAData wsa;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (result != 0) {
		cout << "WSA error!" << endl;
		exit(1);
	}
	Client c1;
	c1.Start();
	//Принятие сообщений
	
}
