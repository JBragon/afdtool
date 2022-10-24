#include "../header.h"

void ConverterAFDParaDot(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    printf("Converter ADF para DOT!\n");

    AFD *afd = LerArquivo(nomeArquivoEntrada);

    GerarDot(afd, nomeArquivoSaida);

    printf("Arquivo %s exportado.\n", nomeArquivoSaida);

}

void GerarDot(AFD *afd, char *nomeArquivoSaida)
{
    FILE *output = fopen(nomeArquivoSaida, "w");

    if (output == NULL) {
        printf("Erro ao abrir arquivo de saída.");
        exit(EXIT_FAILURE);
    }

    fputs("digraph finite_state_machine {\n", output);
    fputs("node [shape = doublecircle];\n", output);

    EscreverEstadosFinais(afd->Estados, output);

    fputs("\nnode [shape = circle];\n", output);

    EscreverTransicoes(afd->Transicoes, output);

    fputs("}\n", output);

    fclose(output);
}

void EscreverEstadosFinais(Estado *estado, FILE *arquivoDeSaida)
{
    if (estado != NULL) {
        if (estado->Final == 1) {
            fprintf(arquivoDeSaida, "\"%s\";", estado->Descricao);
        }
        EscreverEstadosFinais(estado->ProximoEstado, arquivoDeSaida);
    }
}

void EscreverTransicoes(Transicao *transicao, FILE *arquivoDeSaida)
{
    if (transicao != NULL) {
        fprintf(arquivoDeSaida, 
        "\"%s\" -> \"%s\" [label = \"%s\"]\n", transicao->EstadoOrigem->Descricao, 
        transicao->EstadoDestino->Descricao, transicao->SimboloAlfabeto->Simbolo);
        EscreverTransicoes(transicao->ProximaTransicao, arquivoDeSaida);
    }
}