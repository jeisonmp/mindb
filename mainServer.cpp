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

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <iostream>
#include "config.h"
#include "headers\Thread.h"
#include "headers\Server.h"
#include "headers\Bcp.h"
#include "headers\SGBD.h"
#include "headers\Requisition.h"

//A directiva pragma � usado para acessar as extens�es de pr�-processamento espec�ficas do compilador.
//Um uso comum do #pragma � o #pragma once directiva, que pede o compilador para incluir um arquivo de cabe�alho apenas uma �nica vez, n�o importa quantas vezes ele foi importado.
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class SERVERTHREAD: public Thread
{
	Server server;

    public:
		SERVERTHREAD(Server server)
		{
			this->server = server;
			Thread::CreateNewThread(this);
		}

	void Run(void*)
	{
		if (!this->server.Recv())
		{
			return;
		}
		else
		{

		}
	}
};

int main()
{
	/*
	 * Inicia servidor
	 */
	Server server;

	/*
	 * Inicia servidor
	 */
	if (!server.Start())
	{
		return 1;
	}

	while (true)
	{
		/*
		 * Aguarda entrada de usuario e abre a thread para atende-la.
		 */
		if (!server.WaitClient())
		{
			//return 1; //fecha conex�o
		}
		else
		{
			SERVERTHREAD *t = new SERVERTHREAD(server);
		}
	}

	server.Stop(NULL, "closed.");
	system("pause");

	return 1;
}