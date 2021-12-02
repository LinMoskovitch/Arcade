#include "ChessGame.h"

//---------------------------------------Constructors---------------------------------------//
ChessGame::ChessGame()
	: Game()
{
	try
	{
		m_PlayerO = new ChessPlayer(PLAYER_SYMBOL::O_PLAYER, true);
		m_PlayerX = new ChessPlayer(PLAYER_SYMBOL::X_PLAYER, false);
		m_Board = new ChessBoard(static_cast<int>(CHESS_NUMBERS::ROWS), static_cast<int>(CHESS_NUMBERS::COLS));

		m_GameName = "Chess";
		m_PositionsForMove = 2;

		Position kingPosPlayerO, kingPosPlayerX;
		kingPosPlayerO = m_PlayerO->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)]->GetPosition();
		kingPosPlayerX = m_PlayerX->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)]->GetPosition();
		static_cast<ChessBoard*>(m_Board)->SetKingPos(PLAYER_SYMBOL::O_PLAYER, kingPosPlayerO);
		static_cast<ChessBoard*>(m_Board)->SetKingPos(PLAYER_SYMBOL::X_PLAYER, kingPosPlayerX);

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

ChessGame::ChessGame(const ChessGame& other)
	: Game(other) 
{
	try
	{
		m_PlayerO = new ChessPlayer(PLAYER_SYMBOL::O_PLAYER, other.m_PlayerO->GetTurn());
		m_PlayerX = new ChessPlayer(PLAYER_SYMBOL::X_PLAYER, other.m_PlayerX->GetTurn());
		m_Board = new ChessBoard(other.m_Board->GetRows(), other.m_Board->GetCols());
	}
	catch (bad_alloc& ba)
	{
		delete m_PlayerO;
		delete m_PlayerX;
		delete m_Board;
		throw;
	}
}

ChessGame::ChessGame(ChessGame&& other)
	: Game(other) {}

ChessGame::ChessGame(ifstream& f)
	: Game(f)
{
	try
	{
		int rows, cols;
		char playerSymbol;
		Position kingPosPlayerO, kingPosPlayerX;

		f.read(rcastc(&rows), sizeof(int));
		f.read(rcastc(&cols), sizeof(int));

		m_Board = new ChessBoard(rows, cols);

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new ChessPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new ChessPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new ChessPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new ChessPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		kingPosPlayerO = m_PlayerO->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)]->GetPosition();
		kingPosPlayerX = m_PlayerX->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)]->GetPosition();
		static_cast<ChessBoard*>(m_Board)->SetKingPos(PLAYER_SYMBOL::O_PLAYER, kingPosPlayerO);
		static_cast<ChessBoard*>(m_Board)->SetKingPos(PLAYER_SYMBOL::X_PLAYER, kingPosPlayerX);

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
ChessGame::~ChessGame() {}

//---------------------------------------Setters---------------------------------------//
void ChessGame::SetStonePossibleMoves(Stone* stone)
{
	static_cast<ChessStone*>(stone)->SetPossibleMoves(static_cast<ChessBoard*>(m_Board));
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
void ChessGame::MoveValidation(Position* posArr)
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
	else if (m_PlayerPlaying != m_Board->GetCell(currPos)->GetStoneInCell()->GetPlayerProperty())
	{//The player choose rival's stone
		throw invalid_argument("Please choose your own stone!!");
	}

	ChessStone* stone = static_cast<ChessStone*>(m_Board->GetCell(currPos)->GetStoneInCell());
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

void ChessGame::MakeAMove(const Position* posArr)
{
	Position stoneCurrPos = posArr[0], stoneNewPos = posArr[1];

	//Check if another stone got captured by current stone
	if (m_Board->GetCell(stoneNewPos)->GetHaveStone())
	{//Deleting the rival stone
		ChessStone* stoneToDelete = static_cast<ChessStone*>(m_Board->GetCell(stoneNewPos)->GetStoneInCell());
		m_Board->GetCell(stoneNewPos)->RemoveStoneFromCell();
		PLAYER_SYMBOL rivalPlayer = m_PlayerPlaying == PLAYER_SYMBOL::O_PLAYER ? PLAYER_SYMBOL::X_PLAYER : PLAYER_SYMBOL::O_PLAYER;
		static_cast<ChessPlayer*>(GetPlayer(rivalPlayer))->DeleteStoneFromArr(stoneToDelete);
	}

	Stone* stone = dynamic_cast<ChessPawn*>(m_Board->GetCell(stoneCurrPos)->GetStoneInCell());
	//Check if the current stone is a pawn
	if (nullptr != stone)
	{
		MakeAMoveWithPawn(static_cast<ChessPawn*>(stone), stoneNewPos);
	}

	//Update current stone's position 
	Game::MakeAMove(posArr);
}

void ChessGame::MakeAMoveWithPawn(ChessPawn* pawn, const Position pawnNextPos)
{
	if ((pawnNextPos.row == 0 || pawnNextPos.row == m_Board->GetRows() - 1))
	{//The pawn reached the end of the board - promoted to queen 
		int pawnIndex = pawn->GetStoneIndexInArr();
		vector<Stone*>& stoneArr = pawn->GetPlayerProperty() == PLAYER_SYMBOL::O_PLAYER ?
			m_PlayerO->GetStonesArr() :m_PlayerX->GetStonesArr();
		CHESS_SYMBOL queenSymbol = pawn->GetPlayerProperty() == PLAYER_SYMBOL::O_PLAYER ?
			CHESS_SYMBOL::O_QUEEN : CHESS_SYMBOL::X_QUEEN;

		ChessQueen* newQueen = new ChessQueen(pawnNextPos, static_cast<char>(queenSymbol),
			pawnIndex, pawn->GetPlayerProperty());
		if (nullptr == newQueen)
			throw bad_alloc();

		stoneArr[pawnIndex] = newQueen;
		m_Board->GetCell(pawn->GetPosition())->SetStone(newQueen);
		delete pawn;
	}
	else if (pawn->GetFirstTurn())
		pawn->MadeFirstMove();
}

void ChessGame::DemandsForValidMove(string& demandsMessage)
{
	demandsMessage = "Please enter 2 positions (row, column): The stone you'd like to move, and the new position for the chosen stone.";
}

bool ChessGame::CheckIfGameOver()
{
	array<Player*, 2> playersArr = { m_PlayerO, m_PlayerX };

	for (auto& currPlayer : playersArr)
	{
		auto& stoneArr = currPlayer->GetStonesArr();
		ChessKing* king = static_cast<ChessKing*>(currPlayer->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)]);

		if (king->GetCheckedStatus() && king->GetPossibleMoves().size() == 0)
		{//There are no possible moves for the checked king - checkmate
			if (currPlayer == m_PlayerO)
				m_Winner = PLAYER_SYMBOL::X_PLAYER;
			else
				m_Winner = PLAYER_SYMBOL::O_PLAYER;

			GetPlayer(m_Winner)->PlayerWon();
			m_GameOver = true;
			return true;
		}
	}
	return false;
}

void ChessGame::EndOfTurn()
{
	static_cast<ChessKing*>(m_PlayerO->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)])->SetChecked(false);
	static_cast<ChessKing*>(m_PlayerX->GetStonesArr()[static_cast<int>(CHESS_NUMBERS::KING_INDEX)])->SetChecked(false);

	Game::EndOfTurn();
}

void ChessGame::SaveGameToFile(ofstream& f)
{
	int ChessCode = static_cast<int>(GAME_CODE::CHESS);

	f.write(rcastcc(&ChessCode), sizeof(int));

	Game::SaveGameToFile(f);
}

void ChessGame::SaveStoneToFile(ofstream& f, Stone* stone)
{
	Game::SaveStoneToFile(f, stone);

	if (typeid(ChessPawn) == typeid(*stone))
	{
		char firstMove = static_cast<ChessPawn*>(stone)->GetFirstTurn();
		f.write(rcastcc(&firstMove), sizeof(char));
	}
}