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

#ifndef _ENTITY__H_
#define _ENTITY__H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <WinSock2.h>

using std::string;

class Entity
{
	private:
		string table;
		string query;
		
		HANDLE mutex;          // Exclusao mutua para controle de execucao da entidade
		HANDLE mutexQuery;     // Exclusao mutua para controle de alteracao 'query'

	public:
		Entity(string table);

		string getTable();
		string getQuery();
		HANDLE getMutex();           // Retorna o semaforo da entidade.

		void Start(string query);    // Usada para acordar a Entidade e colocar para rodar (controlada por semaforos)
		void Block();                // Bloqueia a entidade (controlada por semaforo)
		void Release();              // Libera para execucao novamente.

		Entity *right;
		Entity *left;
};

int  ENTITY_LOAD (Entity **inicio, Entity **fim, Entity *bcp);
bool ENTITY_KILL (Entity *BCPI, Entity *BCPF, Entity *BCP);


#endif