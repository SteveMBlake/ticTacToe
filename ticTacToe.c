#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// Display menu
void menu()
{
    printf("Tic Tac Toe Game\n");
    printf("----------------\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Three Players\n");
    printf("4. Exit\n");
    printf("----------------\n");
}

// Function to initialize the board with spaces
void initBoard(char board[][MAX], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            board[row][col] = ' ';
        }
    }
}

// Function to print the board
void dispBoard(char board[][MAX], int size)
{
    printf("    ");
    for (int col = 0; col < size; col++)
    {
        printf("%d   ", col);
    }
    printf("\n");

    for (int row = 0; row < size; row++)
    {
        printf("  ");
        for (int col = 0; col < size; col++)
        {
            printf("----");
        }
        printf("-\n");

        printf("%d ", row);
        for (int col = 0; col < size; col++)
        {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }

    printf("  ");
    for (int col = 0; col < size; col++)
    {
        printf("----");
    }
    printf("-\n\n");
}

// Accept input from player
int acceptInput(int *row, int *col, int size)
{
    printf("Enter row and column (0-%d): ", size - 1);
    int check = scanf("%d %d", row, col);
    if (check != 2)
    {
        printf("\nInvalid input! Please enter two integers.\n");
        while (getchar() != '\n')
            ;
        return 0;
    }
    if (*row < 0 || *row >= size || *col < 0 || *col >= size)
    {
        printf("\nInvalid position! Try again.\n");
        return 0;
    }
    printf("\n");
    return 1;
}

// Validate if cell is free
int validateMove(char board[][MAX], int row, int col)
{
    return (board[row][col] == ' ');
}

// Check win condition
int checkWin(char board[][MAX], int size, char symbol)
{
    int win;

    for (int i = 0; i < size; i++)
    {
        win = 1;
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] != symbol)
            {
                win = 0;
                break;
            }
        }
        if (win)
            return 1;
    }

    for (int j = 0; j < size; j++)
    {
        win = 1;
        for (int i = 0; i < size; i++)
        {
            if (board[i][j] != symbol)
            {
                win = 0;
                break;
            }
        }
        if (win)
            return 1;
    }

    win = 1;
    for (int i = 0; i < size; i++)
    {
        if (board[i][i] != symbol)
        {
            win = 0;
            break;
        }
    }
    if (win)
        return 1;

    win = 1;
    for (int i = 0; i < size; i++)
    {
        if (board[i][size - 1 - i] != symbol)
        {
            win = 0;
            break;
        }
    }
    if (win)
        return 1;

    return 0;
}

// Check draw condition
int checkDraw(char board[][MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

// Computer move (smart: win if possible, block if possible, else random)
void computerMove(char board[][MAX], int size, int *row, int *col, char mySymbol)
{
    // Try to win
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (board[r][c] != ' ')
                continue;
            char temp = board[r][c];
            board[r][c] = mySymbol;
            if (checkWin(board, size, mySymbol))
            {
                board[r][c] = temp;
                *row = r;
                *col = c;
                return;
            }
            board[r][c] = temp;
        }
    }

    // Find opponents
    char opps[3];
    int num_opps = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            char ch = board[i][j];
            if (ch != ' ' && ch != mySymbol)
            {
                int found = 0;
                for (int k = 0; k < num_opps; k++)
                {
                    if (opps[k] == ch)
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    opps[num_opps++] = ch;
                }
            }
        }
    }

    // Try to block
    for (int o = 0; o < num_opps; o++)
    {
        char opp = opps[o];
        for (int r = 0; r < size; r++)
        {
            for (int c = 0; c < size; c++)
            {
                if (board[r][c] != ' ')
                    continue;
                char temp = board[r][c];
                board[r][c] = opp;
                if (checkWin(board, size, opp))
                {
                    board[r][c] = temp;
                    *row = r;
                    *col = c;
                    return;
                }
                board[r][c] = temp;
            }
        }
    }

    // Random move
    do
    {
        *row = rand() % size;
        *col = rand() % size;
    } while (!validateMove(board, *row, *col));
}

// Log board state to file
void logBoard(FILE *logFile, char board[][MAX], int size)
{
    fprintf(logFile, "\nBoard State:\n");

    // column headers
    fprintf(logFile, "    ");
    for (int col = 0; col < size; col++)
    {
        fprintf(logFile, "%d   ", col);
    }
    fprintf(logFile, "\n");

    for (int row = 0; row < size; row++)
    {
        fprintf(logFile, "  ");
        for (int col = 0; col < size; col++)
        {
            fprintf(logFile, "----");
        }
        fprintf(logFile, "-\n");

        fprintf(logFile, "%d ", row);
        for (int col = 0; col < size; col++)
        {
            fprintf(logFile, "| %c ", board[row][col]);
        }
        fprintf(logFile, "|\n");
    }

    fprintf(logFile, "  ");
    for (int col = 0; col < size; col++)
    {
        fprintf(logFile, "----");
    }
    fprintf(logFile, "-\n\n");
}

int main()
{

    int size, mode;
    menu();
    printf("Choose mode: ");
    scanf("%d", &mode);

    if (mode == 4)
    {
        printf("Exiting game...\n");
        return 0;
    }

    do
    {
        printf("Enter board size N x N (3 <= N <= 10): ");
        scanf("%d", &size);
        printf("\n");
        if (size < 3 || size > MAX)
        {
            printf("Invalid board size! Must be between 3 and 10.\n\n");
        }
    } while (size < 3 || size > MAX);

    char board[MAX][MAX];
    initBoard(board, size);

    int gameOver = 0;

    // Open log file
    FILE *logFile = fopen("ticTacToe_log.txt", "w");
    if (!logFile)
    {
        printf("Error opening log file!\n");
        return 1;
    }

    switch (mode)
    {
    case 1: // Player vs Player
    {
        int turn = 0; // 0 = X, 1 = O
        int row, col;
        char playerSymbol;
        while (!gameOver)
        {
            dispBoard(board, size);
            logBoard(logFile, board, size);

            playerSymbol = (turn == 0) ? 'X' : 'O';
            printf("Player %c's turn.\n", playerSymbol);

            while (1)
            {
                if (!acceptInput(&row, &col, size))
                    continue;
                if (!validateMove(board, row, col))
                {
                    printf("Cell already occupied! Try again.\n\n");
                }
                else
                {
                    break;
                }
            }

            board[row][col] = playerSymbol;

            if (checkWin(board, size, playerSymbol))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                printf("Player %c wins!\n", playerSymbol);
                gameOver = 1;
            }
            else if (checkDraw(board, size))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                printf("It's a draw!\n");
                gameOver = 1;
            }
            else
            {
                turn = 1 - turn;
            }
        }
    }
    break;

    case 2: // Player vs Computer
    {
        int turn = 0; // 0 = X (human), 1 = O (computer)
        int row, col;
        char playerSymbol;
        while (!gameOver)
        {
            dispBoard(board, size);
            logBoard(logFile, board, size);

            if (turn == 0)
            { // Player
                playerSymbol = 'X';
                printf("Your turn (Player %c).\n", playerSymbol);
                while (1)
                {
                    if (!acceptInput(&row, &col, size))
                        continue;
                    if (!validateMove(board, row, col))
                    {
                        printf("Cell already occupied! Try again.\n\n");
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            { // Computer
                playerSymbol = 'O';
                printf("Computer's turn (Player %c).\n", playerSymbol);
                computerMove(board, size, &row, &col, playerSymbol);
                printf("Computer chooses: %d %d\n\n", row, col);
            }

            board[row][col] = playerSymbol;

            if (checkWin(board, size, playerSymbol))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                if (turn == 0)
                {
                    printf("You win!\n");
                }
                else
                {
                    printf("Computer wins!\n");
                }
                gameOver = 1;
            }
            else if (checkDraw(board, size))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                printf("It's a draw!\n");
                gameOver = 1;
            }
            else
            {
                turn = 1 - turn;
            }
        }
    }
    break;

    case 3: // Three Players
    {
        char symbols[3] = {'X', 'O', 'Z'};
        int isHuman[3];
        int numHumans = 0;

        printf("Configure players (at least one must be human):\n");
        for (int p = 0; p < 3; p++)
        {
            char choice;
            do
            {
                printf("Player %d (%c): 'h' for human, 'c' for computer: ", p + 1, symbols[p]);
                scanf(" %c", &choice);
            } while (choice != 'h' && choice != 'c');
            isHuman[p] = (choice == 'h');
            if (isHuman[p])
                numHumans++;
        }
        printf("\n");

        if (numHumans == 0)
        {
            printf("At least one human required. Setting Player 1 as human.\n");
            isHuman[0] = 1;
        }

        int turn = 0;
        int row, col;
        char playerSymbol;
        while (!gameOver)
        {
            dispBoard(board, size);
            logBoard(logFile, board, size);

            int current = turn % 3;
            playerSymbol = symbols[current];
            printf("Player %d (%c)'s turn.\n", current + 1, playerSymbol);

            if (isHuman[current])
            {
                while (1)
                {
                    if (!acceptInput(&row, &col, size))
                        continue;
                    if (!validateMove(board, row, col))
                    {
                        printf("Cell already occupied! Try again.\n\n");
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                computerMove(board, size, &row, &col, playerSymbol);
            }

            board[row][col] = playerSymbol;

            if (checkWin(board, size, playerSymbol))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                printf("Player %d (%c) wins!\n", current + 1, playerSymbol);
                gameOver = 1;
            }
            else if (checkDraw(board, size))
            {
                dispBoard(board, size);
                logBoard(logFile, board, size);
                printf("It's a draw!\n");
                gameOver = 1;
            }
            else
            {
                turn++;
            }
        }
    }
    break;

    default:
        printf("Invalid option!\n");
        break;
    }

    fclose(logFile);
    return 0;
}
