#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <locale.h>

using namespace std;

void limpaTela() {
    system("CLS");
}

void sobreJogo() {
    cout << "Este jogo foi feito por Thiago Rosario Souza no ano de 2023 em C++, criado como forma de divertir os usuários. Divirta-se jogando!\n";
}

void instrucoes() {
    cout << "O Jogo da Velha é um jogo simples e clássico jogado em um tabuleiro 3x3. As regras são as seguintes:";

 cout << "**Tabuleiro:** O jogo é jogado em um tabuleiro quadrado dividido em nove espaços.\n";

 cout << "**Jogadores:** Dois jogadores participam, um utilizando 'X' e o outro 'O'.\n";

 cout << "**Objetivo:** O objetivo é formar uma linha contínua de três símbolos consecutivos na horizontal, vertical ou diagonal.\n";

 cout << "**Turnos:** Os jogadores alternam turnos, marcando um espaço vazio por vez com seu símbolo.\n";

 cout << "**Vitória:** O jogador que primeiro completar uma linha de três de seus símbolos é o vencedor.\n";

 cout << "**Empate:** Se todas as nove posições são preenchidas e nenhum jogador formou uma linha, o jogo é declarado empate.\n";

 cout << "**Regras de Movimento:** Cada jogador deve escolher uma posição vazia para marcar a cada turno. Não é permitido sobrepor o símbolo do adversário.\n";

 cout << "**Finalização:** O jogo termina assim que um jogador vence ou quando ocorre um empate.\n";

cout << "O Jogo da Velha é um passatempo rápido e estratégico que continua sendo apreciado por sua simplicidade e desafio.\n";
}

void iniciaTabuleiro(char tabuleiro[3][3]) {
    int linha, coluna;
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            tabuleiro[linha][coluna] = '-';
        }
    }
}

void exibeTabuleiro(char tabuleiro[3][3]) {
    int linha, coluna;
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            cout << tabuleiro[linha][coluna];
        }
        cout << "\n";
    }
}

int conferevencedor(char tabuleiro[3][3]) {
    int linha, coluna;

    // Confere se algum jogador ganhou em linhas
    for (linha = 0; linha < 3; linha++) {
        if (tabuleiro[linha][0] == 'X' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
            return 1;
        } else if (tabuleiro[linha][0] == 'O' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
            return 2;
        }
    }

    // Confere se o jogador ganhou nas colunas
    for (coluna = 0; coluna < 3; coluna++) {
        if (tabuleiro[0][coluna] == 'X' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
            return 1;
        } else if (tabuleiro[0][coluna] == 'O' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
            return 2;
        }
    }

    // Analisando a diagonal
    if (tabuleiro[0][0] == 'X' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        return 1;
    } else if (tabuleiro[0][0] == 'O' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        return 2;
    }

    // Analisando a diagonal
    if (tabuleiro[0][2] == 'X' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        return 1;
    } else if (tabuleiro[0][2] == 'O' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        return 2;
    }

    return 0; // Nenhum vencedor ainda
}

void jogaremdupla() {
    string nomedojogador1, nomedojogador2, nomedojogadoratual;
    char tabuleiro[3][3];
    int linhajogada, colunajogada;
    int estadodejogo = 1;
    int turnodojogador = 1;
    int maximoderodadas = 0;

    iniciaTabuleiro(tabuleiro);

    cout << "Digite o nome do jogador 1 'X': \n";
    cin >> nomedojogador1;
    cout << "Digite o nome do jogador 2 'O': \n";
    cin >> nomedojogador2;

    while (maximoderodadas < 9 && estadodejogo == 1) {
        limpaTela();

        exibeTabuleiro(tabuleiro);
        cout << "Rodada\n" << maximoderodadas << "\n";

        if (turnodojogador == 1) {
            nomedojogadoratual = nomedojogador1;
        } else {
            nomedojogadoratual = nomedojogador2;
        }

        cout << nomedojogadoratual << ", Digite uma linha: ";
        cin >> linhajogada;
        cout << nomedojogadoratual << ", Digite uma coluna: ";
        cin >> colunajogada;

        if (tabuleiro[linhajogada][colunajogada] == '-') {
            if (turnodojogador == 1) {
                tabuleiro[linhajogada][colunajogada] = 'X';
                turnodojogador = 2;
            } else {
                tabuleiro[linhajogada][colunajogada] = 'O';
                turnodojogador = 1;
            }

            if (conferevencedor(tabuleiro) == 1) {
                cout << "O jogador 1 venceu 'X', Parabéns !!";
                estadodejogo = 0;
            } else if (conferevencedor(tabuleiro) == 2) {
                cout << "O jogador 2 venceu 'O', Parabéns !!";
                estadodejogo = 0;
            }
        } else {
            cout << "Essa posição já está ocupada. Tente novamente.\n";
        }

        limpaTela();
        maximoderodadas++;
    }

    cout << "\n";
    exibeTabuleiro(tabuleiro);
    cout << "\n Fim De jogo";
}

void jogarSozinho() {
    string nomedojogador, nomedomaquina = "Máquina";
    char tabuleiro[3][3];
    int linhajogada, colunajogada;
    int estadodejogo = 1;
    int maximoderodadas = 0;

    iniciaTabuleiro(tabuleiro);

    cout << "Digite o seu nome 'X': \n";
    cin >> nomedojogador;

    while (maximoderodadas < 9 && estadodejogo == 1) {
        limpaTela();

        exibeTabuleiro(tabuleiro);
        cout << "Rodada\n" << maximoderodadas << "\n";

        // Vez do jogador
        cout << nomedojogador << ", Digite uma linha: ";
        cin >> linhajogada;
        cout << nomedojogador << ", Digite uma coluna: ";
        cin >> colunajogada;

        if (tabuleiro[linhajogada][colunajogada] == '-') {
            tabuleiro[linhajogada][colunajogada] = 'X';

            if (conferevencedor(tabuleiro) == 1) {
                cout << "Você venceu 'X', Parabéns !!";
                estadodejogo = 0;
            }
        } else {
            cout << "Essa posição já está ocupada. Tente novamente.\n";
            continue;  // Pula para a próxima iteração do loop
        }

        limpaTela();
        maximoderodadas++;

        // Vez da máquina
        if (maximoderodadas < 9 && estadodejogo == 1) {
            int linhaMaquina, colunaMaquina;

            // Lógica da jogada da máquina
            do {
                linhaMaquina = rand() % 3;
                colunaMaquina = rand() % 3;
            } while (tabuleiro[linhaMaquina][colunaMaquina] != '-');

            tabuleiro[linhaMaquina][colunaMaquina] = 'O';

            if (conferevencedor(tabuleiro) == 2) {
                cout << "A máquina venceu 'O', Mais sorte na próxima !!";
                estadodejogo = 0;
            }

            limpaTela();
            maximoderodadas++;
        }
    }

    cout << "\n";
    exibeTabuleiro(tabuleiro);
    cout << "\n Fim De jogo";
}

void menuInicial() {
    int opcao = 0;
    while (opcao < 1 || opcao > 5) {
        limpaTela();
        cout << "Bem-vindo ao Tic Tac Toe 2023 by Thiago Rosario \n";
        cout << "\n 1- Jogar Em Dupla";
        cout << "\n 2- Jogar Sozinho";
        cout << "\n 3- Instruções.";
        cout << "\n 4- Sobre ";
        cout << "\n 5- Sair";
        cout << "\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Iniciando jogo em dupla";
                jogaremdupla();
                break;
            case 2:
                cout << "Iniciando jogo sozinho";
                jogarSozinho();
                break;
            case 3:
                instrucoes();
                break;
            case 4:
                sobreJogo();
                break;
            case 5:
                cout << "Saindo do jogo";
                break;
            default:
                cout << "Opção inválida. Tente novamente.";
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    menuInicial();


    return 0;
}

