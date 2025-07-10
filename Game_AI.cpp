#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

void initializeBoard() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "--+---+--\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    // Rows
    for (int row = 0; row < SIZE; ++row)
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == 'O') return +10;
            else if (board[row][0] == 'X') return -10;
        }

    // Columns
    for (int col = 0; col < SIZE; ++col)
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == 'O') return +10;
            else if (board[0][col] == 'X') return -10;
        }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        else if (board[0][0] == 'X') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        else if (board[0][2] == 'X') return -10;
    }

    return 0;
}

int minimax(int depth, bool isMax) {
    int score = evaluate();

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(depth + 1, !isMax));
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(depth + 1, !isMax));
                    board[i][j] = ' ';
                }
        return best;
    }
}

pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
    return bestMove;
}

void playerMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column: 0-2): ";
        cin >> row >> col;
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
            board[row][col] = 'X';
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

int main() {
    initializeBoard();
    cout << "Tic-Tac-Toe: You (X) vs AI (O)\n";

    while (true) {
        printBoard();
        playerMove();
        if (evaluate() == -10) {
            printBoard();
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }

        pair<int, int> aiMove = findBestMove();
        board[aiMove.first][aiMove.second] = 'O';
        cout << "AI played at (" << aiMove.first << ", " << aiMove.second << ")\n";

        if (evaluate() == 10) {
            printBoard();
            cout << "AI wins!\n";
            break;
        }
        if (!isMovesLeft()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}


