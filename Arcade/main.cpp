#include "Arcade.h"

void main()
{
	Arcade start;

	try
	{
		start.StartArcade();
	}
	catch (...)
	{
		cout << "Something's wrong. Exiting the program." << endl;
		exit(1);
	}
}