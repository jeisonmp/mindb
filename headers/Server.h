/*
* Projeto: minDB
* Sistema Gerenciador de Banco de Dados M�nimo
*
* Direitos Autorais Reservados (c) 2016 Max Jeison Prass
*
* Voc� pode obter a �ltima vers�o desse arquivo no GitHub
* localizado em https://bitbucket.org/jeisonmp/mindb
*
* Esta biblioteca � software livre; voc� pode redistribu�-la e/ou modific�-la
* sob os termos da Licen�a P�blica Geral Menor do GNU conforme publicada pela
* Free Software Foundation; tanto a vers�o 2.1 da Licen�a, ou (a seu crit�rio)
* qualquer vers�o posterior.
*
* Esta biblioteca � distribu�da na expectativa de que seja �til, por�m, SEM
* NENHUMA GARANTIA; nem mesmo a garantia impl�cita de COMERCIABILIDADE OU
* ADEQUA��O A UMA FINALIDADE ESPEC�FICA. Consulte a Licen�a P�blica Geral Menor
* do GNU para mais detalhes. (Arquivo LICEN�A.TXT ou LICENSE.TXT)
*
* Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral Menor do GNU junto
* com esta biblioteca; se n�o, escreva para a Free Software Foundation, Inc.,
* no endere�o 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA.
* Voc� tamb�m pode obter uma copia da licen�a em:
* http://www.opensource.org/licenses/lgpl-license.php
*
* Max Jeison Prass, maxjeison@gmail.com
*
*/

#ifndef __SERVER__H
# define __SERVER__H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Bcp.h"
#include "..\headers\SGBD.h"
#include "..\headers\Entity.h"

class Server
{
	SOCKET ClientSocket;
	SOCKET ListenSocket;
	struct addrinfo	*Result;

	public:
		Server ();									// Cosntrutor da classe : Conecta o servidor socket e Inicia os SGBD's.
		HANDLE REQUISICOES;
		
		bool Connect();                             // Estabelece a conexao socket
		bool WaitClient();							// Esperando por cliente
		bool Start();                               // Chama a thread SERVERTHREAD que ira chamar o receive e a thread de REQUISICAO
		bool Recv(); 			                    // Recebe a mensagem
		bool Run(Bcp *bcp);                         // Inicia o SGBD
		bool Request(Bcp *bcp);					    // Entrega a solicitacao ao usuario
		void Stop(addrinfo *result, char* msg);		// Encerra servidor
		void LOG(Bcp *bcp);                         // Imprime mensagem da requisicao

		SGDB   *SGBD;
};

#endif