#include "../header.h"

void ComplementoAFD(char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
    printf("Complemento do AFD!\n");

    AFD *afd = LerArquivo(nomeArquivoEntrada);

    InverterEstados(afd->Estados);

    CriarArquivo(afd, nomeArquivoSaida);
}

void InverterEstados(Estado *estado)
{
    if(estado != NULL)
    {
        if(estado->Final == 0)
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