//DOM-BGJP-Model.cpp - Projeto Dominó
//23/08/2025 - Grupo: BGJP
//Bruno Barreto Ferreira Leão
//Guilherme Pereira de Rivoredo
//João Paulo Vieira Costa
//Pedro Henrique Freire Pereira

#include "Dom_BGJP_Model.h"
#define MAX_NUM 6

//Matrizes que estão no Model.h
peca pecas[28];
mesa mesas[28];

int qtmesa = 0; //quantidade de peças na mesa
char jogatual;  //jogador atual que irá jogar
int mesaE = -1; //extremidade esquerda de mesa
int mesaD = -1; //extremidade direita de mesa
int mostrarPecasJ1 = 1; // 1 = mostrar, 0 = esconder
int mostrarPecasJ2 = 1;
int contraMaquina = 0;  // 0 = jogador 2 humano, 1 = máquina


//Cria as peças para o jogo
void criarPecas()
{
    int index = 0;
    for (int i = 0; i <= MAX_NUM; i++)
	{
        for (int j = i; j <= MAX_NUM; j++)
		{
            pecas[index].lado1 = i;
            pecas[index].lado2 = j;
            index++;
        }
    }
}
int jogoEmAndamento = 0;
