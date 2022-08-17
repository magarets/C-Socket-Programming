#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

#define PORT 65
#define PACKET_SIZE 1024
#define SERVER_IP "server_ip"

#define _WINSOCK_DEPRECATED_NO_WARNINGS


int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &(tAddr.sin_addr));

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	char cMsg[] = "Seong Yoo won";
	send(hSocket, cMsg, strlen(cMsg), 0);

	char cBuffer[PACKET_SIZE] = {};
	recv(hSocket, cBuffer, PACKET_SIZE, 0);

	printf("Recv Msg: %s\n", cBuffer);

	closesocket
	(hSocket);

	WSACleanup();
}
