#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// Display menu
void menu() {
    printf("Tic Tac Toe Game\n");
    printf("----------------\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    printf("----------------\n");
}

// Function to initialize the board with spaces
void initBoard(char board[][MAX], int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = ' ';
        }
    }
}

// Function to print the board in a formatted way
void dispBoard(char board[][MAX], int size) {
    // Print column headers
    printf("    ");
    for (int col = 0; col < size; col++) {
        printf("%d   ", col);
    }
    printf("\n");

    for (int row = 0; row < size; row++) {
        printf("  ");
        for (int col = 0; col < size; col++) {
            printf("----");
        }
        printf("-\n");

        printf("%d ", row);
        for (int col = 0; col < size; col++) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }

    // bottom border
    printf("  ");
    for (int col = 0; col < size; col++) {
        printf("----");
    }
    printf("-\n\n");
}

// Accept input from player
int acceptInput(int* row, int* col, int size) {
    printf("Enter row and column (0-%d): ", size - 1);
    
    // Check if scanf reads two integers
    int check = scanf("%d %d", row, col);
    if (check != 2) {
        printf("\nInvalid input! Please enter two integers.\n");
        while (getchar() != '\n'); // clear input buffer
        return 0;
    }
    if (*row < 0 || *row >= size || *col < 0 || *col >= size) {
        printf("\nInvalid position! Try again.\n");
        return 0;
    }
    printf("\n");
    return 1;
}

// Validate if cell is free
int validateMove(char board[][MAX], int row, int col) {
    return (board[row][col] == ' ');
}

// Check win condition
int checkWin(char board[][MAX], int size, char symbol) {
    int win;

    // Check rows
    for (int i = 0; i < size; i++) {
        win = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    // Check columns
    for (int j = 0; j < size; j++) {
        win = 1;
        for (int i = 0; i < size; i++) {
            if (board[i][j] != symbol) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    // Check diagonal
    win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != symbol) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    // Check anti-diagonal
    win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][size - 1 - i] != symbol) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    return 0;
}

// Check draw condition
int checkDraw(char board[][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

// Log board state to file
void logBoard(FILE* logFile, char board[][MAX], int size) {
    fprintf(logFile, "\nBoard State:\n");

    // column headers
    fprintf(logFile, "    ");
    for (int col = 0; col < size; col++) {
        fprintf(logFile, "%d   ", col);
    }
    fprintf(logFile, "\n");

    for (int row = 0; row < size; row++) {
        fprintf(logFile, "  ");
        for (int col = 0; col < size; col++) {
            fprintf(logFile, "----");
        }
        fprintf(logFile, "-\n");

        fprintf(logFile, "%d ", row);
        for (int col = 0; col < size; col++) {
            fprintf(logFile, "| %c ", board[row][col]);
        }
        fprintf(logFile, "|\n");
    }

    fprintf(logFile, "  ");
    for (int col = 0; col < size; col++) {
        fprintf(logFile, "----");
    }
    fprintf(logFile, "-\n\n");
}

// Computer move (random)
void computerMove(char board[][MAX], int size, int* row, int* col) {
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!validateMove(board, *row, *col));
    printf("Computer chooses: %d %d\n\n", *row, *col);
}

int main() {
    int size;
    menu();

    // Loop until valid size is entered
    do{
		printf("Enter board size N x N (3 <= N <= 10): ");
        scanf("%d", &size);
        printf("\n");

        if (size < 3 || size > MAX) {
            printf("Invalid board size! Must be between 3 and 10.\n\n");
        }
	}while(size < 3 || size > MAX);

    char board[MAX][MAX];
    initBoard(board, size);

    // Open log file
    FILE* logFile = fopen("ticTacToe_log.txt", "w");
    if (!logFile) {
        printf("Error opening log file.\n");
        return 1;
    }

    int turn = 0;
    int row, col;
    char playerSymbol;
    int gameOver = 0;

    while (!gameOver) {
        dispBoard(board, size);

        // Take turns 0 = X, 1 = O and display whose turn it is
        if (turn == 0) {
            playerSymbol = 'X';
        } else {
            playerSymbol = 'O';
        }
        printf("Player %c's turn.\n", playerSymbol);

        // Input and validation
        while (1) {
            if (!acceptInput(&row, &col, size)) 
                continue;
            if (!validateMove(board, row, col)) {
                printf("Cell already occupied! Try again.\n\n");
            } else {
                break;
            }
        }

        // Place move
        board[row][col] = playerSymbol;

        // Log board state
        logBoard(logFile, board, size);

        // Check win/draw
        if (checkWin(board, size, playerSymbol)) {
            dispBoard(board, size);
            printf("Player %c wins!\n", playerSymbol);
            gameOver = 1;
        } else if (checkDraw(board, size)) {
            dispBoard(board, size);
            printf("It's a draw!\n");
            gameOver = 1;
        } else {
            turn = 1 - turn; // Switch turns
        }
    }

    fclose(logFile);
    return 0;
}