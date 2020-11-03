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
#include <malloc.h>
#include "..\config.h"
#include "..\headers\Protocol.h"
#include "..\headers\Client.h"

#include <iostream>

/*<summer>
 * param 'action' = acao a ser definida
 * param 'msg'    = mensagem da comunicacao TCP
 *
 * Mensagem ex.: <USER>:<ACTION>:<MENSAGEM>
 * A action deve ser uma das definidas em 'Action.h'.
 *</summer>*/
void Protocol::Action::Set_Action(char* msg, const char* action)
{
	int idx1 = 0, idx2 = 0;
	
	char User[BUFLEN];
	char Msg[BUFLEN];

	int i;
	for (i = 0; i < strlen(msg); i++)
	{
		if (msg[i] == ':')
		{
			if (idx1 == 0)
			{
				idx1 = i;
			}
			else
			{
				idx2 = i;
				break;
			}
		}
	}

	for (i = 0; i <= idx1; i++)
	{
		User[i] = msg[i];
	}
	User[idx1+1] = '\0';

	for (i = 0; (idx2 + i) < strlen(msg); i++)
	{
		Msg[i] = msg[idx2 + i];
	}
	Msg[i] = '\0';

	memset(msg, '\0', BUFLEN);

	strcat(msg, User);
	strcat(msg, action);
	strcat(msg, Msg);
	msg[strlen(msg)] = '\0';
}

void Protocol::User::Get_UserName(char* msg, char* user)
{
	int idxUser = Protocol::User::Get_Index(msg);

	sprintf(user, "%s", msg);
	user[idxUser] = '\0';
}

void Protocol::Message::Get_Message(char* msg_rcv, char* msg_return)
{
	int idxMsg = Protocol::Message::Get_Index(msg_rcv);

	for (int i=idxMsg; i <= strlen(msg_rcv); i++)
	{
		msg_return[i - idxMsg] = msg_rcv[i];
	}
	msg_return[strlen(msg_rcv) - idxMsg] = '\0';
}

void Protocol::Action::Get_ActionName(char* msg_rcv, char* action_return)
{
	int idxAction = Protocol::Action::Get_Index(msg_rcv);
	int idxUser = Protocol::User::Get_Index(msg_rcv);

	for (int i=idxUser; i < idxAction-1; i++)
	{
		action_return[i - idxUser] = msg_rcv[i+1];
	}
	action_return[(idxAction-1) - idxUser] = '\0';
}

int Protocol::User::Get_Index(char* msg)
{
	int size = strlen(msg);
	for (int i = 0; i < size; i++)
	{
		if (msg[i] == ':')
		{
			return i;
		}
	}

	return 0;
}
int Protocol::Action::Get_Index(char* msg)
{
	int point = 0;
	int size = strlen(msg);
	for (int i = 0; i < size; i++)
	{
		if (msg[i] == ':')
		{
			if (point < 1)
				point ++;
			else
				return i;
		}
	}

	return 0;
}
int Protocol::Message::Get_Index(char* msg)
{
	int point = 0;
	int size = strlen(msg);
	for (int i = 0; i < size; i++)
	{
		if (msg[i] == ':')
		{
			if (point < 1)
				point ++;
			else
				return i+1;
		}
	}

	return 0;
}