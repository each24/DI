// RGZ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include <thread>
#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;
void client(string str) {
	char SERVERADDR[4];
	char buff[10 * 1014];

	printf("UDP Client Started\n");

	// Инициализация WinSock
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("WSAStartup error: %d\n", WSAGetLastError());
	}


	// Открытие и закрытие сокета
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET)
	{
		printf("socket() error: %d\n", WSAGetLastError());
		WSACleanup();
	}

	printf("Enter Server IP: ");
	
	getc(SERVERADDR);

	// Шаг 3 - обмен сообщений с сервером
	HOSTENT *hostent;
	sockaddr_in dest_addr;

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(5150);


	// определение IP-адреса узла
	if (inet_addr(SERVERADDR))
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
		if (hostent = gethostbyname(SERVERADDR))
			dest_addr.sin_addr.s_addr = ((unsigned long **)
				hostent->h_addr_list)[0][0];
		else
		{
			printf("Unknown host: %d\n", WSAGetLastError());
			closesocket(my_sock);
			WSACleanup();
			return;
			//return -1;
		}

	while (1)
	{
		// чтение сообщения с клавиатуры
		printf("C=>S:"); fgets(&buff[0], sizeof(buff) - 1, stdin);
		if (!strcmp(&buff[0], "quit\n")) break;

		// Передача сообщений на сервер
		sendto(my_sock, &buff[0], strlen(&buff[0]), 0, (sockaddr *)&dest_addr, sizeof(dest_addr));

		// Прием сообщения с сервера
		sockaddr_in server_addr;
		int server_addr_size = sizeof(server_addr);

		int n = recvfrom(my_sock, &buff[0], sizeof(buff) - 1, 0, (sockaddr *)&server_addr, &server_addr_size);

		if (n == SOCKET_ERROR)
		{
			printf("recvfrom() error:"\
				"%d\n", WSAGetLastError());
			closesocket(my_sock);
			WSACleanup();
			return;
			//return -1;
		}

		buff[n] = 0;

		// Вывод принятого с сервера сообщения на экран
		printf("S=>C:%s", &buff[0]);
	}

	// шаг последний - выход
	closesocket(my_sock);
	WSACleanup();

	return;
}

int main()
{
	thread Cl(client, "123");
	Cl.join();
	char buff[1024];
	printf("UDP Server Started\n");
	// Инициализация WinSock
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("WSAStartup error: %d\n", WSAGetLastError());
	}
	else printf("WinSock intializing\n");

	// Открытие и закрытие сокета
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET)
	{
		printf("Socket error: %d\n", WSAGetLastError());
		WSACleanup();
	}

	// Связывание сокета 
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(5150);

	if (_WINSOCK2API_::bind(my_sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error: %d\n", WSAGetLastError());
		closesocket(my_sock);
	}

	// Обработка присланных пактов
	while (1)
	{
		sockaddr_in client_addr;
		int client_addr_size = sizeof(client_addr);
		int bsize = recvfrom(my_sock, &buff[0], sizeof(buff) - 1, 0, (sockaddr *)&client_addr, &client_addr_size);
		if (bsize == SOCKET_ERROR)
			printf("recvfrom() error: %d\n", WSAGetLastError());
		// Определяем IP-адрес клиента и прочие атрибуты
		HOSTENT *hostent;
		hostent = gethostbyaddr((char *)&client_addr.sin_addr, 4, AF_INET);
		printf("accepted connection from %s, port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		// Добавление завершающего нуля
		buff[bsize] = 0;

		// Вывод на экран 
		printf("C=>S:%s\n", &buff[0]);

		// посылка датаграммы клиенту
		sendto(my_sock, &buff[0], bsize, 0,
			(sockaddr *)&client_addr, sizeof(client_addr));

	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
