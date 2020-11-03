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
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "config.h"                 // Define palavras reservadas de utilizacao
#include "headers\Client.h"			// Define a comunicação TCP do cliente
#include "headers\Server.h"         // Define a comunicação TCP do servidor
#include "headers\Protocol.h"       // Protocolo da camada de transporte
#include "headers\Action.h"         // Define as interacoes dos usuarios com o servidor

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	bool timer = 0;

	Client *client = new Client();

	int i = 0;

	if (timer)
		i = 0;

	if (timer)
	{
		printf("%s: ", client->Username);
		scanf("%s", &client->Message);
	}

	while(true)
	{
		memset(client->Protocol, '\0', BUFLEN);
		printf("%s: ", client->Username);
		
		if (!timer)
		{
			//verificar que nao conseguindo capturar string que contenham espacos aqui, com gets funciona, porem esta obsoleto no VS2015
			//gets(client->Message);
			fgets(client->Message, 5, stdin);
		}

		fflush(stdin);

		if (!strcmp(client->Message,"clear"))
		{
			system("cls");
		}
		else
		{
			sprintf(client->Protocol, "%s%s%s", client->Username, ":ACTION:", client->Message);

			if (client->Connect())
			{
				if (!client->Run())
				{
					return 0;
				}
			}
		}

		if (timer) 
			i++;

		if (timer) 
			if (i > 10000)
			{
				Sleep(10000);
				i = 0;
			}
	}
	
	system("pause");
	return 1;
}