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


	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connection to server!\n";
		return 1;
	}
	std::cout << "Connection successfully done!\n";
	char msg[256];
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout << msg << std::endl;


	system("pause");
	return 0;
}