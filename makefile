all: afdtool
	make clean
	make afdtool

afdtool: main.c
	gcc -g -Wall -o afdtool main.c src/header.h src/util.c src/AFD/AFDFuncoes.c src/operacoes/visualizar.c src/operacoes/complemento.c src/operacoes/intersecao.c src/operacoes/uniao.c src/operacoes/reconhecer.c

clean:
	del afdtool