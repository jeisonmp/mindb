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