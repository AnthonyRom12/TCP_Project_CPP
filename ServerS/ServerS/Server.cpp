#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include "stdafx.h"

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	// Загрузка библиотеки 
	// WSAStartup
	WSAData wsaData;
	// Запрашиваем версию библиотеки winsock:
	WORD DLLVersion = MAKEWORD(2, 1);
	// Первый аргумент запрашиваемая версия библиотеки, второй ссылка на структура wsaData
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error!" << std::endl;
		exit(1);
	}

	// Заполняем информацию об адресе сокета
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");    // Храним ip адрес
	addr.sin_port = htons(1111);                      // Порт для идентификации поступающих данных
	addr.sin_family = AF_INET;                        // Семейство протоколов 

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));    // Привязываем адресс сокету
	listen(sListen, SOMAXCONN);                       // Прослушивание порта (сокет, максю число запросов)

	// Создаем новый сокет 
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);  // Возвращаем указания на новый сокет

	if (newConnection == 0) {
		std::cout << "Error #2!\n";
	}
	else {
		std::cout << "Client Connected!\n";
		char msg[256] = "Hello from server!";
		send(newConnection, msg, sizeof(msg), NULL);
	}

	system("pause");
	return 0;
}

