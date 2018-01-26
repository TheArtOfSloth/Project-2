#include "View.h"

int main() {
	View test;
	if (!test.getPuzzle("C:\\Users\\John\\Desktop\\puzzleTest.txt"))
		return -1;

	char col;
	int row;
	int answersLeft;
	//std::cin >> col >> row;
	while (View::play()) {
		test.draw();
		std::cin >> col >> row;
	}

	system("pause");
	return 0;

}