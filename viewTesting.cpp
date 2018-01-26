#include "View.h"

int main() {
	View test;
	if (!test.getPuzzle("C:\\Users\\John\\Desktop\\puzzleTest.txt"))
		return -1;

	char col;
	int row;
	
	//Dummy loop for testing purposes
	int i = 0;
	while (i < 10) {
		test.draw();

		std::cin >> col >> row;
		test.userAnswer(col, row);
		i++;
	}


	test.draw();

	system("pause");
	return 0;

}