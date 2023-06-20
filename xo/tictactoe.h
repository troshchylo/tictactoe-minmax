#pragma once

#include <iostream>

using namespace std;

class TicTacToe {
public:
    TicTacToe(int gridSize, int rowCount);
    ~TicTacToe();
    void userChoice(int x, int y);
    void makeChoice();
    bool isGameOver();
    int** getGrid();
    bool isWinningMove(int player);

private:
    int** grid;
    int gridSize;
    int rowCount;
    bool isPlayerTurn;
    int currentPlayer;
    int otherPlayer;

    int evaluateGrid();
    int minimax(int depth, bool maximizingPlayer, int alpha, int beta);
    bool isMoveLeft();
};