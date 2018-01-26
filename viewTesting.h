#pragma once
/* TODO: Implement method to resize grid for > 10. 
 * TODO: Test out view with Evan's puzzles w/ Navi.
 * TODO: Test user input works with draw method.
 * TODO: Decouple score & grid (solution grid)
 */


#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
class View {
	int width;
	int height;
	int grid[12][12];
	int answersLeft = 5; //From my sample test case file. Fit to other puzzles later.
	std::vector<std::pair<int, int>> answers;
	//enum gameState { PLAY, END, QUIT };
public:
	View();
	void userAnswer(char letter, int row);
	void updateAnswerGrid(int col, int row, int& grid);
	bool getPuzzle(const std::string file);
	bool checkAnswer(std::pair<int, int> &answers);
	void fillAnswers(std::pair<int, int> &answer);
	void draw();
	void init(); //Maybe just put this in constructor.
	//bool continuePlaying(gameState &state); //For polling loop of the game match.
	//gameState setGameState = PLAY;
	//gameState endGame(std::string response);

};

void View::init() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			grid[i][j] = 0; //Lazy boolean grid.
		}
	}
}

/*gameState View::endGame(std::string response) {
	
}

bool View::continuePlaying(gameState &state) {
	return state;
}*/

//Check the value the user input matches one of the answers in our puzzle.
bool View::checkAnswer(std::pair<int, int> &userAnswer) {
	int i = 0;
	for (auto it : answers) {
		if (userAnswer.first == answers.at(i).first
			&&
			userAnswer.second == answers.at(i).second) 
		{
			answersLeft--; //Decrement remaining values to check.
			return true;
		}
		i++;
	}
	return false;
}

View::View() {
	width = 12; //Default to 10 for width and height
	height = 12;
	init();
}



void View::userAnswer(char letter, int row) {
	//Translate letter to int value for puzzle
	int col = toupper(letter) - 65;
	std::pair<int, int> choice;
	choice.first = row;
	choice.second = col;

	if (checkAnswer(choice))
		updateAnswerGrid(col, row, grid[row][col]);

}

void View::updateAnswerGrid(int col, int row, int& grid) {
	grid = 1;

	std::cout << grid << std::endl;

}

void View::draw() {
	//Helpful letters for column listing.
	//Like a bad actor, this for loop's been typecasted.
	for (int i = 0; i < width; i++) {
		std::cout << "   " << ((char)(i + 65));
	}

	std::cout << std::endl;

	for (int i = 0; i < width; i++) {
		if (i < 10) //Append a zero in front of values.
			std::cout << "0";

		//REMOVE : TESTING PURPOSES ONLY
		//grid[5][5] = 1; grid[6][4] = 1;

		std::cout << i << "|";
		for (int j = 0; j < height; j++) {
			if (grid[i][j]) { //Check if answer was selected.
				std::cout << "Q "; //Feel free to change marker.
			}
			else {
				std::cout << "  ";
			}
			std::cout << "| ";
		}
		std::cout << std::endl;
	}
}


void View::fillAnswers(std::pair<int, int> &answer) {
	answers.push_back(answer);
}

bool View::getPuzzle(const std::string file) {
	std::ifstream solutionFile(file);

	//File does not exist or cannot be opened.
	if (!solutionFile)
		return false;

	int i, j; //Iterators to capture int values in file.
	std::pair<int, int> answer; //<-- Individual pair value.

	while (solutionFile >> i >> j) {
		answer.first = i;
		answer.second = j;
		fillAnswers(answer);
	}

	solutionFile.close();
	return true;
}