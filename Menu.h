#ifndef MENU_H
#define MENU_H 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include "Game.h"
#include "Picross.h"
using namespace std;

class Menu	//menu class for user traversal
{

public:
	Menu();	//standard constructor
	~Menu();	//standard destructor
	void selectGame();	//sets which game is being played
	void selectPuzzle();	//selects a specific puzzle
	void makeMove();	//makes a move
	void userMenu();	//the user invokes this if they want to open a help menu, or exit the program during a puzzle
	void readString(string);	//reads a string and acts accordingly
	void setRow(int a);	//sets the passRow variable
	void setColumn(int a);	//sets the passColumn variable
	bool isWin(); //checks if the game is won
	bool isPlaying(); //checks if the user still wants to play
	int getRow();	//passes row for Evan's class functions
	int getColumn();	//passes column for Evan's class functions
private:
	ifstream instructions;	//for opening instructions
	bool playing;	//used to track if the user is still wanting to play
	int userMenuType; 	//stores whatever the user types in userMenu
	int game;	//stores game choice
	int choice;	//used to store User choices for switch statements
	int passRow;	//used to pass the row to Evan's classes
	int passColumn;	//used to pass the column to Evan's classes
	string puzzle;	//stores puzzle name
	string readIt;		//used for string function actions
};

Menu::Menu()
{
	selectGame();
	selectPuzzle();
	playing = true;
};
Menu::~Menu()
{

};

void Menu::selectGame()
{
	cout << "Please pick a number between 1 and 2:" << endl << "1=picross   2=rullo" << endl << "Or type 9 to exit." << endl;
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		cout << "Cool! You picked Picross!" << endl;
		break;
	case 2:
		cout << "Neat! Rullo Rules!" << endl;
		break;
	case 9:
		cout << "Sorry to see you go, but have a nice day." << endl;
		playing = false;
		break;
	default://change this to either recurse or exit
		cout << "You miscreant! It's Nonograms for you!" << endl;
		choice = 1;
		break;
	}
	game = choice;
};
void Menu::selectPuzzle()
{
	cout << "Now, please select a puzzle name: ";
	cin >> puzzle;
	cout << endl << "thanks! you will open " << puzzle << "!" << endl;

};
void Menu::readString(string a)
{
	
	int i = 0;
	int j = 0;
	if (isdigit(a.c_str()[0]))
		i = 1;
	else if (isalpha(a.c_str()[0]))
		i = 2;
	switch (i)
	{
	case 1:
		//pass integers to row and column
		for (unsigned int x = 0; x < strlen(a.c_str()); x++)
			if (a[x] == ' ')
			{
				setRow(atoi((a.substr(0, x)).c_str()));
				setColumn(atoi((a.substr(x + 1, strlen(a.c_str())).c_str())));
			}
		break;
	case 2:
		if (a == "help")
		{
			if (game == 1)
				instructions.open("NonogramRules.txt");
			else if (game == 2)
				instructions.open("RulloRules.txt");
			while (getline(instructions, readIt))
			{
				cout << readIt << endl;
			}
			instructions.close();
		}
		else if (a == "menu")
		{
			userMenu();
		}
		else if (a == "exit")
		{
			playing = false;
		}
		break;
	default:
		cout << "Sorry, I didn't catch that. Please try again." << endl;
		cin >> readIt;
		cout << endl;
		readString(readIt);
	}
};
void Menu::makeMove()
{

};
void Menu::userMenu()
{
	cout << "Hello there. What would you like help with?" << endl;
	cout << "If you would like instructions, type 1. If you would like to exit our game, type 9. Otherwise, type 5 to return to your game." << endl;
	cin >> userMenuType;

	switch (userMenuType) {
	case 1:
		//print instructions for the current game type
		if (game = 1)
		{
			cout << "These are Picross rules!" << endl;
		}
		else if (game = 2)
		{
			cout << "These are the rules of Rullo!" << endl;
			cout << "In this game you have a board full of numbers, and your goal is to make the sum of every row and column equal to the number in the box next to it." << endl;
			cout << "At the start of each game all of the numbers will be 'on', and you get to turn numbers on and off until the game is won." << endl;
			cout << "To choose a square, tyle the X/Y co-ordinates (not the number in the grid." << endl;

			//this is assuming console input
		}
		break;
	case 5:
		cout << "Okay! let's try that again!" << endl;
		cin >> readIt;
		cout << endl;
		readString(readIt);
		break;
	case 9:
		cout << "Sorry to see you go, but have a nice day." << endl;
		playing = false;
		//find some way to force exit the program. a new function?
		//-----------------------------------------------------------------------------
		//std::exit;
		//----------------------------------------------------------------------------
		break;
	default:
		break; //yes, this is the same as case 5
	}
};
void Menu::setRow(int a)
{
	passRow = a;
};
void Menu::setColumn(int a)
{
	passColumn = a;
};

bool Menu::isWin()
{
	// needs to be properly coded
	return 0;
};
bool Menu::isPlaying()
{
	return playing;
};

int Menu::getRow()
{
	return passRow;
};
int Menu::getColumn()
{
	return passColumn;
};

#endif
