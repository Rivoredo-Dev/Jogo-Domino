//DOM-BGJP-Model.h - Projeto Dominó
//23/08/2025 - Grupo: BGJP
//Bruno Barreto Ferreira Leão
//Guilherme Pereira de Rivoredo
//João Paulo Vieira Costa
//Pedro Henrique Freire Pereira

#ifndef Dom_BGJP_Model_h
#define Dom_BGJP_Model_h

//Estrutura que armazena os dados das Peças
typedef struct {
    int lado1;
    int lado2;
    char status;
} peca;

//Estrutura que armazena os dodos da mesa
typedef struct{
	int ladoE;
	int ladoD;
}mesa;

//Variaveis globais
extern int qtmesa; //quantidade de peças na mesa
extern char jogatual; //jogador atual que irá jogar
extern int mesaE; //extremidade esquerda de mesa
extern int mesaD; //extremidade direita de mesa
extern int mostrarPecasJ1 ; // mostrar ou esconder peças
extern int mostrarPecasJ2 ;
extern int contraMaquina;  // 0 = jogador 2 humano, 1 = máquina


extern peca pecas[28]; //Matriz que armazena as peças
extern mesa mesas[28]; //matriz que cuida das peças que estão na mesa



void criarPecas();

#endif

