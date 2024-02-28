#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    EMPTY, PAWN_W, ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W,
    PAWN_B, ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B
} Piece;

typedef struct {
    Piece board[8][8];
    int turn;
} ChessBoard;

void print_board(ChessBoard *board) {
    printf("\n");
    for (int y = 7; y >= 0; y--) {
        printf("%d ", y + 1);
        for (int x = 0; x < 8; x++) {
            switch (board->board[x][y]) {
                case EMPTY: printf(". "); break;
                case PAWN_W: printf("P "); break;
                case ROOK_W: printf("R "); break;
                case KNIGHT_W: printf("N "); break;
                case BISHOP_W: printf("B "); break;
                case QUEEN_W: printf("Q "); break;
                case KING_W: printf("K "); break;
                case PAWN_B: printf("p "); break;
                case ROOK_B: printf("r "); break;
                case KNIGHT_B: printf("n "); break;
                case BISHOP_B: printf("b "); break;
                case QUEEN_B: printf("q "); break;
                case KING_B: printf("k "); break;
            }
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n\n");
}

bool is_valid_input(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool is_valid_move(ChessBoard *board, int src_x, int src_y, int dest_x, int dest_y) {
    // Obter a peça na posição de origem
    Piece piece = board->board[src_x][src_y];

    switch (piece) {
        case PAWN_W:
            // Lógica para peão branco
            // Verificar se está movendo uma casa para frente
            if (dest_x == src_x && dest_y == src_y + 1) {
                // Verificar se a casa de destino está vazia
                if (board->board[dest_x][dest_y] == EMPTY) {
                    return true;
                }
            }
            // Verificar movimento inicial de duas casas
            else if (src_y == 1 && dest_x == src_x && dest_y == src_y + 2) {
                // Verificar se as casas estão vazias
                if (board->board[dest_x][dest_y] == EMPTY && board->board[dest_x][src_y + 1] == EMPTY) {
                    return true;
                }
            }
            // Verificar captura em diagonal
            else if ((dest_x == src_x + 1 || dest_x == src_x - 1) && dest_y == src_y + 1) {
                if (board->board[dest_x][dest_y] != EMPTY && board->board[dest_x][dest_y] < 0) {
                    // Captura uma peça preta (assumindo peças pretas como valores negativos)
                    return true;
                }
            }
            break;

        case PAWN_B:
            // Lógica para peão preto
            // Semelhante ao peão branco, mas movendo para a direção oposta
            if (dest_x == src_x && dest_y == src_y - 1) {
                if (board->board[dest_x][dest_y] == EMPTY) {
                    return true;
                }
            }
            else if (src_y == 6 && dest_x == src_x && dest_y == src_y - 2) {
                if (board->board[dest_x][dest_y] == EMPTY && board->board[dest_x][src_y - 1] == EMPTY) {
                    return true;
                }
            }
            else if ((dest_x == src_x + 1 || dest_x == src_x - 1) && dest_y == src_y - 1) {
                if (board->board[dest_x][dest_y] != EMPTY && board->board[dest_x][dest_y] > 0) {
                      // Captura uma peça branca (assumindo peças brancas como valores positivos)
                    return true;
                }
            }
            break;
    }
    case ROOK_W:
    case ROOK_B:
        // Lógica para torre
        // Verifica se o movimento é na mesma coluna ou linha
        if (src_x == dest_x || src_y == dest_y) {
            // Verifica se o caminho até o destino está livre
            if (src_x == dest_x) {
                // Movimento na mesma coluna
                int min_y = src_y < dest_y ? src_y : dest_y;
                int max_y = src_y > dest_y ? src_y : dest_y;
                for (int y = min_y + 1; y < max_y; ++y) {
                    if (board->board[src_x][y] != EMPTY) {
                        return false; // Encontrou uma peça no caminho
                    }
                }
            } else {
                // Movimento na mesma linha
                int min_x = src_x < dest_x ? src_x : dest_x;
                int max_x = src_x > dest_x ? src_x : dest_x;
                for (int x = min_x + 1; x < max_x; ++x) {
                    if (board->board[x][src_y] != EMPTY) {
                        return false; // Encontrou uma peça no caminho
                    }
                }
            }

            // Verifica se o destino está ocupado por uma peça da mesma cor
            if (board->board[dest_x][dest_y] != EMPTY) {
                if ((piece == ROOK_W && board->board[dest_x][dest_y] > 0) ||
                    (piece == ROOK_B && board->board[dest_x][dest_y] < 0)) {
                    return false; // Destino ocupado por uma peça da mesma cor
                }
            }

            return true;
        }
        break;

    case KNIGHT_W:
    case KNIGHT_B:
        // Lógica para cavalo
        // Calcula a diferença absoluta em X e Y entre as posições
        int diferencaX = abs(dest_x - src_x);
        int diferencaY = abs(dest_y - src_y);

        // Verifica se o movimento se encaixa no padrão em L do cavalo
        if ((diferencaX == 2 && diferencaY == 1) || (diferencaX == 1 && diferencaY == 2)) {
            // Verifica se o destino está ocupado por uma peça da mesma cor
            if (board->board[dest_x][dest_y] != EMPTY) {
                if ((piece == KNIGHT_W && board->board[dest_x][dest_y] > 0) ||
                    (piece == KNIGHT_B && board->board[dest_x][dest_y] < 0)) {
                    return false; // Destino ocupado por uma peça da mesma cor
                }
            }
            return true;
        } else {
            return false;
        }
        break;

    case BISHOP_W:
    case BISHOP_B:
        // Lógica para bispo
        // Calcula a diferença absoluta em X e Y entre as posições
        int diferencaX = abs(dest_x - src_x);
        int diferencaY = abs(dest_y - src_y);

        // Verifica se o movimento é diagonal (diferenças em X e Y são iguais)
        if (diferencaX == diferencaY) {
            int stepX = (dest_x - src_x) / diferencaX; // Determina a direção em X
            int stepY = (dest_y - src_y) / diferencaY; // Determina a direção em Y

            // Verifica se o caminho até o destino está livre
            for (int i = 1; i < diferencaX; ++i) {
                if (board->board[src_x + i * stepX][src_y + i * stepY] != EMPTY) {
                    return false; // Encontrou uma peça no caminho
                }
            }

            // Verifica se o destino está ocupado por uma peça da mesma cor
            if (board->board[dest_x][dest_y] != EMPTY) {
                if ((piece == BISHOP_W && board->board[dest_x][dest_y] > 0) ||
                    (piece == BISHOP_B && board->board[dest_x][dest_y] < 0)) {
                    return false; // Destino ocupado por uma peça da mesma cor
                }
            }

            return true;
        } else {
            return false;
        }
        break;

    case QUEEN_W:
    case QUEEN_B:
        // Lógica para rainha
        // Calcula a diferença absoluta em X e Y entre as posições
        int diferencaX = abs(dest_x - src_x);
        int diferencaY = abs(dest_y - src_y);

        // Verifica se o movimento é horizontal, vertical ou diagonal
        if (src_x == dest_x || src_y == dest_y || diferencaX == diferencaY) {
            // Direção do movimento
            int stepX = (dest_x != src_x) ? (dest_x - src_x) / diferencaX : 0;
            int stepY = (dest_y != src_y) ? (dest_y - src_y) / diferencaY : 0;

            // Distância do movimento (maior diferença entre X e Y)
            int distancia = diferencaX > diferencaY ? diferencaX : diferencaY;

            // Verifica se o caminho até o destino está livre
            for (int i = 1; i < distancia; ++i) {
                if (board->board[src_x + i * stepX][src_y + i * stepY] != EMPTY) {
                    return false; // Encontrou uma peça no caminho
                }
            }

            // Verifica se o destino está ocupado por uma peça da mesma cor
            if (board->board[dest_x][dest_y] != EMPTY) {
                if ((piece == QUEEN_W && board->board[dest_x][dest_y] > 0) ||
                    (piece == QUEEN_B && board->board[dest_x][dest_y] < 0)) {
                    return false; // Destino ocupado por uma peça da mesma cor
                }
            }

            return true;
        } else {
            return false;
        }
        break;

    case KING_W:
    case KING_B:
        // Lógica para rei
        // Calcula a diferença absoluta em X e Y entre as posições
        int diferencaX = abs(dest_x - src_x);
        int diferencaY = abs(dest_y - src_y);

        // Verifica se o movimento é de apenas uma casa em qualquer direção
        if ((diferencaX == 1 || diferencaX == 0) && (diferencaY == 1 || diferencaY == 0)) {
            // Verifica se o destino está ocupado por uma peça da mesma cor
            if (board->board[dest_x][dest_y] != EMPTY) {
                if ((piece == KING_W && board->board[dest_x][dest_y] > 0) ||
                    (piece == KING_B && board->board[dest_x][dest_y] < 0)) {
                    return false; // Destino ocupado por uma peça da mesma cor
                }
            }

            return true;
        } else {
            return false;
        }
        break;

        default:
            // Se a peça for vazia ou desconhecida, o movimento é inválido
            return false;
}
 


void move_piece(ChessBoard *board, int src_x, int src_y, int dest_x, int dest_y) {

    if (is_valid_move(board, src_x, src_y, dest_x, dest_y)) {

        Piece piece = board->board[src_x][src_y];
        

        if ((piece == PAWN_W && dest_y == src_y + 1) || (piece == PAWN_B && dest_y == src_y - 1)) {
            board->en_passant_target_x = -1;
        }
        
        if (piece == KING_W && abs(src_x - dest_x) == 2) {
            if (dest_x > src_x) {
                board->board[7][5] = board->board[7][7];
                board->board[7][7] = EMPTY;
            } else {
                board->board[7][3] = board->board[7][0];
                board->board[7][0] = EMPTY;
            }

        }
        if (piece == KING_B && abs(src_x - dest_x) == 2) {
            if (dest_x > src_x) {
                board->board[0][5] = board->board[0][7];
                board->board[0][7] = EMPTY;
            } else {
                board->board[0][3] = board->board[0][0];
                board->board[0][0] = EMPTY;
            }

        }


        // Check for promotion

        if ((piece == PAWN_W && dest_y == 0) || (piece == PAWN_B && dest_y == 7)) {

            // Handle pawn promotion logic here

        }


        board->board[dest_x][dest_y] = piece;

        board->board[src_x][src_y] = EMPTY;

    }

}

void get_player_move(ChessBoard *board, int player) {
    int src_x, src_y, dest_x, dest_y;
    printf("Jogador %d, insira as coordenadas da peça a ser movida (x y): ", player);
    scanf("%d %d", &src_x, &src_y);
    printf("Insira as coordenadas do destino (x y): ");
    scanf("%d %d", &dest_x, &dest_y);
    while (!is_valid_input(src_x, src_y) || !is_valid_input(dest_x, dest_y)) {
        printf("Coordenadas inválidas, tente novamente.\n");
        printf("Insira as coordenadas da peça a ser movida (x y): ");
        scanf("%d %d", &src_x, &src_y);
        printf("Insira as coordenadas do destino (x y): ");
        scanf("%d %d", &dest_x, &dest_y);
    }
}

void make_move(ChessBoard *board, int player) {
    int src_x, src_y, dest_x, dest_y;
    get_player_move(board, player);
    move_piece(board, src_x, src_y, dest_x, dest_y);
}

bool is_game_over(ChessBoard *board) {
    bool KING_W = false;
    bool KING_B = false;

    // Procurar os reis no tabuleiro
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->board[x][y] == KING_W) {
                KING_W = true;
            }
            if (board->board[x][y] == KING_B) {
                KING_B = true;
            }
        }
    }

    // Se um dos reis não for encontrado, o jogo terminou
    return !KING_W || !KING_B;
}



void game_loop(ChessBoard *board) {
    int currentPlayer = 1; // Assumindo que o jogador 1 começa

    while (!is_game_over(board)) {
        print_board(board);
        make_move(board, currentPlayer);
        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Alternar jogadores
    }
    printf("Game over\n");
}

 void initialize_board(ChessBoard *board) {
    // Inicializar todas as posições do tabuleiro como vazias
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            board->board[x][y] = EMPTY;
        }
    }

    // Posicionar as peças brancas
    board->board[0][0] = board->board[7][0] = ROOK_W;
    board->board[1][0] = board->board[6][0] = KNIGHT_W;
    board->board[2][0] = board->board[5][0] = BISHOP_W;
    board->board[3][0] = QUEEN_W;
    board->board[4][0] = KING_W;
    for (int x = 0; x < 8; x++) {
        board->board[x][1] = PAWN_W;
    }

    // Posicionar as peças pretas
    board->board[0][7] = board->board[7][7] = ROOK_B;
    board->board[1][7] = board->board[6][7] = KNIGHT_B;
    board->board[2][7] = board->board[5][7] = BISHOP_B;
    board->board[3][7] = QUEEN_B;
    board->board[4][7] = KING_B;
    for (int x = 0; x < 8; x++) {
        board->board[x][6] = PAWN_B;
    }

    // Definir a vez inicial (branco = 0, preto = 1)
    board->turn = 0;
}


int main() {
    ChessBoard board;
    initialize_board(&board); // Inicialize o tabuleiro
    board.turn = 0; // 0 para branco, 1 para preto
    game_loop(&board); // Inicie o loop do jogo
    return 0;
}
