#ifndef MENU_H
#define MENU_H 1

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class menuSys	//menu class for user traversal
{

public:
	menuSys();	//standard constructor
	~menuSys();	//standard destructor
	void selectGame();	//sets which game is being played
	void selectPuzzle();	//selects a specific puzzle
	void makeMove();	//makes a move
	void userMenu();	//the user invokes this if they want to open a help menu, or exit the program during a puzzle
	bool isWin(); //checks if the game is won
	bool isPlaying(); //checks if the user still wants to play
	void readString(string a);	//reads a string and acts accordingly
private:
	string puzzle;	//stores puzzle name
	int game;	//stores game choice
	int choice;	//used to store User choices for switch statements
	bool isPlaying;	//used to track if the user is still wanting to play
};

void menuSys::selectGame()
{
	int a;
	cout << "Please pick a number between 1 and 2:" << endl << "1=picross   2=rullo" << endl << "Or type 9 to exit." << endl;
	cin >> a;
	cout << endl;
	switch (a)
	{
	case '1':
		cout << "Cool! You picked Picross!" << endl;
		break;
	case '2':
		cout << "Neat! Rullo Rules!" << endl;
		break;
	case '9':
		cout << "Sorry to see you go, but have a nice day." << endl;
		isPlaying = FALSE;
		break;
	default://change this to either recurse or exit
		cout << "You miscreant! It's Nonograms for you!" << endl;
		a = 1;
		break;
	}
	game = a;
};
void menuSys::selectPuzzle()
{
	cout << "Now, please select a puzzle name: ";
	cin >> puzzle;
	cout << endl << "thanks! you will open " << puzzle << "!" << endl;
	
};
void menuSys::readString(string a)
{
	
};
void menuSys::makeMove()
{

};
bool menuSys::isWin()
{

};
bool menuSys::isPlaying()
{
	
};
void menuSys::userMenu()
{
	cout << "Hello there. What would you like help with?" << endl;
};
menuSys::menuSys()
{
menuSys.selectGame();
menuSys.selectPuzzle();
menuSys.isPlaying=TRUE;
};
menuSys::~menuSys()
{

};

#endif
