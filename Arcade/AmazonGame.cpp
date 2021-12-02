#include "AmazonGame.h"

//---------------------------------------Constructors---------------------------------------//
AmazonGame::AmazonGame()
	: Game()
{
	try
	{
		m_PlayerO = new AmazonPlayer(PLAYER_SYMBOL::O_PLAYER, true);
		m_PlayerX = new AmazonPlayer(PLAYER_SYMBOL::X_PLAYER, false);
		m_Board = new AmazonBoard(static_cast<int>(AMAZONS_NUMBERS::ROWS), static_cast<int>(AMAZONS_NUMBERS::COLS));

		m_GameName = "Amazons";
		m_PositionsForMove = 3;

		StartNewGame();
		SetThreats();
	}
	catch (bad_alloc& ba)
	{
		delete m_PlayerO;
		delete m_PlayerX;
		delete m_Board;
		throw;
	}
}

AmazonGame::AmazonGame(const AmazonGame& other)
	: Game(other)
{
	try
	{
	m_PlayerO = new AmazonPlayer(PLAYER_SYMBOL::O_PLAYER, other.m_PlayerO->GetTurn());
	m_PlayerX = new AmazonPlayer(PLAYER_SYMBOL::X_PLAYER, other.m_PlayerX->GetTurn());
	m_Board = new AmazonBoard(other.m_Board->GetRows(), other.m_Board->GetCols());
	}
	catch (bad_alloc& ba)
	{
		delete m_PlayerO;
		delete m_PlayerX;
		delete m_Board;
		throw;
	}
}

AmazonGame::AmazonGame(AmazonGame&& other)
	: Game(other) {}

AmazonGame::AmazonGame(ifstream& f)
	: Game(f)
{
	try
	{
		int rows, cols;
		char playerSymbol;

		f.read(rcastc(&rows), sizeof(int));
		f.read(rcastc(&cols), sizeof(int));

		m_Board = new AmazonBoard(rows, cols);

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new AmazonPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new AmazonPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		f.read(rcastc(&playerSymbol), sizeof(char));
		if (playerSymbol == static_cast<char>(PLAYER_SYMBOL::O_PLAYER))
			m_PlayerO = new AmazonPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));
		else
			m_PlayerX = new AmazonPlayer(f, static_cast<PLAYER_SYMBOL>(playerSymbol));

		static_cast<AmazonBoard*>(m_Board)->MarkPositionsFromFile(f);

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
AmazonGame::~AmazonGame() {}

//---------------------------------------Setters---------------------------------------//
void AmazonGame::SetStonePossibleMoves(Stone* stone)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i != 0 || j != 0)
				SetStonePossibleMovesRec(stone, i, j);
		}
	}
}

/* creating a dummy pawn in order to generate the possible position for the
   dummy pawn to move (later it will be the possible moves to mark)*/
void AmazonGame::SetThreats()
{
	AmazonBoard* board = static_cast<AmazonBoard*>(m_Board);
	Position currPos;
	AmazonStone* dummyStone;
	int rows = board->GetRows(), cols = board->GetCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (!board->GetBoard()[i][j]->GetHaveStone())
			{
				currPos = { i, j };
				dummyStone = new AmazonStone{ currPos, static_cast<char>(AMAZON_SYMBOL::MARKED_SYMBOL),
					PLAYER_SYMBOL::O_PLAYER, 0 };
				
				SetStonePossibleMoves(dummyStone);

				board->GetCell(currPos)->SetThreats(dummyStone->GetPossibleMoves());
				delete dummyStone;
			}
		}
	}
}

void AmazonGame::SetStonePossibleMovesRec(Stone* stone, int rowDiff, int colDiff)
{
	int currPawnRow = stone->GetPosition().row, currPawnCol = stone->GetPosition().col;
	const Position pos = { stone->GetPosition().row + rowDiff, stone->GetPosition().col + colDiff };

	if (!m_Board->CheckPositionInBoard(pos))
	{//Invalid spot
		return;
	}
	else if (static_cast<AmazonBoard*>(m_Board)->GetCell(pos)->GetMarkedStatus())
	{//Marked position
		return;
	}
	else if (static_cast<AmazonBoard*>(m_Board)->GetCell(pos)->GetHaveStone())
	{//Not a free position
		return;
	}
	else if (!m_Board->GetCell(pos)->GetHaveStone())
	{//Free spot
		stone->AddPossibleMove(pos);

		UpdateDiffs(rowDiff, colDiff);

		SetStonePossibleMovesRec(stone, rowDiff, colDiff);
	}
}

void AmazonGame::SetDiffs(const Position& source, const Position& destination, int& rowDiff, int& colDiff)
{//Helper for setting diffs of row, cols and diagonal - this method determines if the pawn moves rowline,coline or diagonal.
	if (source.row > destination.row)
		rowDiff = -1;
	else if (source.row < destination.row)
		rowDiff = 1;
	else
		rowDiff = 0;

	if (source.col > destination.col)
		colDiff = -1;
	else if (source.col < destination.col)
		colDiff = 1;
	else
		colDiff = 0;
}

//---------------------------------------Getters---------------------------------------//

//---------------------------------------Methods---------------------------------------//
bool AmazonGame::CheckStraightPath(const Position & currPos, const Position & nextPos)
{
	//this method checks if the pawn moves in a straigt path (row,col or diagonal).
	int currRow = currPos.row, currCol = currPos.col, nextRow = nextPos.row, nextCol = nextPos.col;

	if (currRow == nextRow || currCol == nextCol)
		return true;
	else if (abs(currRow - nextRow) == abs(currCol - nextCol))
		return true;
	return false;
}

bool AmazonGame::CheckPath(AmazonBoard*& board, Position& source, const Position& destination, int& rowDiff, int& colDiff)
{
	//rec method to determine if the path of the pawn is valid (row,col or diagonal).
	source = { source.row + rowDiff, source.col + colDiff };

	if (destination == source) //Reached destination
		return true;

	AmazonCell* cellChecked = board->GetCell(source);

	if (cellChecked->GetHaveStone())
		return false;
	else if (cellChecked->GetMarkedStatus())
		return false;

	return CheckPath(board, source, destination, rowDiff, colDiff);
}

void AmazonGame::MakeAMove(const Position* posArr)
{
	Game::MakeAMove(posArr);

	Position markPos = posArr[2];
	(static_cast<AmazonBoard*>(m_Board))->MarkPosition(posArr[2]);
}

bool AmazonGame::CheckIfGameOver()
{
	AmazonPlayer* currPlayer = static_cast<AmazonPlayer*>(m_PlayerO);

	//Check if any of the players not having free amazons
	if (currPlayer->GetNumOfBlockedStones() == currPlayer->GetNumOfStartingStones())
	{
		m_Winner = PLAYER_SYMBOL::X_PLAYER;
		GetPlayer(m_Winner)->PlayerWon();
		m_GameOver = true;
		return true;
	}

	currPlayer = static_cast<AmazonPlayer*>(m_PlayerX);
	if (currPlayer->GetNumOfBlockedStones() == currPlayer->GetNumOfStartingStones())
	{
		m_Winner = PLAYER_SYMBOL::O_PLAYER;
		GetPlayer(m_Winner)->PlayerWon();
		m_GameOver = true;
		return true;
	}
	return false;
}

void AmazonGame::EndOfTurn()
{
	Game::EndOfTurn();

	array<AmazonPlayer*, 2> playersArr = { static_cast<AmazonPlayer*>(m_PlayerO), static_cast<AmazonPlayer*>(m_PlayerX) };
	int numOfStones = 0;

	for (auto& currPlayer : playersArr)
	{
		auto& currStonesArr = currPlayer->GetStonesArr();
		int numOfStones = currPlayer->GetNumOfStones();
		AmazonStone* currAmazonStone;

		for (int i = 0; i < numOfStones; ++i)
		{
			currAmazonStone = static_cast<AmazonStone*>(currStonesArr[i]);
			if (currAmazonStone->GetNumOfPossibleMoves() == 0 && !currAmazonStone->GetBlockedStatus())
			{
				currAmazonStone->AmazonBlocked();
				currPlayer->StoneGotBlocked();
			}
		}
	}
}

void AmazonGame::SaveGameToFile(ofstream& f)
{
	int AmazonCode = static_cast<int>(GAME_CODE::AMAZONS);
	auto& markedPositions = static_cast<AmazonBoard*>(m_Board)->GetMarkedPositions();
	int numOfMarked = markedPositions.size();

	f.write(rcastcc(&AmazonCode), sizeof(int));

	Game::SaveGameToFile(f);

	f.write(rcastcc(&numOfMarked), sizeof(int));
	for (int i = 0; i < numOfMarked; ++i)
		f.write(rcastcc(&markedPositions[i]), sizeof(Position));
}

void AmazonGame::SaveStoneToFile(ofstream& f, Stone* stone)
{
	char isBlocked = static_cast<AmazonStone*>(stone)->GetBlockedStatus();

	Game::SaveStoneToFile(f, stone);

	f.write(rcastcc(&isBlocked), sizeof(char));
}

void AmazonGame::DemandsForValidMove(string& demandsMessage)
{
	demandsMessage = "Please enter 3 positions (row, column): choose an amazon, her new position, and a marking spot.";
}

void AmazonGame::MoveValidation(Position* posArr)
{
	Position amazonCurrPos = posArr[0], amazonNextPos = posArr[1], markPos = posArr[2];
	AmazonBoard* board = static_cast<AmazonBoard*>(m_Board);

	if (!board->CheckPositionInBoard(amazonCurrPos))
	{//The current position is outside board lines
		throw invalid_argument("Invalid pawn selection. Please choose an amazon which is in the board lines");
	}
	else if (!board->CheckPositionInBoard(amazonNextPos))
	{//The next move is outside board lines
		throw invalid_argument("Invalid move. Make sure your move in is the board lines.");
	}
	else if (!board->CheckPositionInBoard(markPos))
	{//The next move is outside board lines
		throw invalid_argument("Invalid move.Make sure your marking spot in is the board lines.");
	}
	else if (board->GetCell(amazonCurrPos)->GetHaveStone() == false)
	{//The selected position has no pawn
		throw invalid_argument("Invalid amazon selection. Please choose one of your amazons.");
	}
	else if (board->GetCell(amazonNextPos)->GetMarkedStatus() == true)
	{//The selected position is marked
		throw invalid_argument("Invalid move. Please choose a none-marked position.");
	}
	else if (board->GetCell(markPos)->GetHaveStone() == true && markPos != amazonCurrPos)
	{//The marking position as an amazon on it
		throw invalid_argument("Invalid marking selection. Please mark a free position.");
	}
	else if (board->GetCell(markPos)->GetMarkedStatus() == true)
	{//The selected position is marked
		throw invalid_argument("Invalid marking selection. Please mark a none-marked position.");
	}
	else if (amazonNextPos == markPos)
	{//The selected position is marked
		throw invalid_argument("Invalid move. You cannot mark a position as your amazon's new position.");
	}
	else if (!CheckStraightPath(amazonCurrPos, amazonNextPos))
	{//Not a diagonal move
		throw invalid_argument("Invalid move. Amazons can only move in a straight path.");
	}
	else if (!CheckStraightPath(amazonNextPos, markPos))
	{//Not a diagonal move
		throw invalid_argument("Invalid move. Amazons can only mark a new position in a straight path.");
	}

	PLAYER_SYMBOL SelectStoneSymbol = static_cast<PLAYER_SYMBOL>(board->GetCell(amazonCurrPos)->GetStoneInCell()->GetSymbol());

	if (SelectStoneSymbol != m_PlayerPlaying)
		throw invalid_argument("Please choose your own amazon!!");

	Position posChecked = amazonCurrPos;
	int rowDiff, colDiff;
	SetDiffs(posChecked, amazonNextPos, rowDiff, colDiff);

	if (!CheckPath(board, posChecked, amazonNextPos, rowDiff, colDiff))
	{//The path of the amazon is not free
		throw invalid_argument("Invalid path. Please choose a free moving path for the amazon.");
	}

	posChecked = amazonNextPos;
	SetDiffs(posChecked, markPos, rowDiff, colDiff);
	board->UpdateBoard(amazonCurrPos, amazonNextPos);

	if (!CheckPath(board, posChecked, markPos, rowDiff, colDiff))
	{//The path of the marking is not free
		throw invalid_argument("Invalid path. Please choose a free path for marking.");
		board->UpdateBoard(amazonNextPos, amazonCurrPos); //Returning to the original state
	}

	Stone* movingPawn = board->GetCell(amazonNextPos)->GetStoneInCell();
	int PossibleMovesSize = movingPawn->GetNumOfPossibleMoves();
	auto& movesArr = movingPawn->GetPossibleMoves();

	for (int i = 0; i < PossibleMovesSize; ++i)
	{
		if (amazonNextPos == movesArr[i])
		{//The next move requested to be done is a possible move
			board->UpdateBoard(amazonNextPos, amazonCurrPos);
			return;
		}
	}

	throw invalid_argument("No possible move for selected amazon.");
}

void AmazonGame::UpdateDiffs(int& rowDiff, int& colDiff)
{
	if (rowDiff > 0)
		++rowDiff;
	else if (rowDiff < 0)
		--rowDiff;

	if (colDiff > 0)
		++colDiff;
	else if (colDiff < 0)
		--colDiff;
}