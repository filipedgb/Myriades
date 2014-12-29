
#include <winsock2.h>

#include <stdio.h>
#include <string.h>
#include "Socket.h"

SOCKET m_socket;

bool CtoPlSocket::socketConnect() {// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
	else
		printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return false;
	}
	else
		printf("Client: socket() is OK.\n");

	// Connect to a server.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	// Just test using the localhost, you can try other IP address
	clientService.sin_addr.s_addr = inet_addr(IPADDRESS);
	clientService.sin_port = htons(60070);

	if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		printf("Client: connect() - Failed to connect.\n");
		WSACleanup();
		return false;
	}
	else {
		printf("Client: connect() is OK.\n");
		printf("Client: Can start sending and receiving data...\n");
	}

	// Send and receive data.
	printf("Connected\n");
	return true;
}

void CtoPlSocket::envia(string s1) {
	char *s = new char[s1.length() + 1];
	strcpy_s(s, s1.length()+1, s1.c_str());

	int bytesSent = send(m_socket, s, s1.length(), 0);
	if(bytesSent == SOCKET_ERROR)
		printf("Client: send() error %ld.\n", WSAGetLastError());
}

void CtoPlSocket::recebe(char *ans) {
	int bytesRecv = SOCKET_ERROR;
	int pos = 0;
	while (true) {
		recv(m_socket, &ans[pos], 1, 0);
		if (ans[pos] == '\n')
			break;
		pos++;
	}
	ans[pos] = 0;
	cout << "prolog answered: " << ans << endl;
}

void CtoPlSocket::quit() {
	cout << "Asking prolog to quit\n";
	string s("quit.\n");
	envia(s);
	char ans[128];
	recebe(ans);
}

string CtoPlSocket::addPiece(Board* board, Piece* p, int posX, int posY) {
	string s = "addPiece([";
	s+= p->getColor();
	s.append(",");
	s.append(to_string(p->getNumber()));
	s.append("],");
	s.append(to_string(posX));
	s.append(",");
	s.append(to_string(posY));
	s.append(",");
	s.append(board->toString());
	s.append(").\n");

	envia(s);
	char ans[512];
	recebe(ans);

	return string(ans);
}

string CtoPlSocket::initBoard(int size) {
	if(size > 10) return NULL;

	string s ="initBoard(";
	s.append(to_string(size));
	s.append(").\n");

	envia(s);
	char ans[512];
	recebe(ans);

	return string(ans);
}

string CtoPlSocket::movePiece(Board* board, int posX, int posY, int newPx, int newPy) {
	string s = "movePiece(";
	s.append(to_string(posX));
	s.append(",");
	s.append(to_string(posY));
	s.append(",");
	s.append(to_string(newPx));
	s.append(",");
	s.append(to_string(newPy));
	s.append(",");
	s.append(board->toString());
	s.append(").\n");

	envia(s);
	char ans[512];
	recebe(ans);

	return string(ans);
}