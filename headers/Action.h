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

#ifndef _ACTION__H
#define _ACTION__H


/*
 * Funcionalidades dos usuarios (actions)
 */
# define CLOSE     -1                     // Fechar programa
# define MESSAGE    0                     // Indica envio de mensagem apenas
# define UPDATE     1                     // Altera o atributo de um registro
# define ADD        2                     // Adiciona um registro da tabela com um nome especificado posteriormente
# define SELECT     3                     // Solicita uma leitura de um registro
# define DELETE     4                     // Deleta um registro de uma tabela

/*
 * SGDB - Funcionalidades novas do Sistema Gerenciador de Banco de Dados
 */
# define CREATE     50                     // Cria tabela/arquivo
# define ALTER      60                     // Altera tabela/arquivo
# define DROP       70                     // Deleta tabela/arquivo

int ACTION        (char* code);
int GETACTIONCODE (char* action);

#endif