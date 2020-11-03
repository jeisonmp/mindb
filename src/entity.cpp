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
#include <string>
#include <iostream>
#include "../config.h"
#include "../headers/Entity.h"

Entity::Entity(string table)
{
	// Salva nome da entidade;
	this->table = table;

	// Cria SEMAFORO para controle de execucao. A primeira execucao aguarda o metodo "Start", iniciada pelo servidor.
	this->mutex = CreateSemaphore(NULL, 0, 1, (LPCSTR)(table.c_str()));

	// Cria SEMAFORO para controle de alteracao da Query. Deixa a primeira alteracao livre.
	string mutexquery(table + "Q");
	this->mutexQuery = CreateSemaphore(NULL, 1, 1, (LPCSTR)(mutexquery.c_str()));
}

string Entity::getTable()
{
	return this->table;
}

HANDLE Entity::getMutex()
{
	return this->mutex;
}

string Entity::getQuery()
{
	return this->query;
}

/*
 * Inicializacao:
 *		Bloqueia alteracoes e coloca para rodar.
 */
void Entity::Start(string query)
{
	WaitForSingleObject(this->mutexQuery, INFINITE);
	
	this->query = query;
	
	ReleaseSemaphore(this->mutex, 1, NULL);
}

// Bloqueia a execucao
void Entity::Block()
{
	WaitForSingleObject(this->mutex, INFINITE);
}

// Liberando para novas atualizacoes
void Entity::Release()
{
	ReleaseSemaphore(this->mutexQuery, 1, NULL);
}

/*
 * Fila
 */
int ENTITY_ADD_FIFO(Entity **inicio, Entity **fim, Entity **novo)
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
		Entity *old;

		old = *fim;

		(*fim)->right =  *novo;
		*fim	      =  *novo;
		(*fim)->right =  NULL;
		(*novo)->left =  old;
	}

	return 1;
}

/*
 * Adiciona processo.
 */
int ENTITY_LOAD (Entity **inicio, Entity **fim, Entity *bcp)
{
	Entity *novo;
	novo = bcp;
	
	if (novo)
	{
		if (!strcmp(___stagger, "FIFO"))
		{
			ENTITY_ADD_FIFO(inicio, fim, &novo);
		}
	}

	return 1;
}

/*<Descricao>
 * Elimita processo da fila de processamento.
 *</Descricao>
 */
bool ENTITY_KILL (Entity *BCPI, Entity *BCPF, Entity *BCP)
{
	if (BCP == BCPI)
	{
		if (BCP == BCPF)
		{
			BCPI = NULL;
			BCPF = NULL;
		}
		else
		{
			BCPI = BCP->right;
		}
	}
	else if (BCP == BCPF)
	{
		BCPF = BCP->left;
	}
	else
	{
		Entity *dado = BCP;
		dado->left->right = dado->right;
	}

	return true;
}