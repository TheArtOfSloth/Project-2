#ifndef RULLO_H
#define RULLO_H 1

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

#include<cstdlib>
#include<ctime>

#include "Game.h"

class Rullo : public Game
{
public:
	Rullo() : Game() {}
	Rullo(string);
	Rullo(Space**, int, int);
	virtual int getNumRows() const { return Game::getNumRows(); }
	virtual int getNumCols() const { return Game::getNumCols(); }
	virtual int getRowKeyWidth() const { return 1; }
	virtual int getColKeyHeight() const { return 1; }
	virtual int getRowKey(int row, int col) const { return Game::getRowKey(row, col); }
	virtual int getColKey(int row, int col) const { return Game::getColKey(row, col); }
	virtual Space * getSolution(int row, int col) const { return Game::getSolution(row, col); }
	virtual Space * getBoard(int row, int col) const { return Game::getBoard(row, col); }
	virtual bool isWin() const { return Game::isWin(); }
	virtual void move(int row, int col, int val = 0) { Game::move(row, col, 0); }
	virtual void createGame(Space**, int, int);
	virtual void loadGame(string);
	virtual void saveGame(string filename) { Game::saveGame(filename); }
	virtual ~Rullo() { Game::~Game(); }
private:
	virtual void generateKeys();
	void randomize();
};

Rullo::Rullo(string filename) : Game(filename)
{
	colKeyHeight = getColKeyHeight();
	randomize();
	generateKeys();
}

Rullo::Rullo(Space **sol, int row, int col) : Game(sol, row, col)
{
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

void Rullo::createGame(Space **sol, int row, int col)
{
	Game::createGame(sol, row, col);
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

void Rullo::loadGame(string filename)
{
	Game::loadGame(filename);
	colKeyHeight = getColKeyHeight();
	randomize();
	generateKeys();
}

void Rullo::generateKeys()
{
	rowKey = new int*[getNumRows()];
	for (int i = 0; i < getNumRows(); i++)
	{
		rowKey[i] = new int[getRowKeyWidth()];
		rowKey[i][0] = 0;
		for (int j = 0; j < getNumCols(); j++)
		{
			if (solution[i][j].boolean) rowKey[i][0] += solution[i][j].integer; else;
		}
	}
	colKey = new int*[getColKeyHeight()];
	colKey[0] = new int[getNumCols()];
	for (int i = 0; i < getNumCols(); i++)
	{
		colKey[0][i] = 0;
		for (int j = 0; j < getNumRows(); j++)
		{
			if (solution[j][i].boolean) colKey[0][i] += solution[j][i].integer; else;
		}
	}
}

void Rullo::randomize()
{
	for (int row = 0; row < getNumRows(); row++)
	{
		for (int col = 0; col < getNumCols(); col++)
		{
			solution[row][col].integer = (rand() % 10) + 1;
			board[row][col].integer = solution[row][col].integer;
		}
	}
}

#endif
