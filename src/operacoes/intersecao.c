#include "../header.h"

void IntersecaoAFD(char *nomeArquivoAFD1, char *nomeArquivoAFD2, char *nomeArquivoSaida)
{
    printf("Interseção entre AFD's!\n");
    AFD *afd1 = LerArquivo(nomeArquivoAFD1);
    AFD *afd2 = LerArquivo(nomeArquivoAFD2);

    AFD *intersecao = InicializarAFD();
    intersecao = ProdutoAFD(*afd1, *afd2);

    Estado *estadosFinaisAFD1 = ListarEstadosFinaisOuNaoFinais(afd1->Estados, estadosFinaisAFD1, 1);
    Estado *estadosFinaisAFD2 = ListarEstadosFinaisOuNaoFinais(afd2->Estados, estadosFinaisAFD2, 1);
    int QTDEstadosFinais = 0;

    //Atribuindo estados finais
    //Somente os estados que são finais nos AFD's 1 e 2 que será final no AFD's resultante do produto
    for (Estado *estadoI = estadosFinaisAFD1; estadoI != NULL; estadoI = estadoI->ProximoEstado)
    {
        for (Estado *estadoJ = estadosFinaisAFD2; estadoJ != NULL; estadoJ = estadoJ->ProximoEstado)
        {
            char *descricaoEstadoFinal[STRLENGTH];
            strcpy(descricaoEstadoFinal, estadosFinaisAFD1->Descricao);
            strcat(descricaoEstadoFinal, "&");
            strcat(descricaoEstadoFinal, estadosFinaisAFD2->Descricao);

            QTDEstadosFinais++;
            BuscarEstado(descricaoEstadoFinal, intersecao->Estados)->Final = 1;
        }
    }

    intersecao->QTDEstadosFinais = QTDEstadosFinais;

    CriarArquivo(intersecao, nomeArquivoSaida);
}
