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
#include <iostream>
#include <regex>

#include "..\headers\SGBD.h"
#include "..\headers\Entity.h"
#include "..\headers\dirent.h"
#include "..\headers\thread.h"
#include "..\headers\bcp.h"
#include "..\headers\action.h"
#include "..\headers\help.h"
#include "..\config.h"

using std::string;

SGDB::SGDB()
{
	// Carrega todas as entidades do banco de dados
	this->LoadEntities();
}

class SGBDTHREAD: public Thread
{
	Entity *entity;

public:
	SGBDTHREAD(Entity *entity)
	{
		this->entity = entity;
		Thread::CreateNewThread(this);
	}

	void Run(void*)
	{
		FILE *file = NULL;
		string folder = FOLDERTABLES;
		folder += (*this->entity).getTable();
		file = fopen(folder.c_str(), "r");

		while (true)
		{
			entity->Block();

			printf("query: %s\n", entity->getQuery().c_str());

			//(...) CODIGO DAS DML - Data Manipulation Language.

			entity->Release();
		}
	}
};

/*
 * Este metodo deve tratar de localizar a Entidade especifica requisitada e colocar para rodar.
 *
 * Sao 3 os passos necessarios:
 *		1. Localizar a entidade             : Entity *entity = this->EntityFindByTable("nome-da-entidade")
 *		2. Repassar a query para a entidade : entity->setQuery((*bcp)->buffer));
 *		3. Colocar a entidade para rodar    : entity->Start();
 *
 */
bool SGDB::RequisitionQuery(Bcp **bcp)
{
	//Implementar
	//int table = GETTABLE((*bcp)->buffer);

	string a = (*bcp)->buffer;
	Entity *entity = this->EntityFindByTable("pfisica");
 	entity->Start((*bcp)->buffer);
	
	//int action = GETACTIONCODE((*bcp)->action);

	///*
	//* Trecho para verificar a concorrencia das threads (cpu = true = ganhou cpu)
	//*/
	//if (action != MESSAGE)
	//{
	//	if (this->Query((*bcp)->buffer))
	//	{
	//		if (action = CREATE)
	//		{
				
	//		}
	//		else if (action == ADD)
	//		{
	//			
	//		}
	//		else if (action == DELETE)
	//		{
	//			
	//		}
	//		else if (action == SELECT)
	//		{
	//			
	//		}
	//		else if (action == UPDATE)
	//		{
	//			
	//		}
	//	}
	//	else
	//	{
	//		sprintf((*bcp)->buffer, "%s", ">> Error code. You have an error in your MaxSQL syntax.");
	//	}
	//}
	//else
	//{
	//	//'Help.h'
	//	if (!strcmp(_strupr((*bcp)->buffer), "HELP"))
	//	{
	//		sprintf((*bcp)->buffer, "%s", HELP.c_str());
	//	}
	//	else if (!strcmp(_strupr((*bcp)->buffer), "HELP QUERY"))
	//	{
	//		sprintf((*bcp)->buffer, "%s", HELPQUERY.c_str());
	//	}
	//}

	return false;
}
bool SGDB::Query(string query)
{
	//Esta propriedade pode ser usada pelo servidor
	//para tratar regras especificas.
	//Obs.: Nao descomentar (Elas sao publicas!)
	//this->QueryUpdateReturn = "";
	//this->QuerySelectReturn = "";

	std::string str =  query;
    
	/* EXPRESSOES REGULARES
	 * 
	 * Ex.: (ADD)([\040]+)(WHERE)([\040]+)(ID)([\040]*)(=)([\040]*)([A-Za-z])
	 * Translate: (string) = string
				  (string A|string B) = string A ou string B
				  [\040] = espa�o
				  + = um ou mais
	              * = zero ou mais espa�os
				  [\040]+ = um ou mais espa�os
				  [A-Za-z] = um caractere entre 'a' � 'Z'
				  
	 * string = "ADD" + <1 ou mais espacos> + "WHERE" + <1 ou mais espacos> + "ID" + 
	 */
	std::regex _add("(ADD|add)([\040]+)(VALUE|value)(([\040]+)(MODELO|modelo)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(ANO|ano)([\040]*)(=)([\040]*)([0-9]+))?(([\040]+)(COR|cor)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(CHASSI|chassi)([\040]*)(=)([\040]*)([A-Za-z]+))?(([\040]+)(PROPRIETARIO|proprietario)([\040]*)(=)([\040]*)([A-Za-z]+))?([\040]*)");
	std::regex _add2("(ADD|add)([\040]*)");
	std::regex _adderror("([ADD|add])([\040]+)([^.])");
	std::regex _select("(SELECT|select)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})");
	std::regex _selectall("(SELECT|select)([\040]+)(ALL|all)([\040]*)");
	std::regex _delete("(DELETE|delete)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})");
	std::regex _update("(UPDATE|update)([\040]+)(WHERE|where)([\040]+)(ID|id)([\040]*)(=)([\040]*)([0-9]{1,9})([\040]+)(VALUE|value)([\040]+)(MODELO|modelo|ANO|ano|COR|cor|CHASSI|chassi|PROPRIETARIO|proprietario)([\040]*)(=)([\040]*)(([A-Za-z]|[0-9])+)");
	
	/*
	char modelo[10];
	char ano[10];
	char cor[10];
	char chassi[10];
	char proprietario[10];
	*/
	
	std::smatch match; // Para recolher dados da expressao

	if (regex_search(str, match, _add))
	{
		return true;
	}
    else if (regex_search(str, _add2))
	{
		return (!regex_search(str, _adderror));
	}
	if (regex_search(str, match, _select))
	{
		return true;
	}
	else if (regex_search(str, _selectall))
	{
		return true;
	}
	if (regex_search(str, match, _delete))
	{
		return true;
	}
	if (regex_search(str, match, _update))
	{
		/*this->QueryUpdateReturn = "";

		this->Carro->setId(match.str(9));
		string _attr = match.str(13);
		string _value = match.str(17);
		
		MODELO|modelo|ANO|ano|COR|cor|CHASSI|chassi|PROPRIETARIO|proprietario
		if (_attr.compare("MODELO") == 0 || _attr.compare("modelo") == 0)
		{
			this->QueryUpdateReturn = "UPDATE MODELO";
			this->Carro->setModelo(_value);
		}
		else if (_attr.compare("ANO") == 0 || _attr.compare("ano") == 0)
		{
			this->QueryUpdateReturn = "UPDATE ANO";
			this->Carro->setAno(_value);
		}
		else if (_attr.compare("COR") == 0 || _attr.compare("cor") == 0)
		{
			this->QueryUpdateReturn = "UPDATE COR";
			this->Carro->setCor(_value);
		}
		else if (_attr.compare("CHASSI") == 0 || _attr.compare("chassi") == 0)
		{
			this->QueryUpdateReturn = "UPDATE CHASSI";
			this->Carro->setChassi(_value);
		}
		else if (_attr.compare("PROPRIETARIO") == 0 || _attr.compare("proprietario") == 0)
		{
			this->QueryUpdateReturn = "UPDATE PROPRIETARIO";
			this->Carro->setProprietario(_value);
		}*/
		
		return true;
	}

	return false;
}

bool SGDB::LoadEntities()
{
	DIR *dir;
    struct dirent *lsdir;

	dir = opendir(FOLDERTABLES);

	std::regex regexfindfile("(.+)([.])(.+)");

    /* LEITURA DE TODOS OS ARQUIVOS (TABELAS) DO BANCO DE DADOS */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
		if (std::regex_search(lsdir->d_name, regexfindfile))
		{
			Entity *entity = new Entity(lsdir->d_name);

			ENTITY_LOAD(&this->ENTITYI, &this->ENTITYF, entity);

			SGBDTHREAD *sgbdthread = new SGBDTHREAD(entity);
		}
    }

	return true;
}


Entity* SGDB::EntityFindByTable(string table)
{
	Entity *entity;
	entity = this->ENTITYI;

	if (entity != NULL)
	{
		while (entity != this->ENTITYF)
		{
			if (table.compare(entity->getTable()))
				break;

			entity = entity->right;
		}
	}

	return entity;
}

//// Tupla - Expressao regular para leitura da tupla
//std::regex regextupla("([<].+[>])(.*)([<][/].+[>])");
//	
//std::smatch match;
//
//bool copycode = false;
//char c;
//string code = "";
//string word = "";
//
//if (file != NULL)
//{
//	while ((c = getc(file)) != EOF)
//	{
//		word = word + c;
//
//		//Exemplo: <id>1</id>
//		if (std::regex_search(word, match, regextupla))
//		{
//			word = match.str(2);
//			word = "";
//			int si = match.size();
//			for (int it = 0; it < match.size(); it++)
//			{
//				int a  = 8;
//			}
//		}
//	}
//}