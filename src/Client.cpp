/*
* Projeto: minDB
* Sistema Gerenciador de Banco de Dados Mínimo
*
* Direitos Autorais Reservados (c) 2016 Max Jeison Prass
*
* Você pode obter a última versão desse arquivo no GitHub
* localizado em https://bitbucket.org/jeisonmp/mindb
*
* Esta biblioteca é software livre; você pode redistribuí-la e/ou modificá-la
* sob os termos da Licença Pública Geral Menor do GNU conforme publicada pela
* Free Software Foundation; tanto a versão 2.1 da Licença, ou (a seu critério)
* qualquer versão posterior.
*
* Esta biblioteca é distribuída na expectativa de que seja útil, porém, SEM
* NENHUMA GARANTIA; nem mesmo a garantia implícita de COMERCIABILIDADE OU
* ADEQUAÇÃO A UMA FINALIDADE ESPECÍFICA. Consulte a Licença Pública Geral Menor
* do GNU para mais detalhes. (Arquivo LICENÇA.TXT ou LICENSE.TXT)
*
* Você deve ter recebido uma cópia da Licença Pública Geral Menor do GNU junto
* com esta biblioteca; se não, escreva para a Free Software Foundation, Inc.,
* no endereço 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA.
* Você também pode obter uma copia da licença em:
* http://www.opensource.org/licenses/lgpl-license.php
*
* Max Jeison Prass, maxjeison@gmail.com
*
*/

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include "..\config.h"
#include "..\headers\Client.h"
#include "..\headers\Action.h"
#include "..\headers\Protocol.h"
#include "time.h"

Client::Client()
{
	std::cout << "Enter your login: ";
	scanf("%s", &this->Username);
	fflush(stdin);
	std::cout << "\n\n";
	
	if (!this->Start())
	{
		return;
	}

	#ifndef SERVER
		std::cout << "Enter your IP SERVER: ";
		scanf_s("%s", &ServerName);
	#else
		ServerName = SERVER;
	#endif

	ConnectSocket = INVALID_SOCKET;
}

bool Client::Start()
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		system("pause");
		return false;
	}

	return true;
}

bool Client::Connect()
{
	struct addrinfo	*result = NULL,
					*ptr = NULL,
					hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		
	hints.ai_socktype = SOCK_STREAM;	
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	int iResult = getaddrinfo(ServerName, PORT, &hints, &result);
	if (iResult != 0)
	{
		if (DEBUG)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			system("pause");
			WSACleanup();
		}
		else
		{
			printf("Servidor off!...\n");
		}
		
		return false;
	}

	ptr = result;

	clock_t tini, tfim;
	tini = clock();
	float time = 0;

	do
	{
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET)
		{
			if (DEBUG)
			{
				printf("Error at socket(): %d\n", WSAGetLastError());
				system("pause");
				freeaddrinfo(result);
				WSACleanup();
			
				return false;
			}
		}

		// Connect to server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		}

		tfim = clock();
		time = (tfim - tini)/1000.F;

	} while (ConnectSocket == INVALID_SOCKET && time < 5 );


	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Servidor off!...\n");
		return false;
	}

	return true;
}

// Free the resouces
void Client::Stop()
{
	int iResult = shutdown(ConnectSocket, SD_SEND);

	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
	}

	closesocket(ConnectSocket);
	WSACleanup();
};

// Send message to server
bool Client::Send(char* sndMsg)
{
	do
	{
		int iResult = send(ConnectSocket, sndMsg, strlen(sndMsg), 0);

		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			system("pause");
			Stop();
			return false;
		}

	} while (!this->Recv());

	return true;
}

// Receive message from server
bool Client::Recv()
{
	char recvbuf[BUFLEN];
	int iResult = recv(ConnectSocket, recvbuf, BUFLEN, 0);

	char msg[BUFLEN];
	strncpy_s(msg, recvbuf, iResult);

	if (iResult > 0)
	{
		if (GETACTIONCODE(msg) != MESSAGE)
		{
			printf("%s\n", msg);
		}
		else if (DEBUG)
		{
			printf("Acknowledgement... Bytes received: %d. (OK)\n", iResult);
		}
	}
    else if (iResult == 0)
	{
        printf("Connection closed\n");
		return false;
	}
    else
	{
        printf("recv failed with error: %d\n", WSAGetLastError());
		return false;
	}

	return true;
}

bool Client::Run()
{
	switch (ACTION(this->Message))
	{
		case UPDATE:
			Protocol::Action::Set_Action(this->Protocol, "UPDATE");
			break;

		case ADD:
			Protocol::Action::Set_Action(this->Protocol, "ADD");
			break;

		case DELETE:
			Protocol::Action::Set_Action(this->Protocol, "DELETE");
			break;

		case SELECT:
			Protocol::Action::Set_Action(this->Protocol, "SELECT");
			break;

		case CLOSE:
			this->Stop();
			return false;

		default:
			Protocol::Action::Set_Action(this->Protocol, "MESSAGE");
	}

	this->Send(this->Protocol);

	return true;
}