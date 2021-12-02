#include "Game.h"

//---------------------------------------Constructors---------------------------------------//
Game::Game() :m_PlayerPlaying(PLAYER_SYMBOL::O_PLAYER), m_PlayerX(nullptr), m_PlayerO(nullptr),
			  m_Winner(), m_GameOver(false) , m_Board(nullptr), m_PositionsForMove(0) {}

Game::Game(const Game& other)
	: m_PlayerPlaying(other.m_PlayerPlaying), m_PositionsForMove(other.m_PositionsForMove),
	  m_Winner(other.m_Winner), m_PlayerO(nullptr), m_PlayerX(nullptr), m_GameName(other.m_GameName),
	  m_GameOver(other.m_GameOver), m_Board(nullptr) {}

Game::Game(Game&& other)
	: m_Winner(other.m_Winner), m_PositionsForMove(other.m_PositionsForMove),
	  m_GameOver(other.m_GameOver), m_PlayerPlaying(other.m_PlayerPlaying),
	  m_PlayerO(nullptr), m_PlayerX(nullptr), m_Board(nullptr), m_GameName(other.m_GameName)
{
	if (this != &other)
	{
		m_PlayerO = move(other.m_PlayerO);
		m_PlayerX = move(other.m_PlayerX);
		m_Board = move(other.m_Board);

		other.m_PlayerO = other.m_PlayerX = nullptr;
		other.m_Board = nullptr;
	}
}


Game::Game(istream& f)
	: m_Board(nullptr), m_PlayerO(nullptr), m_PlayerX(nullptr)
{
	int nameLen;
	char winner, playerPlaying, gameOverStatus;

	f.read(rcastc(&nameLen), sizeof(int));
	m_GameName.resize(nameLen);
	f.read(rcastc(&m_GameName[0]), nameLen);
	f.read(rcastc(&m_PositionsForMove), sizeof(int));
	f.read(rcastc(&winner), sizeof(char));
	f.read(rcastc(&gameOverStatus), sizeof(char));
	f.read(rcastc(&playerPlaying), sizeof(char));

	m_Winner = static_cast<PLAYER_SYMBOL>(winner);
	m_GameOver = static_cast<bool>(gameOverStatus);
	m_PlayerPlaying = static_cast<PLAYER_SYMBOL>(playerPlaying);

	if (f.fail() || f.bad())
		throw runtime_error("Bad reading from file.");
}

//---------------------------------------Destructor---------------------------------------//
Game::~Game()
{
	delete m_PlayerO;
	delete m_PlayerX;
	delete m_Board;
}

//---------------------------------------Setters---------------------------------------//
void Game::SetWinner(PLAYER_SYMBOL winner)
{
	m_Winner = winner;
}

void Game::StartNewGame()
{
	array<Player*, 2> playersArr = { m_PlayerO, m_PlayerX };
	int numOfStones;

	m_Board->InitBoard(m_PlayerO->GetStonesArr(), m_PlayerX->GetStonesArr());
	for (auto& currPlayer : playersArr)
	{
		auto& stoneArr = currPlayer->GetStonesArr();
		numOfStones = currPlayer->GetStonesArr().size();

		for (int i = 0; i < numOfStones; ++i)
		{
			SetStonePossibleMoves(stoneArr[i]);
		}
	}
}

//---------------------------------------Getters---------------------------------------//
PLAYER_SYMBOL Game::GetWinner() const
{
	return m_Winner;
}

PLAYER_SYMBOL Game::GetTurn() const
{
	return m_PlayerPlaying;
}

Player*& Game::GetPlayer(PLAYER_SYMBOL playerSymbol)
{
	if (playerSymbol == PLAYER_SYMBOL::X_PLAYER)
		return m_PlayerX;
	return m_PlayerO;
}

bool Game::GetGameOverStatus() const
{
	return m_GameOver;
}

Board*& Game::GetBoard()
{
	return m_Board;
}

int Game::GetPositionsForMove()
{
	return m_PositionsForMove;
}

const string& Game::GetGameName() const
{
	return m_GameName;
}

//---------------------------------------Methods---------------------------------------//
void Game::EndOfTurn()
{
	auto playersArr = { m_PlayerX, m_PlayerO };
	int i;

	m_Board->DeleteThreatsOnBoard();

	for (auto& currPlayer : playersArr)
	{
		auto& currStonesArr = currPlayer->GetStonesArr();
		int numOfStones = currStonesArr.size();

		for (i = 0; i < numOfStones; ++i)
			currStonesArr[i]->DeletePossibleMoves();
	}

	for (auto& currPlayer : playersArr)
	{
		auto& currStonesArr = currPlayer->GetStonesArr();
		int numOfStones = currStonesArr.size();

		for (i = 0 ; i < numOfStones ; ++i)
			SetStonePossibleMoves(currStonesArr[i]);
	}

	ChangeTurn();
}

void Game::GameOver()
{
	m_GameOver = true;
}

void Game::SaveGameToFile(ofstream& f)
{
	array<Player*, 2> playersArr = { m_PlayerO, m_PlayerX };
	char winner = static_cast<char>(m_Winner);
	char gameOverStatus = m_GameOver, playerSymbol;
	char playerPlaying = static_cast<char>(m_PlayerPlaying);
	int nameLen = m_GameName.size(), rows = m_Board->GetRows(), cols = m_Board->GetCols();
	int numOfStones;

	f.write(rcastcc(&nameLen), sizeof(int));
	f.write(rcastcc(m_GameName.c_str()), nameLen);
	f.write(rcastcc(&m_PositionsForMove), sizeof(int));
	f.write(rcastcc(&winner), sizeof(char));
	f.write(rcastcc(&gameOverStatus), sizeof(char));
	f.write(rcastcc(&playerPlaying), sizeof(char));
	f.write(rcastcc(&rows), sizeof(int));
	f.write(rcastcc(&cols), sizeof(int));

	for (auto& currPlayer : playersArr)
	{
		playerSymbol = static_cast<char>(currPlayer->GetPlayerSymbol());
		vector<Stone*>& stonesArr = currPlayer->GetStonesArr();
		numOfStones = currPlayer->GetNumOfStones();

		f.write(rcastcc(&playerSymbol), sizeof(char));
		f.write(rcastcc(&numOfStones), sizeof(int));

		for (int i = 0; i < numOfStones; ++i)
			SaveStoneToFile(f, stonesArr[i]);
	}
}

void Game::SaveStoneToFile(ofstream& f, Stone* stone)
{
	char symbol = stone->GetSymbol();
	Position pos = stone->GetPosition();

	f.write(rcastcc(&symbol), sizeof(char));
	f.write(rcastcc(&pos), sizeof(pos));
}

void Game::ChangeTurn()
{
	if (m_PlayerPlaying == PLAYER_SYMBOL::X_PLAYER)
		m_PlayerPlaying = PLAYER_SYMBOL::O_PLAYER;
	else
		m_PlayerPlaying = PLAYER_SYMBOL::X_PLAYER;

	m_PlayerO->ChangeTurn();
	m_PlayerX->ChangeTurn();
}

void Game::CheckPossibleMovesForPosition(const Position& pos, int& numOfPossibleMoves)
{
	if (!m_Board->CheckPositionInBoard(pos))
		throw invalid_argument("Invalid position!");
	else if (m_Board->GetCell(pos)->GetHaveStone() == false)
		throw invalid_argument("This position is untaken!");

	numOfPossibleMoves = m_Board->GetCell(pos)->GetStoneInCell()->GetNumOfPossibleMoves();
	if (numOfPossibleMoves == 0)
		throw invalid_argument("There are no possible moves for the position requested.");
}

void Game::MakeAMove(const Position* posArr)
{
	Position stoneCurrPos = posArr[0], stoneNextPos = posArr[1];
	m_Board->UpdateBoard(stoneCurrPos, stoneNextPos);
}

bool Game::CheckDiagonal(const Position& currPos, const Position& nextPos)
{
	int currRow = currPos.row, currCol = currPos.col, nextRow = nextPos.row, nextCol = nextPos.col;

	if (abs(currRow - nextRow) == abs(currCol - nextCol))
		return true;
	return false;
}