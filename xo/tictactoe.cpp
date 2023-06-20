#include "tictactoe.h"

using namespace std;

TicTacToe::TicTacToe(int grid_size, int row_count)
{
	gridSize = grid_size;
	rowCount = row_count;
	grid = new int*[gridSize];

    for (int i = 0; i < gridSize; i++)
    {
        grid[i] = new int[gridSize];

        for (int j = 0; j < gridSize; j++)
            grid[i][j] = 0;
    }

	isPlayerTurn = true;
	currentPlayer = 1;
	otherPlayer = 2;
}

TicTacToe::~TicTacToe()
{
	for (int i = 0; i < gridSize; i++)
		delete[] grid[i];
	delete[] grid;
}

void TicTacToe::userChoice(int x, int y)
{
	if (isGameOver() || !isPlayerTurn || x < 0 || x >= gridSize || y < 0 || y >= gridSize || grid[x][y] != 0)
		return;

	grid[x][y] = currentPlayer;
	isPlayerTurn = false;
}

void TicTacToe::makeChoice() {
    if (isGameOver() || isPlayerTurn)
        return;

    int bestScore = INT_MIN;
    int bestMoveX = -1;
    int bestMoveY = -1;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 0) {
                grid[i][j] = otherPlayer;

                int score = minimax(0, false, INT_MIN, INT_MAX);

                grid[i][j] = 0;

                if (score > bestScore) {
                    bestScore = score;
                    bestMoveX = i;
                    bestMoveY = j;
                }
            }
        }
    }

    if (bestMoveX != -1 && bestMoveY != -1)
        grid[bestMoveX][bestMoveY] = otherPlayer;

    isPlayerTurn = true;
}

bool TicTacToe::isGameOver() {
    if (isWinningMove(currentPlayer))
        return true;
    if (isWinningMove(otherPlayer))
        return true;
    if (!isMoveLeft())
        return true;

    return false;
}

int** TicTacToe::getGrid()
{
	return grid;
}

int TicTacToe::evaluateGrid() {
    // Check rows
    for (int row = 0; row < gridSize; ++row) {
        int countPlayer = 0;
        int countOtherPlayer = 0;
        for (int col = 0; col < gridSize; ++col) {
            if (grid[row][col] == currentPlayer)
                countPlayer++;
            else if (grid[row][col] == otherPlayer)
                countOtherPlayer++;
        }
        if (countPlayer == rowCount)
            return 1;
        if (countOtherPlayer == rowCount)
            return -1;
    }

    // Check columns
    for (int col = 0; col < gridSize; ++col) {
        int countPlayer = 0;
        int countOtherPlayer = 0;
        for (int row = 0; row < gridSize; ++row) {
            if (grid[row][col] == currentPlayer)
                countPlayer++;
            else if (grid[row][col] == otherPlayer)
                countOtherPlayer++;
        }
        if (countPlayer == rowCount)
            return 1;
        if (countOtherPlayer == rowCount)
            return -1;
    }

    // Check diagonal from top-left to bottom-right
    int countPlayer = 0;
    int countOtherPlayer = 0;
    for (int i = 0; i < gridSize; ++i) {
        if (grid[i][i] == currentPlayer)
            countPlayer++;
        else if (grid[i][i] == otherPlayer)
            countOtherPlayer++;
    }
    if (countPlayer == rowCount)
        return 1;
    if (countOtherPlayer == rowCount)
        return -1;

    // Check diagonal from top-right to bottom-left
    countPlayer = 0;
    countOtherPlayer = 0;
    for (int i = 0; i < gridSize; ++i) {
        if (grid[i][gridSize - 1 - i] == currentPlayer)
            countPlayer++;
        else if (grid[i][gridSize - 1 - i] == otherPlayer)
            countOtherPlayer++;
    }
    if (countPlayer == rowCount)
        return 1;
    if (countOtherPlayer == rowCount)
        return -1;

    return 0;
}

int TicTacToe::minimax(int depth, bool maximizingPlayer, int alpha, int beta) {
    int score = evaluateGrid();

    if (score == 1 || score == -1)
        return score;

    if (!isMoveLeft())
        return 0;

    if (maximizingPlayer) {
        int maxScore = INT_MIN;

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] == 0) {
                    grid[i][j] = currentPlayer;
                    int currentScore = minimax(depth + 1, false, alpha, beta);
                    grid[i][j] = 0;
                    maxScore = std::max(maxScore, currentScore);
                    alpha = std::max(alpha, currentScore);

                    if (beta <= alpha)
                        break;
                }
            }
        }

        return maxScore;
    }
    else {
        int minScore = INT_MAX;

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] == 0) {
                    grid[i][j] = otherPlayer;
                    int currentScore = minimax(depth + 1, true, alpha, beta);
                    grid[i][j] = 0;
                    minScore = std::min(minScore, currentScore);
                    beta = std::min(beta, currentScore);

                    if (beta <= alpha)
                        break;
                }
            }
        }

        return minScore;
    }
}

bool TicTacToe::isMoveLeft() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 0)
                return true;
        }
    }

    return false;
}

bool TicTacToe::isWinningMove(int player) {
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col <= gridSize - rowCount; ++col) {
            bool isWinning = true;

            for (int i = 0; i < rowCount; ++i) {
                if (grid[row][col + i] != player) {
                    isWinning = false;
                    break;
                }
            }

            if (isWinning)
                return true;
        }
    }

    for (int col = 0; col < gridSize; ++col) {
        for (int row = 0; row <= gridSize - rowCount; ++row) {
            bool isWinning = true;

            for (int i = 0; i < rowCount; ++i) {
                if (grid[row + i][col] != player) {
                    isWinning = false;
                    break;
                }
            }

            if (isWinning)
                return true;
        }
    }

    for (int row = 0; row <= gridSize - rowCount; ++row) {
        for (int col = 0; col <= gridSize - rowCount; ++col) {
            bool isWinning = true;

            for (int i = 0; i < rowCount; ++i) {
                if (grid[row + i][col + i] != player) {
                    isWinning = false;
                    break;
                }
            }

            if (isWinning)
                return true;
        }
    }

    for (int row = rowCount - 1; row < gridSize; ++row) {
        for (int col = 0; col <= gridSize - rowCount; ++col) {
            bool isWinning = true;

            for (int i = 0; i < rowCount; ++i) {
                if (grid[row - i][col + i] != player) {
                    isWinning = false;
                    break;
                }
            }

            if (isWinning)
                return true;
        }
    }

    return false;
}
