#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;

int main() {
	//Create client
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	//Create socket
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is ok!" << endl;
	}

	//Connect to server
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPtonA(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Client: connect() is ok." << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}

	//Send data
	char buffer[200];
	cout << "Please enter a message: ";
	cin.getline(buffer, 200);
	int byteCount = send(clientSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message: " << buffer << endl;
	}
	else {
		WSACleanup();
	}

	//Recieve data
	byteCount = recv(clientSocket, buffer, 200, 0);
	if (byteCount > 0) {
		cout << "Message received: " << buffer << endl;
	}
	else {
		WSACleanup();
	}

	system("pause");
	WSACleanup();
	return 0;

}