#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  

const int BOARD_SIZE = 5;
const int NUM_MOVES = 10;

int bestScore = -1;
int bestMove;

int Score(const std::vector<std::vector<int>>& board, int player) {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == player) {
                score++;
            }
            else if (board[i][j] == 0) {
                int emptyCount = 1;
                // Count empty squares around the current square.  
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        if (k == 0 && l == 0) continue;
                        if (i + k < 0 || i + k >= BOARD_SIZE || j + l < 0 || j + l >= BOARD_SIZE) continue;
                        if (board[i + k][j + l] == 0) {
                            emptyCount++;
                        }
                        else if (board[i + k][j + l] == player) {
                            emptyCount--;
                        }
                    }
                }
                // If the current square is surrounded by empty squares, add it to the score.  
                if (emptyCount > 0) {
                    score += emptyCount;
                }
            }
        }
    }
    return score;
}

void monteCarlo(int move, int player) {
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));
    int score = 0;
    for (int i = 0; i < move; ++i) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] == 0) {
            board[x][y] = player;
            score += Score(board, player); // Add the score of the current board.  
            board[x][y] = 0; // Reset the square.  
        }
    }
    if (score > bestScore) {
        bestScore = score;
        bestMove = move;
    }
}

