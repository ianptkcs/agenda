/* Ian Patrick da Costa Soares                      */
/* Turma 28.1                                       */
/* Exercício 4: Agenda Eletrônica + Vetor Simples   */
/*                                                  */
/* Programa compilado com Visual Studio Code 1.92.2 */

/* Incluir as bibliotecas usadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
- Este programa implementa uma agenda eletrônica usando um TAD fila de prioridade.
- O usuário pode inserir tarefas com prioridades entre 1 e 99.
- O programa permite consultar e remover a tarefa de maior prioridade.
- Ao finalizar, o programa exibe as tarefas remanescentes ordenadas por prioridade.
*/

/* Definição de structs */
typedef struct
{
    int prioridade;
    char descricao[41]; // Descrição com máximo de 40 caracteres + '\0'
} Tarefa;

typedef struct
{
    Tarefa *tarefas;    // Vetor dinâmico de tarefas
    int num_tarefas;    // Número atual de tarefas
    int capacidade_max; // Capacidade máxima
} Agenda;

/* Declaração de funções públicas */
void Inicializar(Agenda *agenda, int capacidade_max);
void Finalizar(Agenda *agenda);
bool AgendaVazia(Agenda *agenda);
bool AgendaCheia(Agenda *agenda);
int Inserir(Agenda *agenda, Tarefa nova_tarefa);
int ConsultarMax(Agenda *agenda, Tarefa *tarefa);
void RemoverMax(Agenda *agenda);
int ObterNumTarefas(Agenda *agenda);
int ObterTarefa(Agenda *agenda, int indice, Tarefa *tarefa);

/* Função privada */
int BuscaBinariaInsercao(Agenda *agenda, int prioridade);

/*--------------------------------------------------*/

/* Função para inicializar a agenda */
void Inicializar(Agenda *agenda, int capacidade_max)
{
    agenda->tarefas = (Tarefa *)malloc(sizeof(Tarefa) * (capacidade_max + 1)); // posição 0 não utilizada
    agenda->num_tarefas = 0;
    agenda->capacidade_max = capacidade_max;
}

/*--------------------------------------------------*/

/* Função para finalizar a agenda e liberar memória */
void Finalizar(Agenda *agenda)
{
    free(agenda->tarefas);
}

/*--------------------------------------------------*/

/* Função para verificar se a agenda está vazia */
bool AgendaVazia(Agenda *agenda)
{
    return agenda->num_tarefas == 0;
}

/*--------------------------------------------------*/

/* Função para verificar se a agenda está cheia */
bool AgendaCheia(Agenda *agenda)
{
    return agenda->num_tarefas >= agenda->capacidade_max;
}

/*--------------------------------------------------*/

/* Função para inserir uma nova tarefa na agenda */
int Inserir(Agenda *agenda, Tarefa nova_tarefa)
{
    if (AgendaCheia(agenda))
    {
        return -1; // Indica que a agenda está cheia
    }
    // Encontra o índice de inserção usando busca binária
    int indice = BuscaBinariaInsercao(agenda, nova_tarefa.prioridade);

    // Desloca os elementos para abrir espaço para a nova tarefa
    for (int i = agenda->num_tarefas; i >= indice; i--)
    {
        agenda->tarefas[i + 1] = agenda->tarefas[i];
    }
    // Insere a nova tarefa
    agenda->tarefas[indice] = nova_tarefa;
    agenda->num_tarefas++;
    return 0; // Sucesso
}

/*--------------------------------------------------*/

/* Função para consultar a tarefa de maior prioridade */
int ConsultarMax(Agenda *agenda, Tarefa *tarefa)
{
    if (AgendaVazia(agenda))
    {
        return -1; // Indica que a agenda está vazia
    }
    *tarefa = agenda->tarefas[agenda->num_tarefas];
    return 0; // Sucesso
}

/*--------------------------------------------------*/

/* Função para remover a tarefa de maior prioridade */
void RemoverMax(Agenda *agenda)
{
    if (!AgendaVazia(agenda))
    {
        agenda->num_tarefas--;
    }
}

/*--------------------------------------------------*/

/* Função para obter o número atual de tarefas na agenda */
int ObterNumTarefas(Agenda *agenda)
{
    return agenda->num_tarefas;
}

/*--------------------------------------------------*/

/* Função para obter uma tarefa específica na agenda */
int ObterTarefa(Agenda *agenda, int indice, Tarefa *tarefa)
{
    if (indice < 1 || indice > agenda->num_tarefas)
    {
        return -1; // Índice inválido
    }
    *tarefa = agenda->tarefas[indice];
    return 0; // Sucesso
}

/*--------------------------------------------------*/

/* Função privada para realizar busca binária para inserção */
int BuscaBinariaInsercao(Agenda *agenda, int prioridade)
{
    int esquerda = 1;
    int direita = agenda->num_tarefas;
    int meio;
    while (esquerda <= direita)
    {
        meio = (esquerda + direita) / 2;
        if (agenda->tarefas[meio].prioridade < prioridade)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }
    return esquerda;
}

/*--------------------------------------------------*/

/* Função principal */
int main()
{
    const int MAX_LINE = 71;
    FILE *arquivo_entrada = fopen("entrada4.txt", "r");
    FILE *arquivo_saida = fopen("Lab4_seu_nome_e_sobrenomes.txt", "w");

    if (!arquivo_entrada || !arquivo_saida)
    {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char linha[MAX_LINE];
    int capacidade_max = 0;

    // Escrever o cabeçalho no arquivo de saída conforme o exemplo
    fprintf(arquivo_saida, "Agenda Eletronica - Exemplo de arquivo de saida.\n");
    fprintf(arquivo_saida, "Pode colocar qualquer texto no cabecalho.\n");
    fprintf(arquivo_saida, "O cabecalho deve ter exatamente 5 linhas.\n");
    fprintf(arquivo_saida, "Neste caso, a quinta linha estah em branco  :-)\n");
    fprintf(arquivo_saida, "\n");

    // Ler o arquivo de entrada para encontrar capacidade_max
    while (fgets(linha, MAX_LINE, arquivo_entrada))
    {
        if (strstr(linha, "Numero maximo de elementos na agenda:"))
        {
            // Ler a próxima linha com a capacidade máxima
            if (fgets(linha, MAX_LINE, arquivo_entrada))
            {
                sscanf(linha, "%d", &capacidade_max);
                break;
            }
        }
    }

    // Pular linhas até "TAREFA"
    while (fgets(linha, MAX_LINE, arquivo_entrada))
    {
        if (strstr(linha, "TAREFA"))
        {
            // Pular a próxima linha separadora
            fgets(linha, MAX_LINE, arquivo_entrada);
            break;
        }
    }

    // Inicializar a agenda
    Agenda agenda;
    Inicializar(&agenda, capacidade_max);

    // Preparar para coletar as saídas dos comandos "PROXIMA"
    fprintf(arquivo_saida, "--------------------------------------------------\n");
    fprintf(arquivo_saida, "RESPOSTAS DAS CONSULTAS\n");
    fprintf(arquivo_saida, "--------------------------------------------------\n");

    // Processar comandos
    while (fgets(linha, MAX_LINE, arquivo_entrada))
    {
        char comando[10];
        int prioridade = 0;
        char descricao[41] = "";

        // Verificar se a linha está vazia ou é apenas uma nova linha
        if (strlen(linha) <= 1)
        {
            continue;
        }

        sscanf(linha, "%s", comando);

        if (strcmp(comando, "NOVA") == 0)
        {
            // Ler prioridade e descrição
            char *ptr = linha + 4; // Avançar após "NOVA"
            // Pular espaços
            while (*ptr == ' ' || *ptr == '\t')
                ptr++;
            sscanf(ptr, "%d", &prioridade);
            // Avançar após a prioridade
            while (*ptr >= '0' && *ptr <= '9')
                ptr++;
            // Pular espaços
            while (*ptr == ' ' || *ptr == '\t')
                ptr++;
            strncpy(descricao, ptr, 40);
            // Remover o caractere de nova linha, se presente
            size_t len = strlen(descricao);
            if (len > 0 && descricao[len - 1] == '\n')
            {
                descricao[len - 1] = '\0';
            }

            // Garantir que a prioridade esteja entre 1 e 99
            if (prioridade < 1 || prioridade > 99)
            {
                prioridade = (prioridade < 1) ? 1 : 99;
            }

            Tarefa nova_tarefa;
            nova_tarefa.prioridade = prioridade;
            strncpy(nova_tarefa.descricao, descricao, 40);
            nova_tarefa.descricao[40] = '\0';

            int res = Inserir(&agenda, nova_tarefa);
            if (res == -1)
            {
                // Agenda cheia, escrever mensagem de erro
                fprintf(arquivo_saida, "ERRO     Agenda cheia. Impossivel inserir.\n");
            }
        }
        else if (strcmp(comando, "PROXIMA") == 0)
        {
            if (AgendaVazia(&agenda))
            {
                // Escrever mensagem de aviso
                fprintf(arquivo_saida, "AVISO    Nao ha tarefas na agenda  :-)\n");
            }
            else
            {
                Tarefa tarefa;
                ConsultarMax(&agenda, &tarefa);
                RemoverMax(&agenda);
                fprintf(arquivo_saida, "%2d       %-40s\n", tarefa.prioridade, tarefa.descricao);
            }
        }
        else if (strcmp(comando, "FIM") == 0)
        {
            break;
        }
        else
        {
            // Ignorar quaisquer outros comandos ou linhas
            continue;
        }
    }

    // Exibir tarefas remanescentes
    fprintf(arquivo_saida, "\n--------------------------------------------------\n");
    fprintf(arquivo_saida, "FICA PARA O DIA SEGUINTE\n");
    fprintf(arquivo_saida, "--------------------------------------------------\n");

    if (AgendaVazia(&agenda))
    {
        fprintf(arquivo_saida, "Agenda vazia! Nao restam tarefas para o dia seguinte.\n");
    }
    else
    {
        for (int i = agenda.num_tarefas; i >= 1; i--)
        {
            Tarefa tarefa;
            ObterTarefa(&agenda, i, &tarefa);
            fprintf(arquivo_saida, "%2d       %-40s\n", tarefa.prioridade, tarefa.descricao);
        }
    }

    // Finalizar a agenda
    Finalizar(&agenda);

    // Fechar arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    return 0;
}
