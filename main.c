#include "src/header.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");
    
    int operacao = BuscaOperacao(argv[1]);

    switch (operacao)
    {
    case VISUALIZAR:
        ValidaArgumentos(argc);
        ConverterAFDParaDot(argv[2], argv[4]);
        break;

    case COMPLEMENTO:
        ValidaArgumentos(argc);
        ComplementoAFD(argv[2], argv[4]);
        break;

    case INTERSECAO:
        ValidaArgumentos(argc);
        IntersecaoAFD(argv[2], argv[3], argv[5]);
        break;

    case UNIAO:
        ValidaArgumentos(argc);
        UniaoAFD(argv[2], argv[3], argv[5]);
        break;

    case MINIMIZACAO:
        printf("Operação não implementada!\n");
        break;

    case RECONHECIMENTO:
        ValidaArgumentos(argc);
        ReconhecerPalavra(argv[2], argv[3], argv[5]);
        break;

    case AJUDA:
        ImprimirAjuda();
        break;

    default:
        printf("Argumento inválido!\n");
        ImprimirAjuda();
        return 1;
    }

    return 1;
}