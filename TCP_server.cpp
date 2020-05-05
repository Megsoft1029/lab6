#include <stdio.h>
#include <stdio.h>
#include <winsock2.h>
#include "file.h"
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	file fh;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[BUFSIZ];
	while (true)
	{
		printf("Waiting for connection\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("Received a connection£º%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		int ret = 0;
		long long count = 0;
		char sendData[BUFSIZ] = "welcome TCP_client£¡\n";
		ret = recv(sClient, revData, BUFSIZ, 0);
		char fromname[BUFSIZ] = {};
		strcpy(fromname, revData);
		char mid[3] = "\\";
		char finame[MAX_PATH] = {};
		char over[BUFSIZ] = "Finnal";
		strcat(finame, inet_ntoa(remoteAddr.sin_addr));
		printf(finame);
		strcat(finame, mid);
		strcat(finame, revData);
		FILE *f = fh.createFile(finame);
		send(sClient, sendData, BUFSIZ, 0);
		while ((ret = recv(sClient, revData, BUFSIZ, 0)) > 0)
		{
			printf("%db\n", count += ret);
			if (strcmp(revData, over) == 0)
			{
				printf("file %s transmission success\n", fromname);
				break;
				send(sClient, over, BUFSIZ, 0);
			}
			fwrite(revData, 1, ret, f);
			send(sClient, sendData, BUFSIZ, 0);
		}
		fclose(f);
		if (strcmp(revData, over) != 0)
		{
			printf("IP£º%s sends %s loss connecton during transmission\n", inet_ntoa(remoteAddr.sin_addr), fromname);
			remove(finame);
		}


		closesocket(sClient);
	}

	closesocket(slisten);
	WSACleanup();
	return 0;
}