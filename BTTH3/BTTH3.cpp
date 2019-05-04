// BTTH3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "winsock2.h"

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8080);

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	while (true)
	{
		SOCKET client = accept(listener, NULL, NULL);

		// Nhan lenh gui tu client
		char buf[1024];
		int ret = recv(client, buf, sizeof(buf), 0);

		buf[ret] = 0;
		printf(buf);

		if (strncmp(buf, "GET / ", 6) == 0)
		{
			char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>";
			char msg[2056] = "";
			int offset = 0;
			sprintf(msg, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>");
			//sprintf(msg + strlen(msg), "HELLO<br>WORLD!");
			WIN32_FIND_DATAA DATA;
			HANDLE h = FindFirstFileA("C:\\*.*", &DATA);
			do {
				if (DATA.dwFileAttributes &
					FILE_ATTRIBUTE_DIRECTORY) {
					// Đây là một thư mục
					// In ra tên thư mục
					char link[] = "";
					//sprintf(link, "C:\\%s\\", DATA.cFileName);
					sprintf(msg + strlen(msg), "<br><i><a href = \"C:\\netcat - 1.11\">%s</a></i><br>", DATA.cFileName);
					//system("PAUSE");
				}
				else {
					char tmp[] = "";
					//int offset =  0;
					unsigned long size = (DATA.nFileSizeHigh*(MAXDWORD + 1)) + DATA.nFileSizeLow;
					sprintf(msg + strlen(msg), "<br><i><a href = \"D:\\netcat - 1.11\\Out.txt\"\">%s : %ul</a></i><br>", DATA.cFileName, size);
				}
			} while (FindNextFileA(h, &DATA));
			sprintf(msg + strlen(msg), "</body></html>");
			printf(msg);
			send(client, msg, strlen(msg), 0);
		}
		else
		{
			// Tra ve du lieu text html
			char msg[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Yeu cau khong duoc ho tro</body></html>";
			send(client, msg, strlen(msg), 0);
		}

		closesocket(client);
	}


	WSACleanup();
	system("PAUSE");

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
