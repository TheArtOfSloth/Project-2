#ifndef VIEW_H
#define VIEW_H 1

#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

#include "Game.h"
#include "Picross.h"
#include "Rullo.h"

// L = left, D = down, U = up, R = right, H = highlighted
enum Unicode {
	DR = 218, LR = 196, LDR = 194, LD = 191, DU = 179, DUR = 195,
	LDUR = 197, UR = 192, LUR = 193, LU = 217, LDU = 180, H = 219
};

class View
{
public:
	View(Picross picross) : game(&picross), displayNum(false) {}	// Constructor for picross
	View(Rullo rullo) : game(&rullo), displayNum(true) {}			// Constructor for rullo
	void playGame();												// While-loop for current game
	~View() {}														// Destructor
private:
	void draw();													// Draw board
	void formatInt(int);											// Handle integer formatting
	void formatSpace(int, int);										// Handle active board space (row, column)
	void inputHandler();											// Output and handle user input
	Game *game;
	bool displayNum;
	string input;
};

void View::playGame()
{
	input = "";
	while (!game->isWin() || input != "EXIT")
	{
		system("CLS");
		draw();
		inputHandler();
		cout << endl;
	}
}

void View::draw()
{
	for (int i = 0; i < game->getRowKeyWidth(); i++) cout << "   "; cout << "    "; for (int i = 1; i <= game->getNumCols(); i++) { if (i <= 9) cout << i << "   "; else cout << i << "  "; } cout << endl;
	for (int i = 0; i < game->getRowKeyWidth(); i++) cout << "   "; cout << "    " << (char)DR; for (int i = 0; i < game->getNumCols(); i++) { if (i < game->getNumCols() - 1) cout << (char)LR << (char)LR << (char)LDR; else cout << (char)LR << (char)LR << (char)LD << endl; }
	for (int i = 0; i < game->getColKeyHeight(); i++)
	{
		for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "    " << (char)DU; for (int j = 0; j < game->getNumCols(); j++) { formatInt(game->getColKey(i, j)); if (j < game->getNumCols() - 1) cout << (char)DU; else cout << (char)DU << endl; }
		if (i < game->getColKeyHeight() - 1) { for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "  " << (char)DUR; for (int j = 0; j < game->getNumCols(); j++) { if (j < game->getNumCols() - 1) cout << (char)LR << (char)LR << (char)LDUR; else cout << (char)LR << (char)LR << (char)LDU << endl; } }
		else { for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "    " << (char)UR; for (int j = 0; j < game->getNumCols(); j++) { if (j < game->getNumCols() - 1) cout << (char)LR << (char)LR << (char)LUR; else cout << (char)LR << (char)LR << (char)LU << endl; } }
	}
	cout << (char)DR; for (int i = 0; i < game->getRowKeyWidth(); i++) { cout << (char)LR << (char)LR; if (i < game->getRowKeyWidth() - 1) cout << (char)LDR; else cout << (char)LD; }
	cout << (char)DR; for (int i = 0; i < game->getNumCols(); i++) { cout << (char)LR << (char)LR; if (i < game->getNumCols() - 1) cout << (char)LDR; else cout << (char)LD << endl; }
	char guide = 'A';
	for (int i = 0; i < game->getNumRows(); i++)
	{
		cout << guide++ << " " << (char)DU; for (int j = 0; j < game->getRowKeyWidth(); j++) { formatInt(game->getRowKey(i, j)); cout << (char)DU; }
		cout << (char)DU; for (int j = 0; j < game->getNumCols(); j++) { formatSpace(i, j); cout << (char)DU; } cout << endl;
		if (i < game->getNumRows() - 1)
		{
			cout << "  " << (char)DUR; for (int j = 0; j < game->getRowKeyWidth() - 1; j++) cout << (char)LR << (char)LR << (char)LDUR; cout << (char)LR << (char)LR << (char)LDU;
			cout << (char)DUR; for (int j = 0; j < game->getNumCols() - 1; j++) cout << (char)LR << (char)LR << (char)LDUR; cout << (char)LR << (char)LR << (char)LDU << endl;
		}
		else
		{
			cout << "  " << (char)UR; for (int i = 0; i < game->getRowKeyWidth(); i++) { cout << (char)LR << (char)LR; if (i < game->getRowKeyWidth() - 1) cout << (char)LUR; else cout << (char)LU; }
			cout << (char)UR; for (int i = 0; i < game->getNumCols(); i++) { cout << (char)LR << (char)LR; if (i < game->getNumCols() - 1) cout << (char)LUR; else cout << (char)LU << endl; }
		}
	}
}

void View::formatInt(int integer)
{
	if (integer == 0) cout << "  ";
	else if (integer <= 9) cout << integer << " ";
	else cout << integer;
}

void View::formatSpace(int row, int col)
{
	if (game->getBoard(row, col)->boolean) cout << (char)H << (char)H;
	else if (displayNum) formatInt(game->getBoard(row, col)->integer);
	else cout << "  ";
}

void View::inputHandler()
{
	cout << endl;
	system("pause");
	return;
}

#endif
