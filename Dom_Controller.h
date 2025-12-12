//DOM-BGJP-Controller.h - Projeto Dominó
//23/08/2025 - Grupo: BGJP
//Bruno Barreto Ferreira Leão
//Guilherme Pereira de Rivoredo
//João Paulo Vieira Costa
//Pedro Henrique Freire Pereira

#ifndef Dom_BGJP_Controller_h
#define Dom_BGJP_Controller_h
//funções usadas no jogo
void embaralharPecas();
void prepararJogo();
char primeiroLance();
void trocarJogador();
void iniciaJogo();
void verificaFimDeJogo();
void jogarPeca();
void comprarPeca();
void passarVez();


void jogar();
void jogarSalvo();
void jogadaMaquina();

// novos protótipos para salvar/carregar
int salvarJogo(const char *nomeArquivo);   // retorna 0 em sucesso, !=0 em erro
int carregarJogo(const char *nomeArquivo); // retorna 0 em sucesso, !=0 em erro


#endif

