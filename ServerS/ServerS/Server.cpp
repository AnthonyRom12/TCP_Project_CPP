#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include "stdafx.h"

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	// �������� ���������� 
	// WSAStartup
	WSAData wsaData;
	// ����������� ������ ���������� winsock:
	WORD DLLVersion = MAKEWORD(2, 1);
	// ������ �������� ������������� ������ ����������, ������ ������ �� ��������� wsaData
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error!" << std::endl;
		exit(1);
	}

	// ��������� ���������� �� ������ ������
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");    // ������ ip �����
	addr.sin_port = htons(1111);                      // ���� ��� ������������� ����������� ������
	addr.sin_family = AF_INET;                        // ��������� ���������� 

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));    // ����������� ������ ������
	listen(sListen, SOMAXCONN);                       // ������������� ����� (�����, ����� ����� ��������)

	// ������� ����� ����� 
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);  // ���������� �������� �� ����� �����

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

