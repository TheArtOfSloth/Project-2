#ifndef PICROSS_H
#define PICROSS_H 1

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

#include<cstdlib>
#include<ctime>

#include "Game.h"

class Picross : public Game
{
public:
	Picross() : Game() {}
	Picross(string);
	Picross(Space**, int, int);
	virtual int getNumRows() const { return Game::getNumRows(); }
	virtual int getNumCols() const { return Game::getNumCols(); }
	virtual int getRowKeyWidth() const { return ((numCols % 2 == 1) ? (numCols + 1) / 2 : numCols / 2); }
	virtual int getColKeyHeight() const { return ((numRows % 2 == 1) ? (numRows + 1) / 2 : numRows / 2); }
	virtual int getRowKey(int row, int col) const { return Game::getRowKey(row, col); }
	virtual int getColKey(int row, int col) const { return Game::getColKey(row, col); }
	virtual Space * getSolution(int row, int col) const { return Game::getSolution(row, col); }
	virtual Space * getBoard(int row, int col) const { return Game::getBoard(row, col); }
	virtual bool isWin() const { return Game::isWin(); }
	virtual void move(int row, int col, int val = 0) { Game::move(row, col, 0); }
	virtual void createGame(Space**, int, int);
	virtual void loadGame(string);
	virtual void saveGame(string filename) { Game::saveGame(filename); }
	virtual ~Picross() { Game::~Game(); }
private:
	virtual void generateKeys();
};

Picross::Picross(string filename) : Game(filename)
{
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

Picross::Picross(Space **sol, int row, int col) : Game(sol, row, col)
{
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

void Picross::createGame(Space** sol, int row, int col)
{
	Game::createGame(sol, row, col);
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

void Picross::loadGame(string filename)
{
	Game::loadGame(filename);
	colKeyHeight = getColKeyHeight();
	generateKeys();
}

void Picross::generateKeys()
{
	rowKey = new int*[getNumRows()];
	for (int i = 0; i < getNumRows(); i++)
	{
		rowKey[i] = new int[getRowKeyWidth()];
		for (int j = 0; j < getRowKeyWidth(); j++) rowKey[i][j] = 0;
	}
	colKey = new int*[getColKeyHeight()];
	for (int i = 0; i < getColKeyHeight(); i++)
	{
		colKey[i] = new int[getNumCols()];
		for (int j = 0; j < getNumCols(); j++) colKey[i][j] = 0;
	}
	for (int i = getNumRows() - 1; i >= 0; i--)
	{
		int temp = getRowKeyWidth() - 1;
		for (int j = getNumCols() - 1; j >= 0; j--)
		{
			if (!solution[i][j].boolean && rowKey[i][temp] > 0) temp--;
			else if (!solution[i][j].boolean);
			else rowKey[i][temp]++;
		}
	}
	for (int i = getNumCols() - 1; i >= 0; i--)
	{
		int temp = getColKeyHeight() - 1;
		for (int j = getNumRows() - 1; j >= 0; j--)
		{
			if (!solution[j][i].boolean && colKey[temp][i] > 0) temp--;
			else if (!solution[j][i].boolean);
			else colKey[temp][i]++;
		}
	}
}

#endif
