#include "../header.h"


void InverterEstados(Estado *estado)
{
    if (estado != NULL)
    {
        if (estado->Final == 0)
        {
            estado->Final = 1;
        }
        else
        {
            estado->Final = 0;
        }

        InverterEstados(estado->ProximoEstado);
    }
}


void ComplementoAFD(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    printf("Complemento do AFD!\n");
    double tempoDecorrido = 0.0;
    clock_t inicio = clock();
    AFD *afd = LerArquivo(nomeArquivoEntrada);

    InverterEstados(afd->Estados);

    CriarArquivo(afd, nomeArquivoSaida);

    clock_t fim = clock();
    tempoDecorrido += (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de resposta: %f segundos\n", tempoDecorrido);
}
