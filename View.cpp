#include "View.h"

int main() {

	View test;

	if (!test.getPuzzle("C:\\Users\\John\\Desktop\\puzzleTest.txt"))
		return -1;

	test.draw();

	system("pause");
	return 0;
}