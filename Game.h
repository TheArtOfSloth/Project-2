#ifndef GAME_H
#define GAME_H 1

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

#include<cstdlib>
#include<ctime>

// Space struct
// Object to hold an integer and a boolean value corresponding with a row or column
// Note: Call the desired value using the "->" operator after calling the appropriate function
// Note: Some puzzle types may not utilize certain values

struct Space
{
	int integer;
	bool boolean;
};

// Game class (abstract)
// Note: Inputted row and column values go from 0 to n-1 (anything else is out of bounds)

class Game
{
public:
	Game();                                                 // Default constructor: initializes all values to 0 or null
	Game(string);											// Constructor to load game from file
	Game(Space**, int, int);                                // Constructor to load custom game (only initializes solution, row, and column)
	virtual int getNumRows() const = 0;                     // Getter for the number of rows in puzzle
	virtual int getNumCols() const = 0;                     // Getter for the number of columns in puzzle
	virtual int getRowKeyWidth() const = 0;                 // Getter for the number of columns in the row key (calculated on call)
	virtual int getColKeyHeight() const = 0;                // Getter for the number of tows in the column key (calculated on call)
	virtual int getRowKey(int, int) const = 0;              // Return int from the row key (-1 if out of bounds)
	virtual int getColKey(int, int) const = 0;              // Return int from the column key (-1 if out of bounds)
	virtual Space * getSolution(int, int) const = 0;		// Return Space object from solution (null if out of bounds)
	virtual Space * getBoard(int, int) const = 0;           // Return Space object from board (null if out of bounds)
	virtual bool isWin() const = 0;                         // Boolean function to hold winning conditions (put in while-loop)
	virtual void move(int, int, int) = 0;                   // Modifies the appropriate value when a certain space is invoked
	virtual void createGame(Space**, int, int) = 0;			// Overwrites current game with game of same type (resets board)
	virtual void loadGame(string) = 0;                      // Load game from a .txt file (returns blank game if file DNE)
	virtual void saveGame(string) = 0;						// Save game to a .txt file
	virtual ~Game() = 0;                                    // Destructor
protected:
	int numRows, numCols, colKeyHeight, **rowKey, **colKey;
	Space **solution, **board;
	virtual void generateKeys() = 0;
};


// Base virtual functions to be inherited regardless of game type (may be overwritten depending on game)

Game::Game() : numRows(0), numCols(0), rowKey(nullptr), colKey(nullptr), solution(nullptr), board(nullptr) {}

Game::Game(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file.good()) numRows = 0, numCols = 0, solution = nullptr, board = nullptr, rowKey = nullptr, colKey = nullptr;
	else
	{
		file >> numRows;
		file >> numCols;
		board = new Space*[getNumRows()];
		solution = new Space*[getNumRows()];
		for (int row = 0; row < getNumRows(); row++)
		{
			board[row] = new Space[getNumCols()];
			solution[row] = new Space[getNumCols()];
			for (int col = 0; col < getNumCols(); col++)
			{
				board[row][col].integer = (rand() % 10) + 1;
				board[row][col].boolean = false;
				solution[row][col].integer = board[row][col].integer;
				solution[row][col].boolean = false;
			}
		}
		int row, col;
		while (!file.eof())
		{
			file >> row;
			file >> col;
			solution[row][col].boolean = true;
		}
	}
	file.close();
}

Game::Game(Space **sol, int row, int col) : numRows(row), numCols(col), solution(sol)
{
	board = new Space*[getNumRows()];
	for (int i = 0; i < getNumRows(); i++)
	{
		board[i] = new Space[getNumCols()];
		for (int j = 0; j < getNumCols(); j++)
		{
			board[i][j].integer = solution[i][j].integer;
			board[i][j].boolean = false;
		}
	}
}

int Game::getNumRows() const { return numRows; }

int Game::getNumCols() const { return numCols; }

int Game::getRowKeyWidth() const { return 0; }

int Game::getColKeyHeight() const { return 0; }

int Game::getRowKey(int row, int col) const { return (row >= getNumRows() || row < 0 || col >= getRowKeyWidth() || col < 0) ? -1 : rowKey[row][col]; }

int Game::getColKey(int row, int col) const { return (row >= getColKeyHeight() || row < 0 || col >= getNumCols() || col < 0) ? -1 : colKey[row][col]; }

Space * Game::getSolution(int row, int col) const { return (row >= getNumRows() || row < 0 || col >= getNumCols() || col < 0) ? nullptr : &solution[row][col]; }

Space * Game::getBoard(int row, int col) const { return (row >= getNumRows() || row < 0 || col >= getNumCols() || col < 0) ? nullptr : &board[row][col]; }

bool Game::isWin() const
{
	for (int row = 0; row < getNumRows(); row++)
	{
		for (int col = 0; col < getNumCols(); col++)
		{
			if (board[row][col].boolean != solution[row][col].boolean) return false; else;
		}
	}
	return true;
}

void Game::move(int row, int col, int val = 0)
{
	if (row < 0 || row >= getNumRows() || col < 0 || col >= getNumCols()) return;
	else board[row][col].boolean = !board[row][col].boolean;
}

void Game::createGame(Space **sol, int row, int col)
{
	for (int i = 0; i < numRows; i++)
	{
		delete[] rowKey[i];
		delete[] solution[i];
		delete[] board[i];
	}
	for (int i = 0; i < getColKeyHeight(); i++) delete[] colKey[i];
	solution = sol, numRows = row, numCols = col;
	board = new Space*[getNumRows()];
	for (int i = 0; i < getNumRows(); i++)
	{
		board[i] = new Space[getNumCols()];
		for (int j = 0; j < getNumCols(); j++)
		{
			board[i][j].integer = solution[i][j].integer;
			board[i][j].boolean = false;
		}
	}
	rowKey = nullptr, colKey = nullptr;
}

void Game::loadGame(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file.good()) return;
	else
	{
		file >> numRows;
		file >> numCols;
		board = new Space*[getNumRows()];
		solution = new Space*[getNumRows()];
		for (int row = 0; row < getNumRows(); row++)
		{
			board[row] = new Space[getNumCols()];
			solution[row] = new Space[getNumCols()];
			for (int col = 0; col < getNumCols(); col++)
			{
				board[row][col].integer = (rand() % 10) + 1;
				board[row][col].boolean = false;
				solution[row][col].integer = board[row][col].integer;
				solution[row][col].boolean = false;
			}
		}
		int row, col;
		while (!file.eof())
		{
			file >> row;
			file >> col;
			solution[row][col].boolean = true;
		}
		file.close();
	}
}

void Game::saveGame(string filename)
{
	ifstream exists;
	exists.open(filename);
	if (exists.good()) return; else exists.close();
	ofstream file;
	file.open(filename);
	file << getNumRows() << " " << getNumCols() << endl;
	for (int i = 0; i < getNumRows(); i++)
	{
		for (int j = 0; j < getNumCols(); j++)
		{
			if (solution[i][j].boolean) file << i << " " << j << endl; else;
		}
	}
	file.close();
}

Game::~Game()
{
	for (int i = 0; i < numRows; i++)
	{
		delete[] rowKey[i];
		delete[] solution[i];
		delete[] board[i];
	}
	for (int i = 0; i < getColKeyHeight(); i++) delete[] colKey[i];
}

#endif

