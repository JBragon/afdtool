#include "../header.h"

void UniaoAFD(char *nomeArquivoAFD1, char *nomeArquivoAFD2, char *nomeArquivoSaida)
{
    printf("União entre AFD's!\n");

    double tempoDecorrido = 0.0;
    clock_t inicio = clock();

    AFD *afd1 = LerArquivo(nomeArquivoAFD1);
    AFD *afd2 = LerArquivo(nomeArquivoAFD2);

    AFD *uniao = InicializarAFD();
    uniao = ProdutoAFD(*afd1, *afd2);

    Estado *estadosFinaisAFD1 = ListarEstadosFinaisOuNaoFinais(afd1->Estados, estadosFinaisAFD1, 1);
    Estado *estadosFinaisAFD2 = ListarEstadosFinaisOuNaoFinais(afd2->Estados, estadosFinaisAFD2, 1);
    int QTDEstadosFinais = 0;

    for (Estado *estado = uniao->Estados; estado != NULL; estado = estado->ProximoEstado)
    {
    
        int estadoFinal = 0;

        char *copy = estado->Descricao;
        int size = strlen(copy);
        char *estadoComparacao = malloc((size + 1) * sizeof(char));
        strcpy(estadoComparacao, copy);

        // dividindo os estados para comparação com os finais de ambos os AFD's
        char *aux;
        char **split = malloc(2 * sizeof(char *));
        aux = strtok(estadoComparacao, "&");
        int x = 0;
        while (aux != NULL)
        {
            split[x] = aux;
            aux = strtok(NULL, "&");
            x++;
        }

        //Se um dos estados que pertencem ao estado resultante for final no AFD de origem,
        //o estado novo também será final
        for (Estado *estadoI = estadosFinaisAFD1; estadoI != NULL; estadoI = estadoI->ProximoEstado)
        {
            //Comparação se um dos estados pertecente ao resultante é final no AFD de origem
            if (strcmp(estadoI->Descricao, split[0]) == 0 || strcmp(estadoI->Descricao, split[1]) == 0)
            {
                estadoFinal = 1;
            }
        }

        if (estadoFinal == 0)
            for (Estado *estadoI = estadosFinaisAFD2; estadoI != NULL; estadoI = estadoI->ProximoEstado)
            {
                //Comparação se um dos estados pertecente ao resultante é final no AFD de origem
                if (strcmp(estadoI->Descricao, split[0]) == 0 
                || strcmp(estadoI->Descricao, split[1]) == 0)
                {
                    estadoFinal = 1;
                }
            }

        if (estadoFinal == 1)
        {   
            QTDEstadosFinais++;
            BuscarEstado(estado->Descricao, uniao->Estados)->Final = 1;
        }
    }

    uniao->QTDEstadosFinais = QTDEstadosFinais;

    CriarArquivo(uniao, nomeArquivoSaida);

    clock_t fim = clock();
    tempoDecorrido += (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de resposta: %f segundos\n", tempoDecorrido);
}
