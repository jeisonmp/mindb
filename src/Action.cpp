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