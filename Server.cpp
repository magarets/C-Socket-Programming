#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

#define PORT 33481
#define SERVER_IP "169.254.89.105"
#define PACKET_SIZE 1024

int main() {

	DWORD dwTaskProcess = 0;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen; // 소켓 핸들 생성
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 캡쳐

	SOCKADDR_IN tListenAddr = {}; // 소켓의 구성요소를 담을 구조체 생성
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT); // PORT
	tListenAddr.sin_addr.s_addr = htons(INADDR_ANY); // IP Address

	/* 소켓에 설정한 주소정보를 묶고, 소켓을 접속대기상태로 만듦*/
	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr)); // 소켓에 주소정보를 연결
	listen(hListen, SOMAXCONN); // 접속승인

	/* 동기화 방식으로 동작, 동기화 : 요청을 마무리 하기 전까지 계속 대기 상태 */
	SOCKADDR_IN tCIntAddr = {}; // 클라이언트 측 소켓 생성 및 정보를 담을 구조체 생성 및 값 할당
	int iCIntSize = sizeof(tCIntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tCIntAddr, &iCIntSize); // 클라이언트가 접속 요청 시 승인

	char cBuffer[PACKET_SIZE] = {};
	recv(hClient, cBuffer, PACKET_SIZE, 0);
	printf("Recv Msg : %s\n", cBuffer);

	char cMsg[] = "hi";
	send(hClient, cMsg, strlen(cMsg), 0);

	closesocket(hClient);
	closesocket(hListen);

	WSACleanup();
	return 0;
}
