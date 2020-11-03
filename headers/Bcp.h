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

#ifndef _BCP_H__
#define _BCP_H__

#include <WinSock2.h>
typedef struct bcp Bcp;

struct bcp
{
	SOCKET host;            // Especifica o endereco do cliente
	bool  cpu;              // Indica se ganhou a cpu e foi atendido
	char* userName;         // Nome de usuario que realizou a solicitacao
	char* action;           // Acao solicitada pelo usuario
	char* buffer;           // Armazena a mensagem
	char* cor;

	// chegada da mensagem
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
	
	Bcp *left;
	Bcp *right;
};

int  BCP_ADD      (Bcp **, Bcp **, Bcp *);
int  BCP_ADD_FIFO (Bcp **, Bcp **, Bcp **);
bool BCP_KILL     (Bcp **, Bcp **, Bcp *);
bool BCP_COPY     (Bcp *, Bcp *);

#endif
