#include <stdio.h>
#define MAX 10

// Display menu
void menu() {
    printf("Tic Tac Toe Game\n");
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

int main() {
    int size;
    menu();

    printf("Enter board size N x N (3 <= N <= 10): ");
    scanf("%d", &size);
    printf("\n");

    if (size < 3 || size > MAX) {
        printf("Invalid size! Must be between 3 and 10.\n");
        return 1;
    }

    char board[MAX][MAX];

    initBoard(board, size);
    dispBoard(board, size);

    return 0;
}