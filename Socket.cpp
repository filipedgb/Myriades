#include "Socket.h"

#include <winsock2.h>

#include <stdio.h>
#include <string.h>
#include "Piece.h" 

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

void CtoPlSocket::envia(char *s, int len) {
	int bytesSent = send(m_socket, s, len, 0);
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
	char buff[] = "quit.\n";
	envia(buff, 6);
	char ans[128];
	recebe(ans);
}


vector<vector<Piece*>> boardParser(string answer) {
	vector<vector<Piece*>> board;
	vector<Piece*> row;

	answer.erase(0,1); // erase first '['
	answer.erase(answer.size()-3,answer.size()-3); // erase last '].\r'

	int posEnd, posBegin;

	
	while(answer != "") {
		if(answer[0] == ',')
			answer.erase(0,1);
		if(answer.find("[[") == 0)
			answer.erase(0,1); // erase row '['

		posEnd = answer.find("]");
		if(posEnd != 0) {
			if(posEnd != 1) {
				string cell = answer.substr(1,posEnd-1);

				char color = cell[0];
				int number = (int) atoi(cell.substr(cell.find(",") + 1, cell.size()-2).c_str());

				row.push_back(new Piece(number, color));
			}
			else row.push_back(NULL); //empty cell
		}
		else { //end of row
			board.push_back(row);
			row.clear();
		}
		answer.erase(0,posEnd+1);
	}

	return board;
}

void printBoard(vector<vector<Piece*>> b) {
	for (int i = 0; i < b.size(); i++) {
		printf("%d\n",i);
		
		for (int j = 0; j < b[i].size(); j++) {
			if(b[i][j]!=NULL)
				printf("%d, %c - %d \t",j, b[i][j]->getColor(), b[i][j]->getNumber());
			else printf("NULL");
		}
		printf("\n");
	}
}

int CtoPlSocket::loop() {
	socketConnect();
	//char *s = "comando(1, 2).\n";
	char *s = "comando(5,'b').\n";
	envia(s, strlen(s));
	char ans[256];
	recebe(ans);

	string str(ans);

	printf("\n size %d\n",str.size());
	quit();
	printBoard(boardParser(str));
	getchar();
	return 0;
}