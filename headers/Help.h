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

#ifndef _HELP__H
# define _HELP__H

#include<iostream>
#include<string>

using std::string;

//std::regex _add("(ADD|add)([\040]+)(VALUE|value)(([\040]+)(MODELO|modelo)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(ANO|ano)([\040]*)(=)([\040]*)([0-9]+))?(([\040]+)(COR|cor)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(CHASSI|chassi)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(PROPRIETARIO|proprietario)([\040]*)(=)([\040]*)([A-Za-z]+))?([\040]*)");
//std::regex _add2("(ADD|add)([\040]*)");
//std::regex _adderror("([ADD|add])([\040]+)([^.])");
//std::regex _select("(SELECT|select)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})");
//std::regex _selectall("(SELECT|select)([\040]+)(ALL|all)([\040]*)");
//std::regex _delete("(DELETE|delete)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})");
//std::regex _update("(UPDATE|update)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})([\040]+)(VALUE|value)([\040]+)(MODELO|modelo|ANO|ano|COR|cor|CHASSI|chassi|PROPRIETARIO|proprietario)([\040]*)(=)([\040]*)([A-Za-z]+)");
//	

string HELP = 
	string(">>Digite HELP <NAME>:\n") +
	string(">>>>'HELP QUERY'      : Obtem a lista de querys.\n") +
	string(">>>>'HELP CONNECTION' : Obtem informacoes de conex�o com o servidor.\n");
	//string(">> Digite 'HELP <NOMEDAQUERY>' : Para obter a funcionalidade de uma query.\n") +
	//string(">>                               EX.: HELP ADD\n");

string HELPQUERY = 
	string(">> QUERY EXAMPLES:\n") +
	string(">>  ADD\n") +
	string(">>  ADD VALUE <attr_1> = <val_1> <attr_2> = <val_2> ... <attr_N> = <val_N>\n") + 
	string(">>  SELECT WHERE ID = 7\n") + 
	string(">>  SELECT ALL\n") + 
	string(">>  DELETE WHERE ID = 7\n") + 
	string(">>  UPDATE WHERE ID = 4 VALUE <attr_1> = <val_1> <attr_2> = <val_2> ... <attr_N> = <val_N>\n\n");


#endif