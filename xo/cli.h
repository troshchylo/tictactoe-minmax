#pragma once

#include <iostream>
#include "tictactoe.h"

using namespace std;

class CommandLineInterface 
{
public:
	CommandLineInterface();
	~CommandLineInterface();
	void run();

private:
	TicTacToe* tt;
	int gridSize;
	int rowCount;

	pair<int, int> getCoords();
	int askGridSize();
	int askRowCount();
	void printGrid();
	void printResults();
	bool isGameOver();
	void userChoice();
	void computerChoice();
};