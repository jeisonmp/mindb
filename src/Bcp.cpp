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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "../headers/bcp.h"

/*
 * Adiciona processo.
 */
int BCP_ADD (Bcp **inicio, Bcp **fim, Bcp *bcp)
{
	Bcp *novo;
	novo = bcp;
	
	if (novo)
	{
		if (!strcmp(___stagger, "FIFO"))
		{
			BCP_ADD_FIFO(inicio, fim, &novo);
		}
	}

	return 1;
}

/*
 * Fila
 */
int BCP_ADD_FIFO(Bcp **inicio, Bcp **fim, Bcp **novo)
{
	if (*inicio == NULL)
	{
		*inicio		    = *novo;
		*fim     	    = *novo;
		(*novo)->right	= NULL;
		(*novo)->left   = NULL;
	}
	else
	{
		Bcp *old;

		old = *fim;

		(*fim)->right =  *novo;
		*fim	      =  *novo;
		(*fim)->right =  NULL;
		(*novo)->left =  old;
	}

	return 1;
}

/*<Descricao>
 * Elimita processo da fila de processamento.
 *</Descricao>
 */
bool BCP_KILL (Bcp **BCPI, Bcp **BCPF, Bcp *BCP)
{
	if (BCP == *BCPI)
	{
		if (BCP == *BCPF)
		{
			*BCPI = NULL;
			*BCPF = NULL;
		}
		else
		{
			*BCPI = BCP->right;
			(*BCPI)->left = NULL;
		}
	}
	else if (BCP == *BCPF)
	{
		*BCPF = BCP->left;
		(*BCPF)->right = NULL;
	}
	else
	{
		Bcp *dado = BCP;
		dado->left->right = dado->right;
	}

	return true;
}

bool BCP_COPY(Bcp *requisicao, Bcp *novo)
{
	requisicao->host     = novo->host;
	requisicao->cpu      = novo->cpu;
	requisicao->userName = novo->userName;
	requisicao->action   = novo->action;
	requisicao->buffer   = novo->buffer;

	requisicao->year = novo->year;
	requisicao->mon  = novo->mon;
	requisicao->day  = novo->day;
	requisicao->hour = novo->hour;
	requisicao->min  = novo->min;
	requisicao->sec  = novo->sec;

	return true;
}