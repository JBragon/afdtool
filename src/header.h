#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//ENUMS

typedef enum
{
    COMPLEMENTO = 1,
    VISUALIZAR = 2,
    INTERSECAO = 3,
    UNIAO = 4,
    MINIMIZACAO = 5,
    RECONHECIMENTO = 6,
    AJUDA = 7
} OperacoesEnum;

//STRUCTS

#define STRLENGTH 100

typedef struct Estado_struct {
    char Descricao[STRLENGTH];
    int Final;
    int Inicial;
    struct Estado_struct *ProximoEstado;
} Estado;
typedef struct Estado_struct Estado;

typedef struct Transicao_struct {
    struct Estado_struct *EstadoOrigem;
    struct Estado_struct *EstadoDestino;
    struct SimboloAlfabeto_struct *SimboloAlfabeto;
    struct Transicao_struct *ProximaTransicao;
} Transicao;

typedef struct SimboloAlfabeto_struct {
    char Simbolo[STRLENGTH];
    struct SimboloAlfabeto_struct *ProximoSimbolo;
} SimboloAlfabeto;

typedef struct AFD_struct {
    struct Estado_struct *Estados;
    struct Transicao_struct *Transicoes;
    struct SimboloAlfabeto_struct *Alfabeto;
    int QTDSimbolos;
    int QTDEstados;
    int QTDTransicoes;
    int QTDEstadosFinais;
} AFD;

//util.c
int BuscaOperacao(char *operacao);
void CriarArquivo(AFD *afd, char *NomeArquivoDeSaida);
void ImprimirAjuda();
void ValidaArgumentos(int argc);

//Funçoes AFD
SimboloAlfabeto* BuscarSimboloAlfabeto(char *descricaoSimbolo, SimboloAlfabeto *simboloAlfabeto);
SimboloAlfabeto* AdicionarSimbolo(SimboloAlfabeto *symbol, char *content);
Estado* BuscarEstado(char *descricao, Estado *estado);
Estado* RetornaEstadoInicial(Estado *estado);
Estado* ListarEstadosFinaisOuNaoFinais(Estado *estados, Estado *result, int EFinal);
Estado* AdicionarEstado(Estado *state, char *name);
Transicao* AdicionarTransicao(AFD *afd, Transicao *transicao, char *origem, char *destino, char *simbolo);
AFD *LerArquivo(char *nomeArquivo);
AFD *InicializarAFD();
AFD *ImportarAlfabeto(AFD *afd, char *linha[STRLENGTH], FILE *arquivo);
AFD *ImportarEstados(AFD *afd, char *linha[STRLENGTH], FILE *arquivo);
AFD *ImportarTransicoes(AFD *afd, char *linha[STRLENGTH], FILE *input);
Estado *AdicionarEstado(Estado *estado, char *descricao);
Estado *BuscarEstado(char *descricao, Estado *estado);
AFD *ProdutoAFD(AFD afd1, AFD afd2);
Estado *RetornaEstadoDestino(AFD *afd, Estado *estado, char simboloAlfabeto);
Transicao *BuscaTransicaoValida(Transicao *transicoes, Estado *estado, char simboloAlfabeto);

//operacoes
void ConverterAFDParaDot(char *nomeArquivoEntrada, char *nomeArquivoSaida);
void ComplementoAFD(char *nomeArquivoEntrada, char *nomeArquivoSaida);
void IntersecaoAFD(char *nomeArquivoAFD1, char *nomeArquivoAFD2, char *nomeArquivoSaida);
void UniaoAFD(char *nomeArquivoAFD1, char *nomeArquivoAFD2, char *nomeArquivoSaida);
void ReconhecerPalavra(char *nomeArquivoAFD, char *nomeArquivoPalavras, char *nomeArquivoSaida);

#endif