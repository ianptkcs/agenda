# Agenda Eletrônica

## Descrição

Este programa implementa uma Agenda Eletrônica utilizando um TAD (Tipo Abstrato de Dados) de fila de prioridade. O objetivo é auxiliar usuários na organização de tarefas diárias, permitindo a inserção de atividades com diferentes níveis de importância e a consulta da próxima tarefa mais importante a ser realizada.

O programa permite:

-   Inserir novas tarefas com prioridade entre 1 e 99.
-   Consultar e remover a tarefa de maior prioridade.
-   Exibir todas as tarefas remanescentes ao finalizar o expediente, ordenadas por importância.

## Funcionalidades

-   **Inserção de Tarefas**: O usuário pode adicionar tarefas a qualquer momento, especificando a prioridade e uma descrição da atividade.
-   **Consulta da Próxima Tarefa**: Ao concluir uma atividade, o usuário pode consultar qual é a próxima tarefa mais importante a ser realizada.
-   **Finalização do Expediente**: Ao selecionar o comando "FIM", o programa exibe todas as tarefas remanescentes para consulta futura.
-   **Mensagens de Aviso e Erro**:
    -   Aviso se a agenda estiver vazia ao consultar a próxima tarefa.
    -   Erro se houver tentativa de inserir mais elementos que a capacidade da agenda.

## Estrutura do Programa

-   **Linguagem**: CPP
-   **TAD Fila de Prioridade**: Implementado usando um vetor simples, ordenado em ordem crescente de prioridade.
-   **Encapsulamento**: O TAD é encapsulado, e a função `main` interage com ele apenas através de funções públicas.
-   **Funções Públicas**:
    -   `Inicializar`: Inicializa a agenda.
    -   `Finalizar`: Libera a memória alocada pela agenda.
    -   `Inserir`: Insere uma nova tarefa na agenda.
    -   `ConsultarMax`: Consulta a tarefa de maior prioridade sem removê-la.
    -   `RemoverMax`: Remove a tarefa de maior prioridade.
    -   `AgendaVazia`: Verifica se a agenda está vazia.
    -   `AgendaCheia`: Verifica se a agenda está cheia.
-   **Função Privada**:
    -   `BuscaBinariaInsercao`: Encontra o índice adequado para inserção mantendo a ordem do vetor.

## Arquivos

-   **entrada4.txt**: Arquivo de entrada contendo as instruções e comandos para o programa.
-   **Lab4_seu_nome_e_sobrenomes.txt**: Arquivo de saída onde o programa escreverá os resultados.

## Como Compilar e Executar

### Pré-requisitos

-   Compilador C (por exemplo, GCC)
-   Os arquivos `agenda.cpp` (contendo o código fornecido) e `entrada4.txt` devem estar no mesmo diretório.

### Compilação

Abra o terminal no diretório onde estão os arquivos e execute:

```bash
gcc -o agenda agenda.cpp
```

Isso irá compilar o programa e gerar um executável chamado `agenda`.

### Execução

Após a compilação bem-sucedida, execute o programa com:

```bash
./agenda
```

O programa lerá o arquivo `entrada4.txt` e gerará o arquivo de saída `Lab4_seu_nome_e_sobrenomes.txt`.

## Formato dos Arquivos

### Arquivo de Entrada (`entrada4.txt`)

O arquivo de entrada deve seguir o formato especificado:

-   Cabeçalho com informações iniciais.
-   Número máximo de elementos na agenda.
-   Lista de comandos:
    -   `NOVA <prioridade> <descrição>`: Insere uma nova tarefa.
    -   `PROXIMA`: Consulta e remove a tarefa de maior prioridade.
    -   `FIM`: Finaliza o expediente e exibe as tarefas remanescentes.

Exemplo de comandos:

```
NOVA          40       Estudar matematica
PROXIMA
NOVA          60       Fazer lab de ces-11
FIM
```

### Arquivo de Saída (`Lab4_seu_nome_e_sobrenomes.txt`)

O arquivo de saída conterá:

-   Cabeçalho com exatamente 5 linhas.
-   Seção `RESPOSTAS DAS CONSULTAS` com as tarefas removidas durante as consultas.
-   Seção `FICA PARA O DIA SEGUINTE` com as tarefas remanescentes.

## Observações

-   **Limites de Prioridade**: As prioridades devem estar entre 1 e 99. Se um valor fora desse intervalo for fornecido, o programa ajustará para 1 ou 99 conforme apropriado.
-   **Capacidade da Agenda**: Se tentar inserir mais tarefas do que a capacidade máxima, o programa exibirá uma mensagem de erro.
-   **Mensagens Personalizadas**: As mensagens de aviso e erro são personalizadas, mas seguem o alinhamento e formato especificados no exemplo.
-   **Nome**: lembre de trocar 'seu_nome_e_sobrenomes' pelas suas informações!

## Exemplos de Uso

### Exemplo de Entrada

```
Software para agenda eletronica
Exemplo de arquivo de entrada
Bla bla
--------------------------------------------------
Numero maximo de elementos na agenda:
30
--------------------------------------------------
TAREFA   IMPORTANCIA   DESCRICAO
--------------------------------------------------
NOVA          40       Estudar matematica
PROXIMA
NOVA          60       Fazer lab de ces-11
FIM
```

### Exemplo de Saída

```
Agenda Eletronica - Exemplo de arquivo de saida.
Pode colocar qualquer texto no cabecalho.
O cabecalho deve ter exatamente 5 linhas.
Neste caso, a quinta linha estah em branco  :-()

--------------------------------------------------
RESPOSTAS DAS CONSULTAS
--------------------------------------------------
40       Estudar matematica

--------------------------------------------------
FICA PARA O DIA SEGUINTE
--------------------------------------------------
60       Fazer lab de ces-11
```

## Contato

Para dúvidas ou sugestões, entre em contato com ianptkcs@gmail.com.
