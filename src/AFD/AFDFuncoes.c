#include "../header.h"

AFD *LerArquivo(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rt");
    AFD *afd = InicializarAFD();

    char linha[STRLENGTH];

    if (arquivo == NULL)
    {
        printf("Não foi possível ler o arquivo.");
        exit(EXIT_FAILURE);
    }

    afd = ImportarEstados(afd, linha, arquivo);

    afd = ImportarAlfabeto(afd, linha, arquivo);

    afd = ImportarTransicoes(afd, linha, arquivo);

    //Buscando Estado inicial
    char *line = fgets(linha, STRLENGTH, arquivo);
    char estadoInicial[STRLENGTH];
    strcpy(estadoInicial, line);
    strtok(estadoInicial, "\n");
    BuscarEstado(estadoInicial, afd->Estados)->Inicial = 1;

    afd->QTDEstadosFinais = atoi(fgets(linha, STRLENGTH, arquivo));

    //Buscando Estados finais
    for (int i = 0; i < afd->QTDEstadosFinais; i++)
    {
        char *linhaArquivo = fgets(linha, STRLENGTH, arquivo);
        char descricaoEstadoFinal[STRLENGTH];
        strcpy(descricaoEstadoFinal, linhaArquivo);
        strtok(descricaoEstadoFinal, "\n");

        BuscarEstado(descricaoEstadoFinal, afd->Estados)->Final = 1;
    }

    fclose(arquivo);

    return afd;
}

AFD *ImportarAlfabeto(AFD *afd, char *linha[STRLENGTH], FILE *arquivo)
{
    afd->QTDSimbolos = atoi(fgets(linha, STRLENGTH, arquivo));

    SimboloAlfabeto *simbolos = NULL;

    for (int i = 0; i < afd->QTDSimbolos; i++)
    {
        char *descricaoSimbolo = fgets(linha, STRLENGTH, arquivo);
        strtok(descricaoSimbolo, "\n");
        simbolos = AdicionarSimbolo(simbolos, descricaoSimbolo);
    }

    afd->Alfabeto = simbolos;

    return afd;
}

AFD *ImportarEstados(AFD *afd, char *linha[STRLENGTH], FILE *arquivo)
{
    afd->QTDEstados = atoi(fgets(linha, STRLENGTH, arquivo));

    Estado *estado = NULL;

    for (int i = 0; i < afd->QTDEstados; i++)
    {
        char *descricaoEstado = fgets(linha, STRLENGTH, arquivo);
        strtok(descricaoEstado, "\n");
        estado = AdicionarEstado(estado, descricaoEstado);
    }

    afd->Estados = estado;

    return afd;
}

AFD *ImportarTransicoes(AFD *afd, char *linha[STRLENGTH], FILE *arquivo)
{
    afd->QTDTransicoes = atoi(fgets(linha, STRLENGTH, arquivo));

    Transicao *transicoes = NULL;

    for (int i = 0; i < afd->QTDTransicoes; i++)
    {
        char linhaArquivo[STRLENGTH];
        strcpy(linhaArquivo, fgets(linha, STRLENGTH, arquivo));

        char estadoOrigem[STRLENGTH];
        char estadoDestino[STRLENGTH];
        char descricaoSimbolo[STRLENGTH];

        int x = 0;
        int y = 0;

        while (x < sizeof(linhaArquivo))
        {
            if (linhaArquivo[x] == ' ')
            {
                x++;
                break;
            }

            estadoOrigem[y] = linhaArquivo[x];
            estadoOrigem[y + 1] = 0;
            x++;
            y++;
        }

        strtok(estadoOrigem, "\n");

        y = 0;

        while (x < sizeof(linhaArquivo))
        {
            if (linhaArquivo[x] == ' ')
            {
                x++;
                break;
            }

            descricaoSimbolo[y] = linhaArquivo[x];
            descricaoSimbolo[y + 1] = 0;
            x++;
            y++;
        }

        y = 0;

        while (x < sizeof(linhaArquivo))
        {
            if (linhaArquivo[x] == ' ')
            {
                x++;
                break;
            }

            estadoDestino[y] = linhaArquivo[x];
            estadoDestino[y + 1] = 0;
            x++;
            y++;
        }

        strtok(estadoDestino, "\n");

        transicoes = AdicionarTransicao(afd, transicoes, estadoOrigem, estadoDestino, descricaoSimbolo);
    }

    afd->Transicoes = transicoes;

    return afd;
}

Estado *AdicionarEstado(Estado *estado, char *descricao)
{
    Estado *e = (Estado *)malloc(sizeof(Estado));

    strcpy(e->Descricao, descricao);
    e->Final = 0;
    e->Inicial = 0;
    e->ProximoEstado = estado;

    return e;
}

SimboloAlfabeto *AdicionarSimbolo(SimboloAlfabeto *simbolo, char *descricaoSimbolo)
{
    SimboloAlfabeto *s = (SimboloAlfabeto *)malloc(sizeof(SimboloAlfabeto));
    strcpy(s->Simbolo, descricaoSimbolo);
    s->ProximoSimbolo = simbolo;

    return s;
}

Transicao *AdicionarTransicao(AFD *afd, Transicao *transicao, char *origem, char *destino, char *simbolo)
{
    Transicao *t = (Transicao *)malloc(sizeof(Transicao));

    t->EstadoOrigem = BuscarEstado(origem, afd->Estados);
    t->EstadoDestino = BuscarEstado(destino, afd->Estados);
    t->SimboloAlfabeto = BuscarSimboloAlfabeto(simbolo, afd->Alfabeto);

    t->ProximaTransicao = transicao;

    return t;
}

Estado *BuscarEstado(char *descricao, Estado *estado)
{
    if (estado == NULL)
        return NULL;
    if (strcmp(estado->Descricao, descricao) == 0)
        return estado;
    return BuscarEstado(descricao, estado->ProximoEstado);
}

SimboloAlfabeto *BuscarSimboloAlfabeto(char *descricaoSimbolo, SimboloAlfabeto *simboloAlfabeto)
{
    if (simboloAlfabeto == NULL)
        return NULL;
    if (strcmp(simboloAlfabeto->Simbolo, descricaoSimbolo) == 0)
        return simboloAlfabeto;
    return BuscarSimboloAlfabeto(descricaoSimbolo, simboloAlfabeto->ProximoSimbolo);
}

AFD *InicializarAFD()
{

    AFD *afd = malloc(sizeof(AFD));
    afd->Estados = malloc(sizeof(Estado));
    afd->Transicoes = malloc(sizeof(Transicao));
    afd->Alfabeto = malloc(sizeof(SimboloAlfabeto));
    afd->QTDSimbolos = malloc(sizeof(int));
    afd->QTDEstados = (int)malloc(sizeof(int));
    afd->QTDTransicoes = malloc(sizeof(int));

    return afd;
}

//Função irá adicionar as transições em vetores somente atribuindo a descrição nos vetores
//estadoOrigem[]
void ListarTransicoes(Transicao *transicoes, char *estadoOrigem[], char *estadoDestino[], char *simbolo[], int contador)
{
    if (transicoes != NULL)
    {
        estadoOrigem[contador] = transicoes->EstadoOrigem->Descricao;
        estadoDestino[contador] = transicoes->EstadoDestino->Descricao;
        simbolo[contador] = transicoes->SimboloAlfabeto;

        ListarTransicoes(transicoes->ProximaTransicao, estadoOrigem, estadoDestino, simbolo, contador + 1);
    }
}

//Função que realizará o produto entre dois AFD's
AFD *ProdutoAFD(AFD afd1, AFD afd2)
{
    AFD *AFD_produto = InicializarAFD();

    AFD_produto->QTDEstados = (afd1.QTDEstados * afd2.QTDEstados);
    AFD_produto->QTDSimbolos = afd1.QTDSimbolos;
    AFD_produto->QTDTransicoes = (AFD_produto->QTDSimbolos * AFD_produto->QTDEstados);
    AFD_produto->Alfabeto = afd1.Alfabeto;

    Estado *estado = NULL;

    //Combinando estados do AFD1 com estados do AFD2
    for (Estado *estadoI = afd1.Estados; estadoI != NULL; estadoI = estadoI->ProximoEstado)
    {
        for (Estado *estadoJ = afd2.Estados; estadoJ != NULL; estadoJ = estadoJ->ProximoEstado)
        {
            char *descricaoEstado[STRLENGTH];
            strcpy(descricaoEstado, estadoI->Descricao);
            strcat(descricaoEstado, "&");
            strcat(descricaoEstado, estadoJ->Descricao); 

            //Estado resultante: estado1&estado2
            estado = AdicionarEstado(estado, descricaoEstado);
        }
    }

    AFD_produto->Estados = estado;

    char *EstadoTransicaoOrigemAFD1[afd1.QTDTransicoes];
    char *EstadoTransicaoOrigemAFD2[afd2.QTDTransicoes];
    char *EstadoTransicaoDestinoAFD1[afd1.QTDTransicoes];
    char *EstadoTransicaoDestinoAFD2[afd2.QTDTransicoes];
    char *SimboloTransicaoAFD1[afd1.QTDTransicoes];
    char *SimboloTransicaoAFD2[afd2.QTDTransicoes];
    
    //Listando as transiçoes em vetores, sendo que estarão em ordem certa em cada vetor
    ListarTransicoes(afd1.Transicoes, EstadoTransicaoOrigemAFD1, EstadoTransicaoDestinoAFD1, SimboloTransicaoAFD1, 0);
    ListarTransicoes(afd2.Transicoes, EstadoTransicaoOrigemAFD2, EstadoTransicaoDestinoAFD2, SimboloTransicaoAFD2, 0);

    Transicao *transicoes = NULL;

    for (int i = 0; i < afd1.QTDTransicoes; i++)
    {
        for (int j = 0; j < afd2.QTDTransicoes; j++)
        {
            //Por os vetores estarem em ordem certa
            //Somente verificar se o simbolo de transição é igual
            //para poder criar a nova transição com o casamento dos estados
            if (strcmp(SimboloTransicaoAFD1[i], SimboloTransicaoAFD2[j]) == 0)
            {
                char *descricaoEstadoOrigem[STRLENGTH];
                strcpy(descricaoEstadoOrigem, EstadoTransicaoOrigemAFD1[i]);
                strcat(descricaoEstadoOrigem, "&");
                strcat(descricaoEstadoOrigem, EstadoTransicaoOrigemAFD2[j]);

                char *descricaoEstadoDestino[STRLENGTH];
                strcpy(descricaoEstadoDestino, EstadoTransicaoDestinoAFD1[i]);
                strcat(descricaoEstadoDestino, "&");
                strcat(descricaoEstadoDestino, EstadoTransicaoDestinoAFD2[j]);

                transicoes = AdicionarTransicao(AFD_produto, transicoes, descricaoEstadoOrigem, descricaoEstadoDestino, SimboloTransicaoAFD1[i]);
            }
        }
    }

    AFD_produto->Transicoes = transicoes;

    //Definindo estado inicial do AFD resultante
    Estado *estadoInicialAFD1 = RetornaEstadoInicial(afd1.Estados);
    Estado *estadoInicialAFD2 = RetornaEstadoInicial(afd2.Estados);

    char *estadoInicialProduto[STRLENGTH];
    strcpy(estadoInicialProduto, estadoInicialAFD1->Descricao);
    strcat(estadoInicialProduto, "&");
    strcat(estadoInicialProduto, estadoInicialAFD2->Descricao);

    BuscarEstado(estadoInicialProduto, AFD_produto->Estados)->Inicial = 1;

    return AFD_produto;
}

Estado *RetornaEstadoInicial(Estado *estados)
{
    Estado *estadoInicial;
    for (Estado *estado = estados; estado != NULL; estado = estado->ProximoEstado)
    {
        if (estado->Inicial == 1)
        {
            estadoInicial = estado;
            break;
        }
    }

    return estadoInicial;
}

Estado *ListarEstadosFinaisOuNaoFinais(Estado *estados, Estado *result, int EFinal)
{
    if (estados == NULL)
        return result;

    if (estados->Final == EFinal)
    {
        Estado *e = (Estado *)malloc(sizeof(Estado));

        strcpy(e->Descricao, estados->Descricao);
        e->Final = 1;
        e->Inicial = estados->Inicial;
        e->ProximoEstado = ListarEstadosFinaisOuNaoFinais(estados->ProximoEstado, result, EFinal);

        return e;
    }

    return ListarEstadosFinaisOuNaoFinais(estados->ProximoEstado, result, EFinal);
}