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