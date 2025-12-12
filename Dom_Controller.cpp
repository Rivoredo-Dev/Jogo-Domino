//DOM-BGJP-Controller.cpp - Projeto Dominó
//23/08/2025 - Grupo: BGJP
//Bruno Barreto Ferreira Leão
//Guilherme Pereira de Rivoredo
//João Paulo Vieira Costa
//Pedro Henrique Freire Pereira

#include <stdlib.h>
#include <time.h>
#include "Dom_BGJP_Controller.h"
#include "Dom_BGJP_View.cpp"

//Faz o embaralhamento das peças
void embaralharPecas()
{
    static int initialized = 0;
    if (!initialized)
	{
        srand(time(NULL)); //usa o tempo atual como base para gerar embaralhamentos diferentes
        initialized = 1;
    }

    for (int i = 0; i < 28; i++)
	{
        int r = rand() % 28;
        peca temp = pecas[i];
        pecas[i] = pecas[r];
        pecas[r] = temp;
    }
}

//faz o preparo das peças e da mesa,afim de evitar erros
void prepararJogo()
{
	embaralharPecas();

	//Define o status de todas as peças para Null,ou seja,a peça NAO pertence a nenhum jogador
	for(int i = 0; i < 28; i++)
	{
		pecas[i].status=NULL;
	}

	//limpa a mesa
	for(int i = 0; i < 28; i++)
    {
	    mesas[i].ladoD = -1;
	    mesas[i].ladoE = -1;
    }

	//distribuição das peças para os jogadores
	for(int i=0;i<7;i++) //jogador 1
	{
		pecas[i].status='1';
	}

	for(int i=7;i<14;i++) //jogador 2
	{
		pecas[i].status='2';
	}
}

//decide com base nos criterios fornecidos,qual jogador fará o primeiro lance
char primeiroLance()
{
    // Maiores duplas (ex: 6|6, 5|5) encontradas para cada jogador
    int maiorIgualJ1 = -1;
    int maiorIgualJ2 = -1;

    // Maiores somas (ex: 6+5, 5+4) encontradas para cada jogador
    int maiorSomaJ1 = -1;
    int maiorSomaJ2 = -1;

    // Índice das melhores peças (por dupla ou soma) para cada jogador
    int indicePecaJ1 = -1;
    int indicePecaJ2 = -1;


    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == '1') // Peça do Jogador 1
        {
            // Verifica se é uma dupla (lado1 == lado2)
            if (pecas[i].lado1 == pecas[i].lado2)
            {
                if (pecas[i].lado1 > maiorIgualJ1)
                {
                    maiorIgualJ1 = pecas[i].lado1;
                    indicePecaJ1 = i;
                }
            }

            // Verifica a maior soma entre lado1 e lado2
            int soma = pecas[i].lado1 + pecas[i].lado2;
            if (soma > maiorSomaJ1)
            {
                maiorSomaJ1 = soma;

                // Só atualiza o índice se ainda não houver uma peça dupla válida
                if (indicePecaJ1 == -1)
                    indicePecaJ1 = i;
            }
        }
        else if (pecas[i].status == '2') // Peça do Jogador 2
        {
            if (pecas[i].lado1 == pecas[i].lado2)
            {
                if (pecas[i].lado1 > maiorIgualJ2)
                {
                    maiorIgualJ2 = pecas[i].lado1;
                    indicePecaJ2 = i;
                }
            }

            int soma = pecas[i].lado1 + pecas[i].lado2;
            if (soma > maiorSomaJ2)
            {
                maiorSomaJ2 = soma;

                if (indicePecaJ2 == -1)
                    indicePecaJ2 = i;
            }
        }
    }

    // Comparação entre as maiores duplas
    if (maiorIgualJ1 > maiorIgualJ2)
    {
        pecas[indicePecaJ1].status = 'M';
        mesas[0].ladoE = pecas[indicePecaJ1].lado1;
        mesas[0].ladoD = pecas[indicePecaJ1].lado2;


        mesaE = mesas[0].ladoE;
        mesaD = mesas[0].ladoD;
        qtmesa = 1;

        return '1';
    }
    else if (maiorIgualJ2 > maiorIgualJ1)
    {
        pecas[indicePecaJ2].status = 'M';
        mesas[0].ladoE = pecas[indicePecaJ2].lado1;
        mesas[0].ladoD = pecas[indicePecaJ2].lado2;

        mesaE = mesas[0].ladoE;
        mesaD = mesas[0].ladoD;
        qtmesa = 1;

        return '2';
    }

    // Se nenhuma dupla foi encontrada ou se estão empatadas, compara maior soma
    if (maiorSomaJ1 > maiorSomaJ2)
    {
        pecas[indicePecaJ1].status = 'M';
        mesas[0].ladoE = pecas[indicePecaJ1].lado1;
        mesas[0].ladoD = pecas[indicePecaJ1].lado2;

        mesaE = mesas[0].ladoE;
        mesaD = mesas[0].ladoD;
        qtmesa = 1;

        return '1';
    }
    else if (maiorSomaJ2 > maiorSomaJ1)
    {
        pecas[indicePecaJ2].status = 'M';
        mesas[0].ladoE = pecas[indicePecaJ2].lado1;
        mesas[0].ladoD = pecas[indicePecaJ2].lado2;

        mesaE = mesas[0].ladoE;
        mesaD = mesas[0].ladoD;
        qtmesa = 1;

        return '2';
    }

    // Caso especial: tudo igual, mas ainda tem uma peça do jogador 1
    if (indicePecaJ1 != -1)
    {
        pecas[indicePecaJ1].status = 'M';
        mesas[0].ladoE = pecas[indicePecaJ1].lado1;
        mesas[0].ladoD = pecas[indicePecaJ1].lado2;

        mesaE = mesas[0].ladoE;
        mesaD = mesas[0].ladoD;
        qtmesa = 1;

        return '1';
    }

    // Retorno padrão de segurança
    return '1';
}


//faz a troca de turnos entre os jogadores
void trocarJogador()
{
    if (jogatual == '1')
        jogatual = '2';
    else
        jogatual = '1';
}


//Mostra as peças do jogador da vez
void iniciaJogo() {
    
	if(contraMaquina==0 || (contraMaquina==1 && jogatual=='1'))
	printf("\nVez do Jogador %c de jogar\n\n", jogatual);

    printf("PECAS DO JOGADOR %c:\n", jogatual);

    int letra = 'A';
    int mostrar = (jogatual == '1') ? mostrarPecasJ1 : mostrarPecasJ2;

    for (int i = 0; i < 28; i++) {
        if (pecas[i].status == jogatual) {
            if (mostrar)
                printf("%c. [%d|%d]  ", letra, pecas[i].lado1, pecas[i].lado2);
            else
                printf("%c. [*|*]  ", letra); // ocultar valores
            letra++;
        }
    }
    printf("\n\n");
}




//Jogo
void jogar()
{
	prepararJogo();
	limpatela();

    jogatual = primeiroLance();
    jogoEmAndamento = 1; //Marca que existe jogo em andamento
    
	if(contraMaquina == 1 && jogatual=='2')
	    printf("A Maquina fez o primeiro lance!\n\n");
	else if(contraMaquina == 1 && jogatual=='1'){
	            printf("O jogador 1 fez o primeiro lance!\n\n");
                trocarJogador();
                jogadaMaquina();
		   }
	else 
	    printf("O jogador %c fez o primeiro lance!\n\n", jogatual);

	apresentarMesa();
    trocarJogador();
    iniciaJogo();
    menuJogo();
}

//executa a açao de jogar a peca
void jogarPeca()
{
    char letraEscolhida;
    printf("Escolha a letra da peca que deseja jogar: ");
    scanf(" %c", &letraEscolhida);
    limpaBuffer();

    letraEscolhida = toupper(letraEscolhida);
    int pos = letraEscolhida - 'A';

    // Mapear a letra para a posição correta do vetor de peças do jogador
    int contador = 0;
    int indicePeca = -1;
    for (int i = 0; i < 28; i++)
	{
        if (pecas[i].status == jogatual)
		{
            if (contador == pos)
			{
                indicePeca = i;
                break;
            }
            contador++;
        }
    }

    if (indicePeca == -1) {
        limpatela();
        printf("Opcao invalida. Tente novamente.\n\n");
        apresentarMesa();
		iniciaJogo();
		menuJogo();
        return;
    }

    int l1 = pecas[indicePeca].lado1;
    int l2 = pecas[indicePeca].lado2;

    int podeEsquerda = (l1 == mesaE || l2 == mesaE);
    int podeDireita  = (l1 == mesaD || l2 == mesaD);

    //faz a verificação se a peça pode ser jogada nas duas extremidades
	if (!podeEsquerda && !podeDireita)
    {
        limpatela();
        printf("Essa peca nao pode ser jogada nas extremidades da mesa.\n\n");
        apresentarMesa();
        iniciaJogo();
		menuJogo();
        return;
    }

    //faz a verificação se a peça pode ser jogada nas duas extremidades
    char lado;
    if (podeEsquerda && podeDireita)
    {
        printf("Deseja jogar na esquerda (E) ou direita (D)? ");
        scanf(" %c", &lado);
        limpaBuffer();
        lado = toupper(lado);
    }
    else if (podeEsquerda)
    {
        lado = 'E';
    }
    else
    {
        lado = 'D';
    }

    // Jogar a peça no lado escolhido
    if (lado == 'D')
    {
        if (l1 != mesaD)
        {
            // inverter
            int temp = l1;
            l1 = l2;
            l2 = temp;
        }

        // Coloca no final da mesa
        mesas[qtmesa].ladoE = l1;
        mesas[qtmesa].ladoD = l2;
        mesaD = l2;
    }
    else // lado == 'E'
    {
        if (l2 != mesaE)
        {
            // inverter
            int temp = l1;
            l1 = l2;
            l2 = temp;
        }

        // Desloca a mesa para a direita
        for (int i = qtmesa; i > 0; i--)
        {
            mesas[i] = mesas[i - 1];
        }

        mesas[0].ladoE = l1;
        mesas[0].ladoD = l2;
        mesaE = l1;
    }

    // Atualiza a peça
    pecas[indicePeca].status = 'M';
    qtmesa++;

    limpatela();
    printf("Jogador %c jogou [%d|%d] na %s!\n\n", jogatual, l1, l2, (lado == 'E') ? "esquerda" : "direita");
    trocarJogador();
    if(contraMaquina==0)
	{
	apresentarMesa();
    iniciaJogo();
	}
	verificaFimDeJogo();
    menuJogo();
}


void comprarPeca() {
    int comprou = 0;
    limpatela();
	for (int i = 0; i < 28; i++) {
        if (pecas[i].status == 0) {  // 0 = no monte
            pecas[i].status = jogatual; // vai pro jogador atual
            printf("Jogador %c comprou a peca [%d|%d]\n",
                   jogatual, pecas[i].lado1, pecas[i].lado2);
            comprou = 1;
            break;
        }
    }
    if (!comprou) {
        printf("Nao ha mais pecas para comprar!\n");
    }

    apresentarMesa();

    iniciaJogo();
    menuJogo();
}


//passa a vez ao proximo jogador caso nao hajam peças jogaveis na mao do jogador e nao hajam peças no monte
void passarVez()
{
    int podeJogar = 0;
    int podeComprar = 0;

    // Verifica se o jogador atual possui alguma peça jogável
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == jogatual)
        {
            if (pecas[i].lado1 == mesaE || pecas[i].lado1 == mesaD ||
                pecas[i].lado2 == mesaE || pecas[i].lado2 == mesaD)
            {
                podeJogar = 1;
                break;
            }
        }
    }

    // Verifica se ainda há peças disponíveis para compra
    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == 0)
        {
            podeComprar = 1;
            break;
        }
    }

    // toma a decisão com base nas duas verificações
    if (podeJogar)
    {
        limpatela();
        printf("\nVoce ainda possui pecas jogaveis. Nao pode passar a vez.\n\n");
        apresentarMesa();
		iniciaJogo();
        verificaFimDeJogo();
    }
    else if (podeComprar)
    {
        limpatela();
        printf("\nVoce nao pode passar enquanto ainda ha pecas para comprar!\n\n");
        iniciaJogo();
        verificaFimDeJogo();
        apresentarMesa();
    }
    else
    {
        // Jogador pode passar legitimamente
        trocarJogador();
        limpatela();
        printf("\nNenhuma jogada possivel e o monte acabou. Passando a vez.\n\n");
        iniciaJogo();
        verificaFimDeJogo();
        apresentarMesa();
    }
}

//Acessar um jogo interrompido anteriormente
void jogarSalvo()
{
	limpatela();
    printf("Jogo retomado com suceso!\n\n");
	apresentarMesa();
    iniciaJogo();
    menuJogo();
}

//após cada ação executada por um dos jogadores,as condiçoes de fim de jogo sao verificadas
void verificaFimDeJogo()
{
    int pecasJ1 = 0, pecasJ2 = 0;
    int pontosJ1 = 0, pontosJ2 = 0;
    int podeJogarJ1 = 0, podeJogarJ2 = 0;
    int pecasNoMonte = 0;

    for (int i = 0; i < 28; i++)
    {
        if (pecas[i].status == '1')
        {
            pecasJ1++;
            pontosJ1 += pecas[i].lado1 + pecas[i].lado2;

            if (pecas[i].lado1 == mesaE || pecas[i].lado1 == mesaD ||
                pecas[i].lado2 == mesaE || pecas[i].lado2 == mesaD)
                podeJogarJ1 = 1;
        }
        else if (pecas[i].status == '2')
        {
            pecasJ2++;
            pontosJ2 += pecas[i].lado1 + pecas[i].lado2;

            if (pecas[i].lado1 == mesaE || pecas[i].lado1 == mesaD ||
                pecas[i].lado2 == mesaE || pecas[i].lado2 == mesaD)
                podeJogarJ2 = 1;
        }
        else if (pecas[i].status == 0) // peças no monte
        {
            pecasNoMonte++;
        }
    }

    // Caso 1: Algum jogador ficou sem peças
    if (pecasJ1 == 0 || pecasJ2 == 0)
    {
        limpatela();

        if (pecasJ1 == 0)
            printf("FIM DE JOGO! Jogador 1 venceu! Zerou suas pecas.PARABENS!!!\n");
        else
        {
        	if(contraMaquina == 1)
        	   printf("FIM DE JOGO! A Maquina venceu! Zerou suas pecas.Que tal tentar de novo?\n");
		    else
			   printf("FIM DE JOGO! Jogador 2 venceu! Zerou suas pecas.PARABENS!!!\n");
		}
            

        esperarEnter();
        menuInicial();
        return;
    }

    // Caso 2: Ambos não podem jogar e monte está vazio
    if (!podeJogarJ1 && !podeJogarJ2 && pecasNoMonte == 0)
    {
        limpatela();
        printf("FIM DE JOGO! O jogo travou. Ninguem pode jogar e o monte acabou.\n");
        printf("Pontos:\nJogador 1: %d\n", pontosJ1);
        if (contraMaquina == 1)
            printf("Maquina: %d\n", pontosJ2);
        else
            printf("Jogador 2: %d\n", pontosJ2);

        if (pontosJ1 < pontosJ2)
            printf("Jogador 1 venceu por menor soma de pontos nas pecas.\n");
        else if (pontosJ2 < pontosJ1) 
		     {
                if (contraMaquina == 1)
                    printf("A Maquina venceu por menor soma de pontos nas pecas.\n");
                else
                    printf("Jogador 2 venceu por menor soma de pontos nas pecas.\n");
             }
            else
             printf("Empate!\n");


        esperarEnter();
        menuInicial();
        return;
    }

    // Caso contrário, o jogo continua
}

// Jogada da maquina
void jogadaMaquina() {
    int jogadasPossiveis[28];
    int count = 0;
    int pecasCompradas = 0;

    // Loop: continua comprando enquanto não houver peça jogável
    while (1) {
        // Busca peças jogáveis da máquina
        count = 0;
        for (int i = 0; i < 28; i++) {
            if (pecas[i].status == '2') {
                int l1 = pecas[i].lado1;
                int l2 = pecas[i].lado2;
                if (l1 == mesaE || l2 == mesaE || l1 == mesaD || l2 == mesaD) {
                    jogadasPossiveis[count++] = i;
                }
            }
        }

        if (count > 0) break; // encontrou peça jogável, sai do loop

        // Se não tem peça jogável, tenta comprar
        int comprou = 0;
        for (int i = 0; i < 28; i++) {
            if (pecas[i].status == 0) { // peça no monte
                pecas[i].status = '2';
                pecasCompradas++;
                comprou = 1;
                break;
            }
        }

        if (!comprou) {
            // Não há mais peças para comprar
            mostrarJogadaMaquina(' ', 0, 0, 2); // passou a vez
            trocarJogador();
            apresentarMesa();
            iniciaJogo();
            verificaFimDeJogo();
            menuJogo();
            return;
        }
    }

    // Agora há peças jogáveis
    int idx = jogadasPossiveis[rand() % count];
    int l1 = pecas[idx].lado1, l2 = pecas[idx].lado2;
    char lado;

    int podeEsquerda = (l1 == mesaE || l2 == mesaE);
    int podeDireita  = (l1 == mesaD || l2 == mesaD);

    if (podeEsquerda && podeDireita) lado = (rand() % 2) ? 'E' : 'D';
    else if (podeEsquerda) lado = 'E';
    else lado = 'D';

    // Coloca a peça na mesa
    if (lado == 'D') {
        if (l1 != mesaD) { int temp = l1; l1 = l2; l2 = temp; }
        mesas[qtmesa].ladoE = l1; mesas[qtmesa].ladoD = l2;
        mesaD = l2;
    } else {
        if (l2 != mesaE) { int temp = l1; l1 = l2; l2 = temp; }
        for (int i = qtmesa; i > 0; i--) mesas[i] = mesas[i-1];
        mesas[0].ladoE = l1; mesas[0].ladoD = l2;
        mesaE = l1;
    }

    pecas[idx].status = 'M';
    qtmesa++;

    // Mostra quantas peças comprou antes de jogar
    if (pecasCompradas > 0) {
        printf("A maquina comprou %d peca(s) antes de jogar.\n", pecasCompradas);
    }

    mostrarJogadaMaquina(lado, l1, l2, 0); // 0 = jogou peça

    // Troca turno para jogador humano
    trocarJogador();

    // Atualiza interface
    apresentarMesa();
    iniciaJogo();
    verificaFimDeJogo();
    menuJogo();
}





// Salva o estado atual do jogo em um arquivo texto.
// Retorna 0 em sucesso, !=0 em erro.
int salvarJogo(const char *nomeArquivo)
{
    FILE *f = fopen(nomeArquivo, "w");
    if (!f) {
        return 1;
    }

    // Cabeçalho: qtmesa jogatual mesaE mesaD mostrarPecasJ1 mostrarPecasJ2 contraMaquina
    fprintf(f, "%d %d %d %d %d %d %d\n", qtmesa, (int)jogatual, mesaE, mesaD, mostrarPecasJ1, mostrarPecasJ2, contraMaquina);

    // Salva as 28 peças: lado1 lado2 status (status como int)
    for (int i = 0; i < 28; i++) {
        fprintf(f, "%d %d %d\n", pecas[i].lado1, pecas[i].lado2, (int)pecas[i].status);
    }

    // Salva as 28 entradas da mesa (ladoE ladoD)
    for (int i = 0; i < 28; i++) {
        fprintf(f, "%d %d\n", mesas[i].ladoE, mesas[i].ladoD);
    }

    fclose(f);
    return 0;
}



// Carrega estado do arquivo salvo.
// Retorna 0 em sucesso, !=0 em erro.
int carregarJogo(const char *nomeArquivo)
{
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        return 1;
    }

    int jogatual_int;
    if (fscanf(f, "%d %d %d %d %d %d %d\n", &qtmesa, &jogatual_int, &mesaE, &mesaD, &mostrarPecasJ1, &mostrarPecasJ2, &contraMaquina) != 7)
    {
        fclose(f);
        return 2; // formato inválido
    }
    jogatual = (char)jogatual_int;

    // Lê as 28 peças
    for (int i = 0; i < 28; i++) {
        int lado1, lado2, status_int;
        if (fscanf(f, "%d %d %d\n", &lado1, &lado2, &status_int) != 3) {
            fclose(f);
            return 3;
        }
        pecas[i].lado1 = lado1;
        pecas[i].lado2 = lado2;
        pecas[i].status = (char)status_int;
    }

    // Lê as 28 mesas
    for (int i = 0; i < 28; i++) {
        int le, ld;
        if (fscanf(f, "%d %d\n", &le, &ld) != 2) {
            fclose(f);
            return 4;
        }
        mesas[i].ladoE = le;
        mesas[i].ladoD = ld;
    }

    fclose(f);
    return 0;
}







