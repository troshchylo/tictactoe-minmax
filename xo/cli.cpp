#include "cli.h"

using namespace std;

CommandLineInterface::CommandLineInterface()
{
	askGridSize();
	askRowCount();
	tt = new TicTacToe(gridSize, rowCount);
}

CommandLineInterface::~CommandLineInterface()
{
	if (tt != NULL)
	{
		delete tt;
	}
}

void CommandLineInterface::run()
{
	while (!isGameOver())
	{
		printGrid();
		userChoice();
		computerChoice();
	}
	printResults();
}

pair<int, int> CommandLineInterface::getCoords()
{
	int x = -1, y = -1;

	while (x < 0 || x >= gridSize)
	{
		cout << "Podaj rzad: ";
		cin >> x;
	}

	while (y < 0 || y >= gridSize)
	{
		cout << "Podaj kolumne: ";
		cin >> y;
	}

	return make_pair(x, y);
}

int CommandLineInterface::askGridSize()
{
	int size = -1;

	while (size < 3 || size > 100)
	{
		cout << "Podaj rozmiar siatki (>=3 ^ <=100): ";
		cin >> size;
	}

	cout << "Podany rozmiar: " << size << endl;

	gridSize = size;

	return size;
}

int CommandLineInterface::askRowCount()
{
	int rows = -1;

	while (rows < 3 || rows > gridSize)
	{
		cout << "Podaj ilosc znakow w rzedzie (>=3 ^ <=" << gridSize << "): ";
		cin >> rows;
	}

	cout << "Podana ilosc znakow: " << rows << endl;

	rowCount = rows;

	return rows;
}

void CommandLineInterface::printGrid()
{
	int** grid = tt->getGrid();

	for (int i = 0; i < gridSize; i++)
	{
		cout << endl;
		for (int j = 0; j < gridSize; j++)
		{
			if(grid[i][j] == 0)
				cout << "  ";
			else if (grid[i][j] == 1)
				cout << " x";
			else if (grid[i][j] == 2)
				cout << " o";

			cout << ((j == gridSize - 1) ? " \n" : " |");
		}

		if(i < gridSize - 1)
			for (int i = 0; i < gridSize; i++)
				cout << "----";
	}

	cout << endl;
}

void CommandLineInterface::printResults()
{
	printGrid();
	if (tt->isWinningMove(1))
		cout << "Uzytkownik wygrywa!\n";
	else if (tt->isWinningMove(2))
		cout << "Komputer wygrywa!\n";
	else
		cout << "Remis!\n";
}


bool CommandLineInterface::isGameOver()
{
	return tt->isGameOver();
}

void CommandLineInterface::userChoice()
{
	pair<int, int> coords = getCoords();

	while (tt->getGrid()[coords.first][coords.second] != 0)
		coords = getCoords();

	tt->userChoice(coords.first, coords.second);
}

void CommandLineInterface::computerChoice()
{
	tt->makeChoice();
}
