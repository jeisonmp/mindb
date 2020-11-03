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

#ifndef __DB__H
# define __DB__H

#include <string>

/*<Descricao>
 * Classe SGBD.
 *</Descricao>
 */

#include "..\headers\dirent.h"
#include "..\headers\Entity.h"
#include "..\headers\bcp.h"

class SGDB
{
	private:	
		Entity *ENTITYI;
		Entity *ENTITYF;

	public:
		SGDB();
		
		bool LoadEntities();                                       // Carrega os sgbd's/arquivos/tabelas do banco de dados.
		bool RequisitionQuery(Bcp **bcp);                          // Recebe a query recebida pelo servidor.
		bool Query(string query);                                  // Realiza o tratamento da mensagem.

		Entity* EntityFindByTable (string table);                  // Metodo de pesquisa para tratamento da Entidade solicitada.
};

#endif