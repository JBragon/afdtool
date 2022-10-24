#include "../header.h"

void ReconhecerPalavra(char *nomeArquivoAFD, char *nomeArquivoPalavras, char *nomeArquivoSaida)
{
    printf("Reconhecimento de palavra no AFD!\n");

    AFD *afd = LerArquivo(nomeArquivoAFD);

    FILE *arquivoPalavras = fopen(nomeArquivoPalavras, "rt");

    if (arquivoPalavras == NULL)
    {
        printf("Não foi possível ler o arquivo.");
        exit(EXIT_FAILURE);
    }

    FILE *arquivoDeSaida = fopen(nomeArquivoSaida, "w");

    char linhaArquivo[STRLENGTH];
    char *simbolo;

    //Percorrendo todo o arquivo
    while (fgets(linhaArquivo, STRLENGTH, arquivoPalavras))
    {
        int palavraReconhecida = 0;
        simbolo = linhaArquivo;

        Estado *estado = RetornaEstadoInicial(afd->Estados);

        //Percorrendo cada simbolo da palavra
        while (*simbolo && isdigit(*simbolo))
        {
            //Percorrendo cada simbolo também percorrerá cada estado do AFD
            estado = RetornaEstadoDestino(afd, estado, *simbolo++);
        }

        if(estado != NULL)
            palavraReconhecida = estado->Final;

        fprintf(arquivoDeSaida, "%d\n", palavraReconhecida);

    }

    fclose(arquivoPalavras);
    fclose(arquivoDeSaida);

    printf("Arquivo %s gerado com sucesso.\n", nomeArquivoSaida);
}

Estado *RetornaEstadoDestino(AFD *afd, Estado *estado, char simboloAlfabeto)
{
    Transicao *transicao = BuscaTransicaoValida(afd->Transicoes, estado, simboloAlfabeto);

    if (transicao == NULL)
        return NULL;

    //Após encontrar a transição, retorna o estado destino da transição para a continuação do reconhecimento
    //da palavra
    return transicao->EstadoDestino;
}

/// @brief Verifica e retorna se existe uma transição valida do estado com o cimbolo
/// @param transicoes 
/// @param estado 
/// @param simboloAlfabeto 
/// @return 
Transicao *BuscaTransicaoValida(Transicao *transicoes, Estado *estado, char simboloAlfabeto)
{
    if (transicoes == NULL || transicoes->EstadoOrigem == NULL || estado == NULL)
        return NULL;

    if (
        strcmp(transicoes->EstadoOrigem->Descricao, estado->Descricao) == 0 &&
        transicoes->SimboloAlfabeto->Simbolo[0] == simboloAlfabeto)
        return transicoes;

    return BuscaTransicaoValida(transicoes->ProximaTransicao, estado, simboloAlfabeto);
}