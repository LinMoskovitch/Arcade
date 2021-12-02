#include "CheckersGame.h"

//---------------------------------------Constructors---------------------------------------//
CheckersGame::CheckersGame() 
	: Game()
{
	try
	{
		m_PlayerO = new CheckersPlayer(PLAYER_SYMBOL::O_PLAYER, true);
		m_PlayerX = new CheckersPlayer(PLAYER_SYMBOL::X_PLAYER, false);
		m_Board = new CheckersBoard(static_cast<int>(CHECKERS_NUMBERS::ROWS), static_cast<int>(CHECKERS_NUMBERS::COLS));

		m_GameName = "Checkers";
		m_PositionsForMove = 2;

		StartNewGame();
	}
	catch (bad_alloc& ba)
	{
		delete m_PlayerO;
		delete m_PlayerX;
		delete m_Board;
		throw;
	}
}

CheckersGame::CheckersGame(const CheckersGame& other)
	: Game(other) 
{
	try
	{
	m_PlayerO = new CheckersPlayer(PLAYER_SYMBOL::O_PLAYER, other.m_PlayerO->GetTurn());
	m_PlayerX = new CheckersPlayer(PLAYER_SYMBOL::X_PLAYER, other.m_PlayerX->GetTurn());
	m_Board = new CheckersBoard(other.m_Board->GetRows(), other.m_Board->GetCols());
	}
	catch (bad_alloc& ba)
	{
		delete m_PlayerO;
		delete m_PlayerX;
		delete m_Board;
		throw;
	}
}

CheckersGame::CheckersGame(CheckersGame&& other)
	: Game(other) {}

CheckersGame::CheckersGame(ifstream& f)
	: Game(f)
{
	try
	{
		int rows, cols;
		char playerSymbol;

		f.read(rcastc(&rows), sizeof(int));
		f.read(rcastc(&cols), sizeof(int));

		m_Board = new CheckersBoard(rows, cols);

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new CheckersPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new CheckersPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new CheckersPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new CheckersPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		if (f.fail() || f.bad())
			throw runtime_error("Bad reading from file.");

		if (m_GameOver)
			GetPlayer(m_Winner)->PlayerWon();
		else
			GetPlayer(m_PlayerPlaying)->SetTurn(true);

		StartNewGame();
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;

		delete m_Board;
		delete m_PlayerO;
		delete m_PlayerX;

		throw;
	}
	catch (...)
	{
		cout << "Unknown error occured while reading the game." << endl;

		delete m_Board;
		delete m_PlayerO;
		delete m_PlayerX;

		throw;
	}
}

//---------------------------------------Destructor---------------------------------------//
CheckersGame::~CheckersGame() {}


//---------------------------------------Setters---------------------------------------//
void CheckersGame::SetStonePossibleMoves(Stone* stone)
{
	bool kingStatus = static_cast<CheckersStone*>(stone)->GetKingStatus();
	CHECKERS_SYMBOL symbol = static_cast<CHECKERS_SYMBOL>(stone->GetSymbol());
	int rowDiff, colDiff;

	if (symbol == CHECKERS_SYMBOL::O_PAWN_SYMBOL || kingStatus) //O_PLAYER
	{
		rowDiff = colDiff = -1;
		SetStonePossibleMovesRec(stone, rowDiff, colDiff);
		colDiff = 1;
		SetStonePossibleMovesRec(stone, rowDiff, colDiff);
	}
	if (symbol == CHECKERS_SYMBOL::X_PAWN_SYMBOL || kingStatus) //X_PLAYER
	{
		rowDiff = colDiff = 1;
		SetStonePossibleMovesRec(stone, rowDiff, colDiff);
		colDiff = -1;
		SetStonePossibleMovesRec(stone, rowDiff, colDiff);
	}
}

void CheckersGame::SetStonePossibleMovesRec(Stone* stone, int rowDiff, int colDiff)
{
	Position currStonePos = { stone->GetPosition().row + rowDiff, stone->GetPosition().col + colDiff };

	if (!m_Board->CheckPositionInBoard(currStonePos))
	{//Invalid spot
		return;
	}
	else if (!m_Board->GetCell(currStonePos)->GetHaveStone())
	{//Free spot
		stone->AddPossibleMove(currStonePos);

		if (static_cast<CheckersStone*>(stone)->GetKingStatus())
		{
			rowDiff > 0 ? ++rowDiff : --rowDiff;
			colDiff > 0 ? ++colDiff : --colDiff;
			SetStonePossibleMovesRec(stone, rowDiff, colDiff);
		}
	}
	else
	{//Found another stone on next position
		if (stone->GetSymbol() != m_Board->GetCell(currStonePos)->GetStoneInCell()->GetSymbol())
		{//Eating potential (different symbols of stones)
			Position secondStonePos = currStonePos;
			rowDiff > 0 ? ++currStonePos.row : --currStonePos.row;
			colDiff > 0 ? ++currStonePos.col : --currStonePos.col;
			if (EatingPotential(currStonePos))
			{
				stone->AddPossibleMove(currStonePos);

				static_cast<CheckersCell*>(m_Board->GetCell(secondStonePos))->AddNewThreat(stone->GetPosition());
			}
		}
	}
}
//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
bool CheckersGame::CheckIfGameOver()
{
	int playerOStonesLeft = m_PlayerO->GetNumOfStones();
	int playerXStonesLeft = m_PlayerX->GetNumOfStones();

	//Check if any of the players have 0 stones left on the board
	if (playerOStonesLeft == 0)
	{//PlayerO has 0 stones left = lost the game
		SetWinner(PLAYER_SYMBOL::X_PLAYER);
		m_PlayerX->PlayerWon();
		ChangeTurn();
		m_GameOver = true;
		return true;
	}
	else if (playerXStonesLeft == 0)
	{//PlayerX has 0 stones left = lost the game
		SetWinner(PLAYER_SYMBOL::O_PLAYER);
		m_PlayerO->PlayerWon();
		ChangeTurn();
		m_GameOver = true;
		return true;
	}

	//Check if the player currently playing has no possible moves
	auto& stonesArr = GetPlayer(m_PlayerPlaying)->GetStonesArr();
	int numOfStones = stonesArr.size();

	for (int i = 0; i < numOfStones; ++i)
	{
		if (stonesArr[i]->GetNumOfPossibleMoves() != 0)
		{//The current player has a possible move (not all blocked)
			return false;
		}
	}

	//One of the players won (the one who just finished his turn)
	ChangeTurn();
	SetWinner(m_PlayerPlaying);
	GetPlayer(m_PlayerPlaying)->PlayerWon();

	m_GameOver = true;
	return true;
}

void CheckersGame::SaveGameToFile(ofstream& f)
{
	int CheckersCode = static_cast<int>(GAME_CODE::CHECKERS);

	f.write(rcastcc(&CheckersCode), sizeof(int));

	Game::SaveGameToFile(f);
}

void CheckersGame::SaveStoneToFile(ofstream& f, Stone* stone)
{
	char isKing = static_cast<CheckersStone*>(stone)->GetKingStatus();

	Game::SaveStoneToFile(f, stone);

	f.write(rcastcc(&isKing), sizeof(char));
}

bool CheckersGame::EatingPotential(const Position& pos)
{
	if (!m_Board->CheckPositionInBoard(pos))
		return false;
	else if (m_Board->GetCell(pos)->GetHaveStone())
		return false;
	return true;
}

void CheckersGame::MoveValidation(Position* posArr)
{
	Position currPos = posArr[0], nextPos = posArr[1];

	if (!m_Board->CheckPositionInBoard(currPos))
	{//The current position is outside board lines
		throw invalid_argument("Invalid stone selection. Please choose a stone which is in the board lines");
	}
	else if (!m_Board->CheckPositionInBoard(nextPos))
	{//The next move is outside board lines
		throw invalid_argument("Invalid move. Make sure your move in is the board lines.");
	}
	else if (m_Board->GetCell(currPos)->GetHaveStone() == false)
	{//The selected position has no stone
		throw invalid_argument("Invalid stone selection. Please choose a position with a stone.");
	}
	else if (!CheckDiagonal(currPos, nextPos))
	{//Not a diagonal move
		throw invalid_argument("Invalid move. The stones can only move in diagonal path.");
	}

	CHECKERS_SYMBOL SelectedStoneSymbol = static_cast<CHECKERS_SYMBOL>(m_Board->GetCell(currPos)->GetStoneInCell()->GetSymbol());
	if (m_PlayerPlaying == PLAYER_SYMBOL::X_PLAYER)
	{//The user choose a stone of PlayerX
		if (CHECKERS_SYMBOL::O_PAWN_SYMBOL == SelectedStoneSymbol || CHECKERS_SYMBOL::O_KING_SYMBOL == SelectedStoneSymbol)
		{//It's the turn of PlayerO
			throw invalid_argument("Please choose your own stone!!");
		}
	}
	else if (m_PlayerPlaying == PLAYER_SYMBOL::O_PLAYER)
	{//The user choose a stone of PlayerO
		if (CHECKERS_SYMBOL::X_PAWN_SYMBOL == SelectedStoneSymbol || CHECKERS_SYMBOL::X_KING_SYMBOL == SelectedStoneSymbol)
		{//It's the turn of PlayerX
			throw invalid_argument("Please choose your own stone!!");
		}
	}
	if (!static_cast<CheckersStone*>(m_Board->GetCell(currPos)->GetStoneInCell())->GetKingStatus())
	{//The selected position has a stone, which is not a king
		if (m_PlayerPlaying == PLAYER_SYMBOL::O_PLAYER && currPos.row < nextPos.row)
		{//PlayerO stones can only move down
			throw invalid_argument("Invalid move. The stones of PlayerO can only move upwards the board");
		}
		else if (m_PlayerPlaying == PLAYER_SYMBOL::X_PLAYER && currPos.row > nextPos.row)
		{//PlayerX stones can only move up
			throw invalid_argument("Invalid move. The stones of PlayerX can only move downwards the board");
		}
	}

	CheckersStone* stone = static_cast<CheckersStone*>(m_Board->GetCell(currPos)->GetStoneInCell());
	int PossibleMovesSize = stone->GetNumOfPossibleMoves();
	auto& movesArr = stone->GetPossibleMoves();

	for (int i = 0; i < PossibleMovesSize; ++i)
	{
		if (nextPos == movesArr[i])
		{//The next move requested to be done is a possible move
			return;
		}
	}

	throw invalid_argument("No possible move for selected stone.");
}

void CheckersGame::MakeAMove(const Position* posArr)
{
	Position currPos = posArr[0], nextPos = posArr[1];

	if (abs(currPos.row - nextPos.row) >= 2)
	{//The current stone moved more than 2 rows on its turn, another stone might got eaten

		Position potentialStone;
		potentialStone.row = nextPos.row - currPos.row < 0 ? nextPos.row + 1 : nextPos.row - 1;
		potentialStone.col = nextPos.col - currPos.col < 0 ? nextPos.col + 1 : nextPos.col - 1;

		if (m_Board->GetCell(potentialStone)->GetHaveStone()== true)
		{//An enemy stone got eaten by the current stone
			if (m_PlayerPlaying == PLAYER_SYMBOL::X_PLAYER)
			{//The eaten stone belongs to O_PLAYER
				static_cast<CheckersPlayer*>(m_PlayerO)->DeleteStoneFromArr(m_Board->GetCell(potentialStone)->GetStoneInCell());
			}
			else
			{//The eaten stone belongs to X_PLAYER
				static_cast<CheckersPlayer*>(m_PlayerX)->DeleteStoneFromArr(m_Board->GetCell(potentialStone)->GetStoneInCell());
			}
			m_Board->GetCell(potentialStone)->RemoveStoneFromCell();
		}
	}

	Game::MakeAMove(posArr);

	if (static_cast<CheckersStone*>(m_Board->GetCell(nextPos)->GetStoneInCell())->GetKingStatus() == false)
	{//The stone we just moved is not a king
		if (nextPos.row == 0 || nextPos.row == m_Board->GetRows() - 1) //The stone becoming a king
			static_cast<CheckersStone*>(m_Board->GetCell(nextPos)->GetStoneInCell())->MakeKing();
	}
}

void CheckersGame::DemandsForValidMove(string& demandsMessage)
{
	demandsMessage = "Please enter 2 position (row, column): The stone you'd like to make a move with, and its new position on the board.";
}