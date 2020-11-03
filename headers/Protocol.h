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

#ifndef _PROTOCOL__H
# define _PROTOCOL__H

#include "Client.h"

static class Protocol
{
	public:
		/*
		 * Firula para mostrar como pode ser organizada OO em C++.
		 */
		static class User
		{
			public:
				static int Get_Index(char* msg);
				static void Get_UserName(char* msg_entrada, char* user);
		};

		static class Action
		{
			public:
				static int Get_Index(char* msg);
				static void Get_ActionName(char* msg_entrada, char* action);
				static void Set_Action(char* msg, const char* action);
		};

		static class Message
		{
			public:
				static int Get_Index(char* msg);
				static void Get_Message(char* msg_entrada, char* msg);

		};
};
	
#endif