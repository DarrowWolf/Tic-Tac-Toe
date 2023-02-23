#include <iostream>
#define SIZE 3

char board[SIZE][SIZE] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };

void printBoard(char board[][SIZE]) {
    printf("\n\n");

    printf("\t\t\t %c | %c | %c \n",
        board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n",
        board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n",
        board[2][0], board[2][1], board[2][2]);

    return;
}

int getMove(char board[][SIZE], int player) {
    int choice;
    printf("Player %d, enter the number of the cell where you want to place your symbol: ", player);
    std::cin >> choice;

    int row = (choice - 1) / SIZE;
    int col = (choice - 1) % SIZE;

    // Check if the chosen position is valid and available
    if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
        return choice;
    }
    else {
        printf("Invalid move. Please try again.\n");
        return getMove(board, player); // Recursively call this function until a valid move is entered
    }
}

bool checkWin(char board[][SIZE], char symbol, bool& draw) {
    // Initialize draw to false
    draw = false;

    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true; // Player has won by completing a row
        }
    }

    //Check for Columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true; // Player has won by completing a column
        }
    }
    //Check Diagonal 
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true; // Diagonal check from top-left to bottom-right
    }

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true; // Diagonal check from top-right to bottom-left
    }

    // Check for a draw
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                draw = false;
                return false; // Game is not over yet
            }
        }
    }

    // No more moves left, so the game is a draw
    draw = true;
    return true;
}


int main()
{
bool replay = true;
    do {
        int player = 1;
        int choice;
        bool draw = false;
        printBoard(board);

        do {
            choice = getMove(board, player);

            // Update the board with the player's move
            int row = (choice - 1) / SIZE;
            int col = (choice - 1) % SIZE;
            board[row][col] = (player == 1) ? 'X' : 'O';

            // Print the updated board and remove previous board so it won't clog up the console
            std::system("cls");
            printBoard(board);

            // Check if the current player has won or draw
            if (checkWin(board, (player == 1) ? 'X' : 'O', draw)) {
                if (draw) {
                    printf("The game is a draw.\n");
                }
                else {
                    printf("Congratulations! Player %d has won.\n", player);
                }
                break; 
            }

            // Switch to the other player
            player = (player == 1) ? 2 : 1;
        } while (true);

        // Ask if the player wants to play again
        char replayChoice;
        printf("Do you want to play again? (y/n): ");
        std::cin >> replayChoice;
        replayChoice= toupper(replayChoice);

        if (replayChoice != 'Y') {
            replay = false;
        }
        else {
            // Reset the game board 
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    board[i][j] = (i * SIZE) + j + '1';
                }
            }
        }

    } while (replay);

    return 0;
}
