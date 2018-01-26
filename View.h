#pragma once
#include <windows.h> //Interact with Windows OS. For mouse events.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//enum GameState { PLAY, END }; //For polling loop or other spinlock structure.

class View {
	//Dimensions of the grid itself.
	int width;
	int height;
	int score;
	//Vector for the actual grid of the game board itself.
	std::vector<std::pair<int,int>> grid;
	//List of actual solutions for the particular puzzle.
	std::vector<std::pair<int, int>> answers;
	std::vector<std::pair<int, int>> validator;
	//For the individual user input for a given coordinate point.
	std::pair<int, int> answer;

	//Allocate answer buffer
	void fillAnswers(std::pair<int, int> &answer);
	void setGrid(int& width, int& height, std::vector<std::pair<int, int>> &grid);
	//Grid helper
	 //(const std::pair<int, int>& tile);
public:
	View();
	void draw(); //Make grid
	bool getPuzzle(const std::string file); //Open file for puzzle solution
	//Checks if a given tile has been correctly selected or not.
	bool correctTile(const std::vector<std::pair<int,int>> &answers, int i); 
};

void View::setGrid(int& width, int& height, std::vector<std::pair<int, int>> &grid) {
	width = 10;
	height = 10;
	std::pair<int, int> tile;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			tile.first = i;
			tile.second = j;
			grid.push_back(tile);
		}
	}

}

View::View() {
	width = 10;
	height = 10;
	score = 0;
	setGrid(width, height, grid);
}

bool View::correctTile(const std::vector<std::pair<int, int>> &answers, int i) {
	return ((answers.at(i).first && answers.at(i).second) == (validator.at(i).first && validator.at(i).second));
}

void View::draw() {

	int rowCtr = 0;
	int valCheck = 0;

	for (auto &it : grid) {
		if (rowCtr == width)
			std::cout << std::endl;

		std::cout << " | ";
		if (correctTile(grid, valCheck))
			std::cout << "X";
		else
			std::cout << " ";

		std::cout << " |";

		valCheck++;
	}

}
//Helper function to fill the answer vector.
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