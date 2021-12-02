#include "Arcade.h"

Arcade::~Arcade()
{
	int size = m_GameList.size();

	for(int i = 0 ; i < size ; ++i)
	{
		m_GameList[i]->~Game();
	}
}

void Arcade::StartArcade()
{//the main method of the game, this method activates the menu and creates a game list.
	int choice(0), currGameIndex(0);

	cout << "*********************************************" << endl;
	cout << "*******WELCOME TO THE ARCADE PROJECT!!!******" << endl;

	while ((MENU_OPTIONS)choice != MENU_OPTIONS::OPTION_EIGHT)
	{
		try
		{
			choice = PrintGameMenu();

			switch ((MENU_OPTIONS)choice)
			{
			case MENU_OPTIONS::OPTION_ONE:
			{
				OptionOneFromMenu(currGameIndex);
				break;
			}
			case MENU_OPTIONS::OPTION_TWO:
			{
				OptionTwoFromMenu(currGameIndex);
				break;
			}
			case MENU_OPTIONS::OPTION_THREE:
			{
				OptionThreeFromMenu(currGameIndex);
				break;
			}
			case MENU_OPTIONS::OPTION_FOUR:
			{
				OptionFourFromMenu(currGameIndex);
				break;
			}
			case MENU_OPTIONS::OPTION_FIVE:
			{
				OptionFiveFromMenu(m_GameList.at(currGameIndex - 1));
				break;
			}
			case MENU_OPTIONS::OPTION_SIX:
			{
				OptionSixFromMenu(m_GameList.at(currGameIndex - 1));
				break;
			}
			case MENU_OPTIONS::OPTION_SEVEN:
			{
				OptionSevenFromMenu(m_GameList.at(currGameIndex - 1));
				break;
			}
			case MENU_OPTIONS::OPTION_EIGHT:
			{
				OptionEightFromMenu();
				break;
			}
			case MENU_OPTIONS::OPTION_NINE:
			{
				OptionNineFromMenu(currGameIndex);
				break;
			}
			case MENU_OPTIONS::OPTION_TEN:
			{
				OptionTenFromMenu(currGameIndex);
				break;
			}
			default:
				cout << "Please enter a valid choice!!!" << endl;
			}
		}
		catch (bad_alloc& ba)
		{
			cout << ba.what() << endl << "Exiting the program" << endl;

			for (int i = 0; i < m_GameList.size(); ++i)
				delete m_GameList[i];

			exit(1);
		}
		catch (exception& ex)
		{
			cout << "Please select another option from the menu." << endl;
		}
		catch (...)
		{
			cout << "Unexpected error occurred.\nExiting the program safely" << endl;

			for (int i = 0; i < m_GameList.size(); ++i)
				delete m_GameList[i];

			exit(1);
		}
	}
}

int Arcade::PrintGameMenu()
{//prints the menu
	int choose;

	cout << "*********************************************" << endl;
	cout << "*Please choose one of the following options:*" << endl;
	cout << "*1)  Add a new game	                    *" << endl;      
	cout << "*2)  Move to the next game                  *" << endl;
	cout << "*3)  Delete current game                    *" << endl;
	cout << "*4)  Show game details	                    *" << endl;
	cout << "*5)  Show possible Moves                    *" << endl;
	cout << "*6)  Show threats	                    *" << endl;
	cout << "*7)  Make a move                            *" << endl;
	cout << "*8)  Exit menu	                            *" << endl;
	cout << "*9)  Save game to file	                    *" << endl;
	cout << "*10) Load game from file	            *" << endl;
	cout << "*********************************************" << endl << endl;

	do
	{
		cout << "Your choice: ";
		cin >> choose;

		if ((MENU_OPTIONS)choose <MENU_OPTIONS::OPTION_ONE || (MENU_OPTIONS)choose > MENU_OPTIONS::OPTION_TEN)
		{
			cout << "Invalid choice. Please choose an option between 1-" << (int)MENU_OPTIONS::OPTION_TEN << "." << endl;
		}
	} while ((MENU_OPTIONS)choose <MENU_OPTIONS::OPTION_ONE || (MENU_OPTIONS)choose > MENU_OPTIONS::OPTION_TEN);

	return choose;
}

void Arcade::OptionOneFromMenu(int& currGameIndex)
{//Creating a new game
	int selection(0);

	try
	{
		cout << "Please select the game you'd like to start:" << endl;
		for (int i = 0; i < m_GamesName.size(); ++i)
		{
			cout << i + 1 << ") " << m_GamesName[i] << endl;
		}
		cout << "Your choice: ";
		cin >> selection;
	
		m_GameList.push_back(CreateNewGame(selection));
		currGameIndex = m_GameList.size();
		cout << "New " << m_GameList.back()->GetGameName() << " game created!\n\n";

		cout << "You're currently playing game number " << currGameIndex << " out of " << m_GameList.size() << ".\n";
		cout << *m_GameList.back()->GetBoard();
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionTwoFromMenu(int& currGameIndex)
{//Moving to the next game (if there's any)
	try
	{
		if (m_GameList.empty())
			throw runtime_error("ERROR!! There's no game in progress.");
		else if (m_GameList.size() == 1)
			throw runtime_error("There's only 1 game available!");
		else if (currGameIndex == m_GameList.size())
			currGameIndex = 1;
		else
			++currGameIndex;
		
		cout << "You're currently playing " << m_GameList.at(currGameIndex - 1)->GetGameName() <<
			", number " << currGameIndex << " out of " << m_GameList.size() << ".\n";

		cout << *m_GameList.at(currGameIndex - 1)->GetBoard();
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionThreeFromMenu(int& currGameIndex)
{//Deleting the current game from the list
	try
	{
		if (m_GameList.empty())
			throw runtime_error("ERROR!! There's no game in progress.");

		m_GameList.erase(m_GameList.begin() + currGameIndex - 1);
		cout << "\nGame deleted!\n";

		if (m_GameList.size() == 0)
		{
			cout << "There are no games left.\n";
			return;
		}
		else if(currGameIndex > m_GameList.size())
		{ 
			currGameIndex = 1;
		}
		
		cout << "You're currently playing " << m_GameList.at(currGameIndex-1)->GetGameName()  <<
			", number " << currGameIndex << " out of " << m_GameList.size() << ".\n";
		cout << *m_GameList.at(currGameIndex - 1)->GetBoard();

	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionFourFromMenu(int& currGameIndex)
{//Showing the details of the current game
	try
	{
		if (m_GameList.empty())
			throw runtime_error("ERROR!! There's no game in progress.");

		cout << *m_GameList.at(currGameIndex - 1)->GetBoard();
		if (m_GameList.at(currGameIndex - 1)->GetGameOverStatus())
		{//The game is already over
			cout << "Game status: Over.\nThe winner is ";

			if (m_GameList.at(currGameIndex - 1)->GetWinner() == PLAYER_SYMBOL::O_PLAYER)
				cout << "PlayerO!!" << endl;
			else
				cout << "PlayerX!!" << endl;
		}
		else
		{//The game still running
			cout << "Game status: In progress.\nPlayer's turn: ";
			if (m_GameList.at(currGameIndex - 1)->GetTurn() == PLAYER_SYMBOL::O_PLAYER)
				cout << "PlayerO" << endl;
			else
				cout << "PlayerX" << endl;
		}
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionFiveFromMenu(Game* currGame)
{//Showing the possible moves of a selected stone
	try
	{
		if (nullptr == currGame)
			throw runtime_error("ERROR!! There's no game in progress.");
		else if (currGame->GetGameOverStatus())
			throw runtime_error("The game is already over!");

		int numOfPossibleMoves;
		Position userPos{ 0,0 }, systemPos{ 0,0 };

		cout << *currGame->GetBoard();
		cout << "Please enter the row and the column : ";
		cin.ignore();
		cin >> userPos;

		systemPos.row = userPos.row - 1;
		systemPos.col = userPos.col - 1;
	
		currGame->CheckPossibleMovesForPosition(systemPos, numOfPossibleMoves);
		auto& possibleMovesArr = currGame->GetBoard()->GetCell(systemPos)->GetStoneInCell()->GetPossibleMoves();

		cout << "The possible moves for position " << userPos << " are:" << endl;
		for (int i = 0; i < numOfPossibleMoves; ++i)
		{
			cout << "(" << possibleMovesArr[i].row + 1 << "," << possibleMovesArr[i].col + 1 << ") ";
		}
		cout << endl;
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionSixFromMenu(Game* currGame)
{//Showing all threats on selected pawn
	try
	{
		if (nullptr == currGame)
			throw runtime_error("ERROR!! There's no game in progress.");
		else if (currGame->GetGameOverStatus())
			throw runtime_error("The game is already over!");

		Position userPos{ 0,0 }, systemPos{ 0,0 };

		cout << *currGame->GetBoard();
		cout << "Please enter the row and the column : ";
		cin.ignore();
		cin >> userPos;

		systemPos.row = userPos.row - 1;
		systemPos.col = userPos.col - 1;

		currGame->GetBoard()->ValidationCheckForThreatsRequest(systemPos);

		auto& PossibleThreatsArr = currGame->GetBoard()->GetCell(systemPos)->GetThreatsArr();
		int numOfPossibleThreats = PossibleThreatsArr.size();

		if (numOfPossibleThreats == 0)
			throw runtime_error("There are no threats on selected position.");

		cout << "The threats on " << userPos << " are:" << endl;
		for (int i = 0; i < numOfPossibleThreats; ++i)
		{
			cout << "(" << PossibleThreatsArr[i].row + 1 << "," << PossibleThreatsArr[i].col + 1 << ") ";
		}
		cout << endl;
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionSevenFromMenu(Game* currGame)
{//Making a move
	try
	{
		if (nullptr == currGame)
			throw runtime_error("ERROR!! There's no game in progress.");
		else if (currGame->GetGameOverStatus())
			throw runtime_error("The game is already over!!!");

		PLAYER_SYMBOL playerPlaying = currGame->GetTurn();
		PLAYER_SYMBOL playerSymbol;
		int numOfPositions = currGame->GetPositionsForMove();
	
		cout << *currGame->GetBoard();

		playerSymbol = playerPlaying == PLAYER_SYMBOL::O_PLAYER ? playerSymbol = PLAYER_SYMBOL::O_PLAYER : playerSymbol = PLAYER_SYMBOL::X_PLAYER;
		cout << "It's player" << (char)playerSymbol << " Turn." << endl;

		Position* posArr = new Position[numOfPositions];
		if (posArr == nullptr)
			throw bad_alloc();

		string message;

		currGame->DemandsForValidMove(message);
		cout << message << endl;

		for (int i = 0; i < numOfPositions; ++i)
		{
			cin >> posArr[i];
		}
		ConvertUserPositionsToSystemPosition(posArr, numOfPositions);

		static_cast<AmazonGame*>(currGame)->MoveValidation(posArr);

		currGame->MakeAMove(posArr);

		cout << *currGame->GetBoard();
		currGame->EndOfTurn();

		if (currGame->CheckIfGameOver())
		{//GAME OVER
			cout << "The game's over!!" << endl << "The winner is ";
			if (currGame->GetWinner() == PLAYER_SYMBOL::O_PLAYER)
				cout << "PlayerO!!" << endl;
			else
				cout << "PlayerX!!" << endl;
		}
	}
	catch (bad_alloc& ba)
	{
		throw;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionEightFromMenu()
{//Exiting the program
	cout << "Exiting the arcade. Have a good day!" << endl;
}

Game* Arcade::CreateNewGame(int gameSelection)
{
	try
	{
		Game* newGame(nullptr);

		switch (gameSelection)
		{
			case 1:
			{
				newGame = new CheckersGame();
				break;
			}
			case 2:
			{
				newGame = new AmazonGame();
				break;
			}
			case 3:
			{
				newGame = new ChessGame();
				break;
			}
			default:
				throw invalid_argument("Invalid choice.");
		}

		return newGame;
	}
	catch (exception& ex)
	{
		throw;
	}
}

void Arcade::ConvertUserPositionsToSystemPosition(Position*& posArr, const int size)
{//converts the position for human convenient instead of subtract 1.
	for (int i = 0; i < size; ++i)
	{
		--posArr[i].row;
		--posArr[i].col;
	}
}

void Arcade::OptionNineFromMenu(int& currGameIndex)
{
	try
	{
		if (m_GameList.empty())
			throw runtime_error("ERROR!! There's no game in progress.");

		string fileName;

		cout << "Please enter the name of the file: ";
		cin >> fileName;

		ofstream f(fileName, ios::binary | ios::out);
		if (!f.is_open())
			throw runtime_error("Couldn't open file.");

		m_GameList[currGameIndex - 1]->SaveGameToFile(f);

		cout << "Game saved successfully!" << endl;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}
}

void Arcade::OptionTenFromMenu(int& currGameIndex)
{
	try
	{
	ifstream f;
	string fileName;
	int gameCode;

	cout << "Please enter the name of the file: ";
	cin >> fileName;

	f.open(fileName, ios::binary | ios::in);
	if (!f.is_open())
		throw runtime_error("Couldn't open file.");

	f.read(rcastc(&gameCode), sizeof(int));

	switch (static_cast<GAME_CODE>(gameCode))
	{
		case GAME_CODE::CHECKERS:
		{
			m_GameList.push_back(new CheckersGame(f));
			break;
		}
		case GAME_CODE::AMAZONS:
		{
			m_GameList.push_back(new AmazonGame(f));
			break;
		}
		case GAME_CODE::CHESS:
		{
			m_GameList.push_back(new ChessGame(f));
			break;
		}
		default:
		{
			throw runtime_error("Invalid game code from file.");
		}
	}
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		throw;
	}

	currGameIndex = m_GameList.size();

	cout << *m_GameList.back()->GetBoard();
	cout << "Game loaded successfully!" << endl;
	cout << "You're currently playing " << m_GameList.at(currGameIndex - 1)->GetGameName() <<
		", number " << currGameIndex << " out of " << m_GameList.size() << ".\n";
}