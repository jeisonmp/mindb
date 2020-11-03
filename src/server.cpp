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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <regex>
#include "..\config.h"
#include "..\headers\Server.h"
#include "..\headers\Protocol.h"
#include "..\headers\Bcp.h"
#include "..\headers\Thread.h"
#include "..\headers\Action.h"
#include "..\headers\SGBD.h"
#include "..\headers\entity.h"
#include "..\headers\requisition.h"

#pragma deprecated

//Armazena ponteiro inicial da lista de processos
Bcp *BCPI = NULL;
//Armazena ponteiro final da lista de processos
Bcp *BCPF = NULL;

Server::Server()
{
	ClientSocket = INVALID_SOCKET;
	ListenSocket = INVALID_SOCKET;
	struct addrinfo	*Result = NULL;
}

bool Server::Recv()
{
	if (DEBUG)
	{
		printf("Wait for a message... ");
	}

	char recvbuf[BUFLEN];
	int iResult;
	char* user = (char*)malloc(sizeof(recvbuf));
	char* msg = (char*)malloc(sizeof(recvbuf));
	char* action = (char*)malloc(sizeof(recvbuf));

	iResult = recv(ClientSocket, recvbuf, BUFLEN, 0);

	if (iResult > 0)
	{

	#pragma region // (...) TRECHO DE CODIGO RECEIVED

		if (DEBUG)
		{
			printf("(OK)\n");
		}

		char rcvMsg[BUFLEN];
		strncpy_s(rcvMsg, recvbuf, iResult);

		Protocol::User::Get_UserName(rcvMsg, user);
		Protocol::Message::Get_Message(rcvMsg, msg);
		Protocol::Action::Get_ActionName(rcvMsg, action);

		time_t rawtime;
		struct tm * timeinfo = (tm*)malloc(sizeof(tm));
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		/***********************************************************************************
		* ADICIONANDO MENSAGEM ************************************************************
		***********************************************************************************/
		Bcp *dado;
		dado = (Bcp *)malloc(sizeof(Bcp));

		dado->host     = ClientSocket;
		dado->cpu      = false;
		dado->userName = user;
		dado->buffer   = msg;
		dado->action   = action;
		dado->hour     = timeinfo->tm_hour;
		dado->min      = timeinfo->tm_min;
		dado->sec      = timeinfo->tm_sec;
		dado->year     = timeinfo->tm_year;
		dado->mon      = timeinfo->tm_mon;
		dado->day      = timeinfo->tm_mday;

		BCP_ADD(&BCPI, &BCPF, dado);

		#pragma endregion

		REQUISITIONTHREAD *t = new REQUISITIONTHREAD(*this, dado);
	}
	else if (iResult == 0)
	{
		if (DEBUG)
		{
			this->Stop(NULL, "\nA client connection was closed.");
		}
		//return false;
	}
	else
	{
		if (DEBUG)
		{
			char iRes[BUFLEN] = "\nA client received failed: ";
			sprintf_s(iRes, "%s%d", iRes, WSAGetLastError());

			this->Stop(NULL, iRes);
		}
		//return false;
	}

	return true;
}

// Recebe as mensagens (BCP) e repassa ao SGBD.
bool Server::Run(Bcp *bcp)
{
	this->SGBD->RequisitionQuery(&bcp);

	// Imprime o log da requisicao.
	this->LOG(bcp);

	// Envia acknowledgment
	this->Request(bcp);

	return true;
}

bool Server::Request(Bcp *bcp)
{
	int iResult = send(bcp->host, bcp->buffer, strlen(bcp->buffer), 0);

	if (iResult == SOCKET_ERROR)
	{
		if (DEBUG)
		{
			char iRes[BUFLEN] = "send failed: ";
			sprintf_s(iRes,"%s%d", iRes, WSAGetLastError());

			this->Stop(NULL, iRes);
		}
		//return false;
	}

	if (DEBUG)
	{
		printf("Acknowledgement... Bytes sent: %ld. (OK)...\n", iResult);
	}

	return true;
}

bool Server::Start()
{
	this->Connect();
	this->SGBD = new SGDB();

	return true;
}

bool Server::Connect()
{
	WaitForSingleObject(this->REQUISICOES, INFINITE);

	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		system("pause");
		return false;
	}
	printf("starting...\n");

	struct addrinfo	hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;		    // Internet address family is unspecified so that either an IPv6 or IPv4 address can be returned
	hints.ai_socktype = SOCK_STREAM;	// Requests the socket type to be a stream socket for the TCP protocol
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, PORT, &hints, &this->Result);
	if (iResult != 0)
	{
		char iRes[BUFLEN] = "\ngetaddrinfo failed: ";
		sprintf_s(iRes, "%s%c", iRes, iResult);

		this->Stop(this->Result, iRes);

		return false;
	}
	printf("server address and port info. (OK)...\n");

	// Create a SOCKET for the server to listen for client connections
	ListenSocket = socket(this->Result->ai_family, this->Result->ai_socktype, this->Result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET)
	{
		char iRes[BUFLEN] = "\nError at socket(): ";
		sprintf_s(iRes, "%s%c", iRes, WSAGetLastError());

		this->Stop(this->Result, iRes);
		return false;
	}
	printf("create socket. (OK)...\n");

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, this->Result->ai_addr, (int)this->Result->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		char iRes[BUFLEN] = "\nbind failed: ";
		sprintf_s(iRes, "%s%c", iRes, WSAGetLastError());

		this->Stop(this->Result, iRes);
		return false;
	}
	printf("bind (OK)...\n");

	// To listen on a socket
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		char iRes[BUFLEN] = "\nlisten failed: ";
		sprintf_s(iRes, "%s%c", iRes, WSAGetLastError());

		this->Stop(this->Result, iRes);
		return false;
	}
	printf("listen (OK)...\n");
	printf("Server started! (OK)\n\n");
	
	ReleaseSemaphore(this->REQUISICOES, 1, NULL);
}

bool Server::WaitClient()
{
	if (DEBUG)
	{
		printf("\nWait for a client... ");
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);

	if (ClientSocket == INVALID_SOCKET)
	{
		char iRes[BUFLEN] = "\naccept failed: ";
		sprintf_s(iRes, "%s%c", iRes, WSAGetLastError());

		this->Stop(this->Result, iRes);
		return false;
	}

	if (DEBUG)
	{
		printf("(OK)\n");
	}

	return true;
}

void Server::Stop(addrinfo *result, char* msg)
{
	std::cout << msg;

	if (result != NULL)
	{
		freeaddrinfo(result);
	}
	closesocket(ListenSocket);
	WSACleanup();

	system("pause");
}

void Server::LOG(Bcp *bcp)
{
	printf("Request: %.2d/%.2d/%.2d %.2d:%.2d:%.2d HOST:%.4d USER:%.8s ACTION:%s\n", bcp->day, bcp->mon, bcp->year,
		bcp->hour, bcp->min, bcp->sec, bcp->host, bcp->userName, bcp->action);
}
