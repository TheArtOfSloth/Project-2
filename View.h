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
char DR = (char) 218; char LR = (char) 196; char LDR = (char) 194; char LD = (char) 191; char DU = (char) 179; char DUR = (char) 195;
char LDUR = (char) 197; char UR = (char) 192; char LUR = (char) 193; char LU = (char) 217; char LDU = (char) 180; char H = (char) 219;

class View
{
public:
	View(Picross *picross) : game(picross), displayNum(false) {}	// Constructor for picross
	View(Rullo *rullo) : game(rullo), displayNum(true) {}			// Constructor for rullo
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
		return;
		cout << endl;
	}
}

void View::draw()
{
	for (int i = 0; i < game->getRowKeyWidth(); i++) cout << "   "; cout << "    "; for (int i = 1; i <= game->getNumCols(); i++) { if (i <= 9) {formatInt(i); cout << " ";} else {formatInt(i); cout << " "; }} cout << endl;
	for (int i = 0; i < game->getRowKeyWidth(); i++) cout << "   "; cout << "   " << DR; for (int i = 0; i < game->getNumCols(); i++) { if (i < game->getNumCols() - 1) cout << LR << LR << LDR; else cout << LR << LR << LD; } cout << endl;
	for (int i = 0; i < game->getColKeyHeight(); i++)
	{
		for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "   " << DU; for (int j = 0; j < game->getNumCols(); j++) { formatInt(game->getColKey(i, j)); if (j < game->getNumCols() - 1) cout << DU; else cout << DU << endl; }
		if (i < game->getColKeyHeight() - 1) { for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "  " << DUR; for (int j = 0; j < game->getNumCols(); j++) { if (j < game->getNumCols() - 1) cout << LR << LR << LDUR; else cout << LR << LR << LDU << endl; } }
		else { for (int j = 0; j < game->getRowKeyWidth(); j++) cout << "   "; cout << "   " << UR; for (int j = 0; j < game->getNumCols(); j++) { if (j < game->getNumCols() - 1) cout << LR << LR << LUR; else cout << LR << LR << LU << endl; } }
	}
	cout << "  " << DR; for (int i = 0; i < game->getRowKeyWidth(); i++) { if (i < game->getRowKeyWidth() - 1) cout << LR << LR << LDR; else cout << LR << LR << LD; }
	cout << DR; for (int i = 0; i < game->getNumCols(); i++) { if (i < game->getNumCols() - 1) cout << LR << LR << LDR; else cout << LR << LR << LD << endl; }
	char guide = 'A';
	for (int i = 0; i < game->getNumRows(); i++)
	{
		cout << guide++ << " " << DU; for (int j = 0; j < game->getRowKeyWidth(); j++) { formatInt(game->getRowKey(i, j)); cout << DU; }
		cout << DU; for (int j = 0; j < game->getNumCols(); j++) { formatSpace(i, j); cout << DU; } cout << endl;
		if (i < game->getNumRows() - 1)
		{
			cout << "  " << DUR; for (int j = 0; j < game->getRowKeyWidth() - 1; j++) cout << LR << LR << LDUR; cout << LR << LR << LDU;
			cout << DUR; for (int j = 0; j < game->getNumCols() - 1; j++) cout << LR << LR << LDUR; cout << LR << LR << LDU << endl;
		}
		else
		{
			cout << "  " << UR; for (int i = 0; i < game->getRowKeyWidth(); i++) { cout << LR << LR; if (i < game->getRowKeyWidth() - 1) cout << LUR; else cout << LU; }
			cout << UR; for (int i = 0; i < game->getNumCols(); i++) { cout << LR << LR; if (i < game->getNumCols() - 1) cout << LUR; else cout << LU << endl; }
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
	if (game->getBoard(row, col)->boolean) cout << H << H;
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
