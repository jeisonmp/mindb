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