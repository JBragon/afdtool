afdtool: main.o intersecao.o  uniao.o reconhecer.o complemento.o  util.o visualizar.o  AFDFuncoes.o 
	gcc main.o intersecao.o  uniao.o reconhecer.o complemento.o  util.o visualizar.o  AFDFuncoes.o  -o afdtool

main.o: main.c src/header.h
	gcc -c main.c

AFDFuncoes.o: src/AFD/AFDFuncoes.c src/header.h
	gcc -c src/AFD/AFDFuncoes.c

util.o: src/util.c
	gcc -c src/util.c

visualizar.o: src/operacoes/visualizar.c
	gcc -c src/operacoes/visualizar.c

complemento.o:  src/operacoes/complemento.c
	gcc -c  src/operacoes/complemento.c

intersecao.o: src/operacoes/intersecao.c
	gcc -c  src/operacoes/intersecao.c

uniao.o: src/operacoes/uniao.c
	gcc -c src/operacoes/uniao.c

reconhecer.o: src/operacoes/reconhecer.c
	gcc -c src/operacoes/reconhecer.c

clean:
	rm *.o */*.dot */*.svg afdtool
