#include "header.h"





/// @brief função que irar filtrar a operação para fazer a comparação com o switch case da main.c
/// @param operacao 
/// @return 
int BuscaOperacao(char *operacao)
{

    char operacoes[][256] =
        {
            "--complemento",
            "--dot",
            "--intersecao",
            "--uniao",
            "--minimizacao",
            "--reconhecer",
            "--help"};

    for (int i = 0; i < 7; i++)
    {
        if (strcmp(operacao, operacoes[i]) == 0)
        {
            return i + 1;
        }
    }

    return -1;
}


void ExportarEstados(Estado *estado, FILE *arquivoDeSaida)
{
    if (estado != NULL)
    {
        fprintf(arquivoDeSaida, "%s\n", estado->Descricao);
        ExportarEstados(estado->ProximoEstado, arquivoDeSaida);
    }
}

void ExportarEstadosParaArquivo(AFD *afd, FILE *arquivoDeSaida)
{
    fprintf(arquivoDeSaida, "%d\n", afd->QTDEstados);

    ExportarEstados(afd->Estados, arquivoDeSaida);
}


void ExportarSimbolos(SimboloAlfabeto *simboloAlfabeto, FILE *arquivoDeSaida)
{
    if (simboloAlfabeto != NULL)
    {
        fprintf(arquivoDeSaida, "%s\n", simboloAlfabeto->Simbolo);
        ExportarSimbolos(simboloAlfabeto->ProximoSimbolo, arquivoDeSaida);
    }
}

void ExportarSimbolosParaArquivo(AFD *afd, FILE *arquivoDeSaida)
{
    fprintf(arquivoDeSaida, "%d\n", afd->QTDSimbolos);

    ExportarSimbolos(afd->Alfabeto, arquivoDeSaida);
}



void ExportarTransicoes(Transicao *transicao, FILE *arquivoDeSaida)
{
    if (transicao != NULL)
    {
        fprintf(arquivoDeSaida, "%s %s %s\n", transicao->EstadoOrigem->Descricao, transicao->SimboloAlfabeto->Simbolo, transicao->EstadoDestino->Descricao);
        ExportarTransicoes(transicao->ProximaTransicao, arquivoDeSaida);
    }
}

void ExportarTransicoesParaArquivo(AFD *afd, FILE *arquivoDeSaida)
{
    fprintf(arquivoDeSaida, "%d\n", afd->QTDTransicoes);
    ExportarTransicoes(afd->Transicoes, arquivoDeSaida);
}

void ExportarEstadosIniciaisParaArquivo(Estado *estado, FILE *arquivoDeSaida)
{
    if (estado != NULL)
    {
        if (estado->Inicial == 1)
            fprintf(arquivoDeSaida, "%s\n", estado->Descricao);

        ExportarEstadosIniciaisParaArquivo(estado->ProximoEstado, arquivoDeSaida);
    }
}


void ExportarEstadosFinais(Estado *estado, FILE *arquivoDeSaida)
{
    if (estado != NULL)
    {
        if (estado->Final == 1)
            fprintf(arquivoDeSaida, "%s\n", estado->Descricao);

        ExportarEstadosFinais(estado->ProximoEstado, arquivoDeSaida);
    }
}

void ExportarEstadosFinaisParaArquivo(AFD *afd, FILE *arquivoDeSaida)
{
    fprintf(arquivoDeSaida, "%d\n", afd->QTDEstadosFinais);

    ExportarEstadosFinais(afd->Estados, arquivoDeSaida);
}


void ImprimirAjuda()
{
    printf("--dot                  Para visualizar AFD em DOT!\n");
    printf("                       Exemplo: ./afdtool --dot afd.txt --output afd.dot\n");
    printf("--complemento          Complemento do AFD!\n");
    printf("                       Exemplo: ./afdtool --complemento afd1.txt --output afd1-complemento.txt\n");
    printf("--intersecao           interseção entre dois AFD's!\n");
    printf("                       Exemplo: ./afdtool --intersecao afd1.txt afd2.txt --output afd1-intersecao-afd2.txt\n");
    printf("--uniao                união entre dois AFD's!\n");
    printf("                       Exemplo: ./afdtool --uniao afd1.txt afd2.txt --output afd1-uniao-afd2.txt\n");
    printf("--reconhecer           Verificar se palavra é reconhecida no AFD!\n");
    printf("                       Exemplo: ./afdtool --reconhecer afd.txt palavras.txt --output palavras-reconhecidas.txt\n");
}

void ValidaArgumentos(int argc)
{
    if (argc < 5)
    {
        printf("Informe os demais argumentos.\n");
        ImprimirAjuda();
        exit(EXIT_FAILURE);
    }
}

/// @brief Função que transpila um AFD para um arquivo
/// @param afd 
/// @param nomeArquivoDeSaida 
void CriarArquivo(AFD *afd, char *nomeArquivoDeSaida)
{
    FILE *arquivoDeSaida = fopen(nomeArquivoDeSaida, "w");

    if (arquivoDeSaida == NULL)
    {
        printf("Erro ao criar arquivo de saída.");
        exit(EXIT_FAILURE);
    }

    ExportarEstadosParaArquivo(afd, arquivoDeSaida);
    ExportarSimbolosParaArquivo(afd, arquivoDeSaida);
    ExportarTransicoesParaArquivo(afd, arquivoDeSaida);
    ExportarEstadosIniciaisParaArquivo(afd->Estados, arquivoDeSaida);
    ExportarEstadosFinaisParaArquivo(afd, arquivoDeSaida);

    fclose(arquivoDeSaida);

    printf("Arquivo %s exportado.\n", nomeArquivoDeSaida);
}
