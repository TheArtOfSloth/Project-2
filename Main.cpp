#include"Game.h"
#include"Picross.h"
#include"Rullo.h"
#include"View.h"
using namespace std;

int main()
{
	Space **sol = new Space*[10];
	for (int i = 0; i < 10; i++)
	{
		sol[i] = new Space[10];
		for (int j = 0; j < 10; j++)
		{
			sol[i][j].boolean = false;
		}
	}
	//Rullo *rullo = new Rullo("puzzle1.txt");
	//View *view = new View(*rullo);
	sol[5][5].boolean = true;

	Rullo *rullo = new Rullo(sol, 10, 10);
	View *view = new View(*(rullo));

	view->playGame();

	system("pause");
	return 0;
}
