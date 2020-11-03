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