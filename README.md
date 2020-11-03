# minDB - Sistema Gerenciador de Banco de Dados Mínimo #

Este projeto trata-se de um gerenciador de banco de dados *multithread*, escrito em C/C++ no sistema operacional windows.

### Objetivos Gerais ###

* Fornecer uma interface ao usuário para acesso à dados (API’s);
* Fornecer uma linguagem que permite a criação, alteração e consulta à dados;

### Funcionamento básico ###

1. O SERVIDOR é iniciado, estabelece a conexão e inicializa o SGBD;
2. O SGBD, ao ser iniciado, realiza a leitura de todas as tabelas do banco:
    * Para cada Entidade é criada uma Thread SGBD. Todas elas iniciam-se dormindo;
    * O servidor mantém uma lista de Entidades e uma HANDLE em cada Entidade, para garantir a exclusão mútua do acesso aos arquivos;
3. O Servidor então vai para o estado de AGUARDAR CLIENTE, para aguardar uma requisição;
4. Quando a requisição chega o servidor repassa a informação para o SGBD, iniciando uma thread, e retorna para o estado AGUARDAR CLIENTE;
5. A Thread SGBD identifica a Entidade que será acionada e o “acorda”, esta Entidade irá tratar a requisição do usuário e retornar ao cliente através do Servidor;
6. Após a Entidade entregar a mensagem ele passa a dormir novamente.

### Diagrama do funcionamento ###

![Diagrama de Funcionamento do Servidor de Banco de Dados.png](https://bitbucket.org/repo/zka65y/images/2596291545-Diagrama%20de%20Funcionamento%20do%20Servidor%20de%20Banco%20de%20Dados.png)

### Para executar o projeto ###

O projeto está organizado em 3 pastas + um arquivo config.h:
* Entities: Contém as entidades, é nesta pasta que o SGDB consulta as tabelas do banco de dados. A ideia é utilizar arquivos para identificar a tabela. Por exemplo: arquivo 'carro.txt' representando a tabela 'carro' de um banco de dados. O sistema procura estes arquivos, entretanto faltam as implementações DDM e DML necessárias. A estrutura interna destes arquivos também precisam ser definidas, como: área de configuração, área de dados, etc.
* headers: Contém todas as bibliotecas do SGDB;
* src: Contém todos os .cpp do SGDB;
* config.h: Arquivo das definições, deve ser setado o ip do servidor antes da compilação.

Os arquivos 'mainCliente.cpp' e 'mainServer.cpp', são exemplos de aplicações usadas que representam o cliente e servidor, respectivamente.

Para compilar o projeto, utilize o visual studio 2015 e abra o arquivo 'SGBD.sln' e execute o projeto. Ou, em qualquer outro Visual Studio, crie uma aplicação vazia em C++, inclua todos os arquivos das pastas descritos acima, inclua o config.h (configure o ip do servidor) e gere duas aplicações: uma para o servidor e outra para o cliente.

Obs.: As versões mais recentes do VS informam um erro de segurança em algumas funções depreciadas, para ignorar estes erros siga os seguintes passos:
- abra o visual studio
- clique na solução com o botão direito e clique em propriedades;
- na aba C/C++/Preprocessor clique em 'Preprocessor Definitions', clique na seta para abrir um diálogo e depois em '<edit>';
- adicione "_CRT_SECURE_NO_WARNINGS", clique em OK e depois em 'aplicar';
- recompile o seu projeto. 

Ao compilar os programas, pegue-os os executáveis gerados na pasta 'debug' ou 'release', dependendo da escolha da compilação no seu VS, renomeia-os e execute-os. Faça isso duas vezes, uma para gerar o servidor e outra para o cliente.

### Instruções do programa 'cliente' ###

No programa cliente, é possível realizar de mensagens para o servidor, mesmo elas não representando comandos SQL, é possível observar o recebimento da requisição. Neste momento ela é tratada como apenas uma mensagem e retorna apenas um 'ack' de confirmação ao usuário.
Este é o ponto em que será necessário a inclusão das linguagens DDL e DML para manipulação de dados, receber a requisição, verificar a sintaxe da instrução, executar o comando da query e retornar as respostas devidas (dados, confirmação de insert, etc).

A princípio, estes comandos pode ser definidos no arquivo 'src/SGDB.cpp'.

# DESCRIÇÃO DAS CLASSES E DOS PROGRAMAS #
## 1. Programa Main/Servidor ##
* Instancia a classe SERVER
* Inicializa comunicação socket
* Matém um loop de execução:
* * Aguarda cliente;
* * Abre uma thread server.

## 2. CLASSE SERVER ##
* Reinicia ClienteSocket
* Inicializa o SGDB
* Estabelece conexão com cliente
* Atende solicitações dos clientes

## 3. CLASSE SGDB ##
* Matém uma fila de entidades ativas, mas dormindo (exclusão mútua).
* Realiza o tratamento das querys quando acordadas.
* O construtor da classe carrega todas as Entidades.

## 4. CLASSE ENTITY ##
* O SGBD inicia uma por tabela.
* São usados dois semáforos para tratamento de exclusão mútua: um para o controle dos dados e o outro para o controle de execução.
* Para cada entidade é criada uma thread.

# ETAPAS DE EXECUÇÃO #
![etapas de execucao.JPG](https://bitbucket.org/repo/zka65y/images/1147084866-etapas%20de%20execucao.JPG)

# MAIS CLASSES #
## 5. CLASSE SERVERTHREAD ##
* Criada a cada requisição;
* Invoca o método receive do servidor para atender requisições;
* Recebe a mensagem via socket;
* Cria uma REQUISITIONTHREAD;

## 6. CLASSE REQUISITIONTHREAD ##
* Invoca o método do servidor para rodar;
* Usada para não "des"sincronizar a comunicação estabelecida entre os N clientes;
* Depois de atender a requisição ela morre.

# FATORES QUE DEVEM SER LEVADOS EM CONTA EM TODO SGBD #
Construir um banco de dados não é fácil, aqui segue alguns fatores que devem ser levados em conta no projeto:

* Analisar as atividades dos equipamentos de armazenamento e canais de tráfego de informação;
* Frequência de acesso em cada arquivo;
* Frequência de uso e tempo gasto por operação: insert, select, etc;
* Espaço utilizado por arquivo;
* Número de registros por classe de inversão;
* Entre outros...

# Bug tracker #
Encontrou um bug? Informe-nos.

# Mantenedores #
Max Jeison Prass (maxjeison@gmail.com)