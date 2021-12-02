#pragma once
#include "GameList.h"

enum class MENU_OPTIONS {
	OPTION_ONE = 1, OPTION_TWO, OPTION_THREE, OPTION_FOUR,
	OPTION_FIVE, OPTION_SIX, OPTION_SEVEN, OPTION_EIGHT,
	OPTION_NINE, OPTION_TEN
};

class Arcade
{
public:
	//Constructor
	Arcade() = default;

	//Destructor
	~Arcade();

	//Methods
	void StartArcade();
	int PrintGameMenu();
	void OptionOneFromMenu(int& currGameIndex);
	void OptionTwoFromMenu(int& currGameIndex);
	void OptionThreeFromMenu(int& currGameIndex);
	void OptionFourFromMenu(int& currGameIndex);
	void OptionFiveFromMenu(Game* currGame);
	void OptionSixFromMenu(Game* currGame);
	void OptionSevenFromMenu(Game* currGame);
	void OptionEightFromMenu();
	void OptionNineFromMenu(int& currGameIndex);
	void OptionTenFromMenu(int& currGameIndex);
	Game* CreateNewGame(int gameSelection);
	void ConvertUserPositionsToSystemPosition(Position*& posArr, const int size);

private:
	const array<const string, 3> m_GamesName = {"Checkers", "Amazons", "Chess" };
	vector<Game*> m_GameList;
};