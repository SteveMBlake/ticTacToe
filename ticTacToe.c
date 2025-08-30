#include <stdio.h>

// Display menu
void menu() {
    printf("Tic Tac Toe Game\n");
    printf("----------------\n");
}

// Function to initialize the board with spaces
void initBoard(char board[][10], int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = ' ';
        }
    }
}

// Function to print the board in a formatted way
void dispBoard(char board[][10], int size) {
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
    printf("-\n");
}

int main() {
    int size;
    menu();

    printf("Enter board size N x N (3 <= N <= 10): ");
    scanf("%d", &size);
    printf("\n");

    if (size < 3 || size > 10) {
        printf("Invalid size! Must be between 3 and 10.\n");
        return 1;
    }

    char board[10][10];

    initBoard(board, size);
    dispBoard(board, size);

    return 0;
}