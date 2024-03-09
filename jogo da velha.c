#include <stdio.h>
#include <locale.h>

char board[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
int currentPlayer = 1;

// Função para exibir o tabuleiro
void displayBoard() {
    printf("\n  1   2   3\n");
    for (int i = 0; i < 3; i++) {
        printf("%c", 65 + i);  // Exibe as letras A, B, C para as linhas
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf(" ---|---|---\n");
    }
    printf("\n");
}

// Função para verificar se o jogo terminou
int isGameOver() {
    // Verifica as linhas
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
    }

    // Verifica as colunas
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }

    // Verifica as diagonais
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;

    // Verifica se o tabuleiro está cheio (empate)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0; // O jogo ainda não acabou
        }
    }

    return -1; // Empate
}

// Função para realizar uma jogada
int makeMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
        return 0; // Movimento inválido

    if (currentPlayer == 1) {
        board[row][col] = 'X';
        currentPlayer = 2;
    } else {
        board[row][col] = 'O';
        currentPlayer = 1;
    }

    return 1; // Movimento válido
}

int main() {
    setlocale(LC_ALL, ""); // Configura a localidade para a localidade padrão do sistema

    int row, col, moveResult;

    printf("Bem-vindo ao Jogo da Velha!\n\n");

    do {
        displayBoard();
        
        // Solicita a jogada do jogador atual
        printf("Jogador %d, insira sua jogada (linha coluna): ", currentPlayer);
        scanf("%d %d", &row, &col);

        // Ajusta os índices de entrada para a matriz
        row--;
        col--;

        moveResult = makeMove(row, col);

        if (!moveResult)
            printf("Movimento inválido. Tente novamente.\n");
        
    } while (isGameOver() == 0);

    displayBoard();

    int result = isGameOver();

    if (result == -1)
        printf("Empate! O jogo acabou em empate.\n");
    else
        printf("Jogador %d venceu! Parabéns!\n", result);

    return 0;
}

