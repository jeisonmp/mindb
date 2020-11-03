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

#include "..\headers\Thread.h"
#include <string>
#include "..\config.h"

Thread::Thread() {}

using std::string;

int Thread::CreateNewThread(void * arg)
{
	int code = 0;
    this->setArg(arg); // store user data

	this->thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Thread::EntryPoint,(LPVOID) this,0,(LPDWORD) &lpId);
		
	char procId[10];
	sprintf(procId,"%d", this->lpId);
	this->semaphore = CreateSemaphore(NULL, 0, 1, (LPCSTR)(procId));
	
	if(this->thread == NULL) code = 1;

	return code;
}

void* Thread::EntryPoint(void * pthis)
{
	Thread * pt = (Thread*)pthis;
	pt->Run( pt->getArg() );

	//As thread estao morrendo: Acredito ser devido o metodo ser estatico.
	//Apenas para teste;
	TerminateThread(pt->thread, pt->lpId);
	return NULL;
}

void* Thread::getArg()
{
	return this->arg;
}
void Thread::setArg(void* arg)
{
	this->arg = arg;
}