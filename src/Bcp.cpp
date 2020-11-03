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