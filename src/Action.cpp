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

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "..\config.h"
#include "..\headers\Action.h"
#include "..\headers\Protocol.h"

int ACTION (char* msg)
{
	char* action = (char*)malloc(BUFLEN);

	Protocol::Message::Get_Message(msg, action);

	int result = GETACTIONCODE(action);

	free(action);

	return result;
}

int GETACTIONCODE(char* action)
{
	int idx1 = 0;
	int idx2 = strlen(action);

	char* pt = action;

	char _action[BUFLEN];

	int idx;
	
	for (idx = idx1; action[idx] != ' ' && idx < idx2; idx++)
	{
		_action[idx] = action[idx];
	}
	_action[idx] = '\0';

	int result =
		!strcmp(_strupr(_action), "CLOSE")          ? -1 :
		!strcmp(_strupr(_action), "MESSAGE")        ?  0 :
		!strcmp(_strupr(_action), "UPDATE")         ?  1 :
		!strcmp(_strupr(_action), "ADD")            ?  2 :
		!strcmp(_strupr(_action), "SELECT" )        ?  3 :
		!strcmp(_strupr(_action), "DELETE")         ?  4 :
	100;

	return result;
}