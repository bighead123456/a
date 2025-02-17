// hello_server_win.cpp : 定义控制台应用程序的入口点。
//




#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA	wsaData;
	SOCKET hServSock, hClntSock;		
	SOCKADDR_IN servAddr, clntAddr;		

	int szClntAddr;
	char message[]="Hello World!"；

	if(argc!=3) 
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 

	hServSock=socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi(argv[1]));

	if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("bind() error");  

	if(listen(hServSock, 5)==SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr=sizeof(clntAddr);    	
	
	if(hClntSock==INVALID_SOCKET)
		ErrorHandling("accept() error");  

	send(hServSock, message, sizeof(message), 0);
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void Errorhandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
