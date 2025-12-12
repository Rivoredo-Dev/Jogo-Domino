//DOM-BGJP-View.cpp - Projeto Dominó
//29/08/2025 - Grupo: BGJP
//Bruno Barreto Ferreira Leão
//Guilherme Pereira de Rivoredo
//João Paulo Vieira Costa
//Pedro Henrique Freire Pereira

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Dom_BGJP_View.h"


//Faz a apresentação das peças na tela
void apresentarPecas()
{
    printf("Pecas:");
	for (int i = 0; i < 28; i++)
	{
        printf("[%d|%d] ", pecas[i].lado1, pecas[i].lado2);
    }
    printf("\n\n");

}

void menuInicial() {
    int opcao;

    while (1) {
        limpatela();
        printf(" ================================================\n");
        printf("|                                                |\n");
        printf("|                 MENU PRINCIPAL                 |\n");
        printf("|                                                |\n");
        printf(" ================================================\n");

        printf("1. Iniciar Novo Jogo - Jogador 1 vs Jogador 2\n");
        printf("2. Iniciar Novo Jogo - Jogador 1 vs Maquina\n");
        printf("3. Voltar ao jogo salvo (memoria)\n");
        printf("4. Carregar jogo salvo em arquivo\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1: // J1 vs J2
                contraMaquina = 0;
                jogar();
                break;

            case 2: // J1 vs Máquina
                contraMaquina = 1;
                jogar();
                break;

            case 3: // Retomar salvo
                if (qtmesa == 0) {
                    limpatela();
                    printf("Nao ha jogo salvo no momento. Pressione ENTER para voltar ao menu.\n");
                    esperarEnter();
                } else {
                    jogarSalvo();
                }
                break;
            case 4:
            {
                char filename[256];
                limpatela();
                printf("Nome do arquivo para carregar: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    // remove newline
                    char *p = filename;
                    while (*p && *p != '\n') p++;
                    *p = '\0';
                    int res = carregarJogo(filename);
                    if (res == 0) {
                        limpatela();
                        printf("Arquivo '%s' carregado com sucesso! Retornando ao jogo...\n\n", filename);
                        apresentarMesa();
                        iniciaJogo();
                        menuJogo();
                    } else {
                        limpatela();
                        printf("Falha ao carregar '%s' (codigo %d). Pressione ENTER para voltar ao menu.\n", filename, res);
                        esperarEnter();
                    }
                }
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                exit(0);

            default:
                printf("Opcao invalida. Pressione ENTER para voltar ao menu...\n");
                esperarEnter();
                break;
        }
    }
}


//menu de controle das ações do jogador
void menuJogo()
{
    if (contraMaquina && jogatual == '2') {
        jogadaMaquina();   // Máquina joga
        return;            // Sai, o próximo turno já será do jogador
    }
    
    char opcao;
    do {
        printf("J - Jogar\n");
        printf("C - Comprar\n");
        printf("P - Passar a vez\n");
        printf("V - Visualizacao das suas pecas (Mostrar/Esconder)\n");
        printf("G - Gravar Jogo em arquivo\n");
        printf("L - Carregar jogo de arquivo (substitui estado atual)\n");
        printf("S - Sair\n");
        printf("opcao: ");
        scanf("%c",&opcao);
        limpaBuffer();
        printf("\n");

        opcao = toupper(opcao);

        switch(opcao)
        {
            case 'J': jogarPeca(); break;
            case 'C': comprarPeca(); break;
            case 'P': passarVez(); break;
            case 'S': limpatela(); menuInicial(); break;
            case 'V': alternarVisualizacaoPecas(); break;
            case 'G': // salvar para arquivo
            {
                char filename[256];
                printf("Nome do arquivo para salvar: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    // remove newline
                    char *p = filename;
                    while (*p && *p != '\n') p++;
                    *p = '\0';
                    int res = salvarJogo(filename);
                    if (res == 0) {
                        printf("Jogo salvo em '%s' com sucesso.\n", filename);
                    } else {
                        printf("Falha ao salvar em '%s' (codigo %d).\n", filename, res);
                    }
                }
                printf("Pressione ENTER para continuar...\n");
                esperarEnter();
                limpatela();
                apresentarMesa();
                iniciaJogo();
                break;
            }
            case 'L': // carregar arquivo e retomar
            {
                char filename[256];
                printf("Nome do arquivo para carregar: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    // remove newline
                    char *p = filename;
                    while (*p && *p != '\n') p++;
                    *p = '\0';
                    int res = carregarJogo(filename);
                    if (res == 0) {
                        limpatela();
                        printf("Arquivo '%s' carregado com sucesso! Retomando jogo...\n\n", filename);
                        apresentarMesa();
                        iniciaJogo();
                    } else {
                        limpatela();
                        printf("Falha ao carregar '%s' (codigo %d). Pressione ENTER.\n", filename, res);
                        esperarEnter();
                        limpatela();
                        apresentarMesa();
                        iniciaJogo();
                    }
                }
                break;
            }
            default:
                limpatela();
                printf("Opcao invalida. Tente novamente.\n\n");
                apresentarMesa();
                iniciaJogo();
                menuJogo();
                break;
        }
    } while(opcao != 'S');
}

//Faz a apresentação da mesa,ou seja,as peças que foram jogadas e as extremidades da mesa
void apresentarMesa() {
    printf("\n=============================================================================================================\n");
	printf("Mesa: ");
    for (int i = 0; i < qtmesa; i++)
	{
        printf("[%d|%d] ", mesas[i].ladoE, mesas[i].ladoD);
    }
    printf("\n=============================================================================================================");
    printf("\n\n");
    printf("Extremidades: %d (esquerda) - %d (direita)\n\n", mesaE, mesaD);
}


//Apresenta mensagens Solicitadas
void apresentarMensagem(char mens[100])
{
	printf("%s\n",mens);
}

//Limpa a Tela
void limpatela()
{
	system("cls");
}

//Limpa o buffer do teclado
void limpaBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarEnter()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

//esconde ou mostra as peças do jogador
void alternarVisualizacaoPecas()
{
    if (jogatual == '1')
    {
        mostrarPecasJ1 = !mostrarPecasJ1;
        printf("Visualizacao do Jogador 1 %s.\n", mostrarPecasJ1 ? "ATIVADA" : "DESATIVADA");
    }
    else
    {
        mostrarPecasJ2 = !mostrarPecasJ2;
        printf("Visualizacao do Jogador 2 %s.\n", mostrarPecasJ2 ? "ATIVADA" : "DESATIVADA");
    }
    printf("Pressione ENTER para atualizar...\n");
    esperarEnter();
    limpatela();
    apresentarMesa();
    iniciaJogo();
    menuJogo();
}

//mostra a jogada da maquina
void mostrarJogadaMaquina(char lado, int l1, int l2, int acao) 
{
    printf("--- A MAQUINA JOGOU ---\n");
    if (acao == 0)
        printf("Maquina jogou [%d|%d] na %s!\n", l1, l2, (lado=='E')?"esquerda":"direita");
    else if (acao == 1)
        printf("Maquina comprou uma peca.\n");
    else
        printf("Maquina passou a vez.\n");
    
    printf("\n");
}





