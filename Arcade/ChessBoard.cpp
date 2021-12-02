#include "ChessBoard.h"

//---------------------------------------Constructors---------------------------------------//
ChessBoard::ChessBoard(int rows, int cols)
	: Board(rows, cols)
{
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Cols; ++j)
		{
			m_CellsArr[i].push_back(new ChessCell());

			if (nullptr == m_CellsArr[i][j])
			{//Allocation failed for current cell
				for (int i1 = 0; i1 <= i; ++i1)
				{
					m_CellsArr.clear();
					throw bad_alloc();
				}
			}
		}
	}
}

ChessBoard::ChessBoard(const ChessBoard& other)
	: Board(other), m_KingPosPlayerX(other.m_KingPosPlayerX),
	  m_KingPosPlayerO(other.m_KingPosPlayerO)
{
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Cols; ++j)
		{
			ChessCell* currCell = static_cast<ChessCell*>(other.m_CellsArr[i][j]);
			m_CellsArr[i][j] = new ChessCell(*currCell);

			if (nullptr == m_CellsArr[i][j])
			{//Allocation failed for current cell
				for (int i1 = 0; i1 <= i; ++i1)
				{
					for (int j1 = 0; j1 < j; ++j1)
					{
						delete m_CellsArr[i1][j1];
					}
				}
				throw bad_alloc();
			}
		}
	}
}

ChessBoard::ChessBoard(ChessBoard&& other)
	: Board(other), m_KingPosPlayerX(other.m_KingPosPlayerX),
	  m_KingPosPlayerO(other.m_KingPosPlayerO) {}

//---------------------------------------Destructor---------------------------------------//
ChessBoard::~ChessBoard() {}

//---------------------------------------Setters---------------------------------------//
void ChessBoard::SetKingPos(PLAYER_SYMBOL playerPlaying, const Position& kingNewPos)
{
	if (playerPlaying == PLAYER_SYMBOL::O_PLAYER)
		m_KingPosPlayerO = kingNewPos;
	else //playerPlaying == PLAYER_SYMBOL::X_PLAYER
		m_KingPosPlayerX = kingNewPos;
}

//---------------------------------------Getters---------------------------------------//
const Position& ChessBoard::GetKingPos(PLAYER_SYMBOL playerPlaying)
{
	if (playerPlaying == PLAYER_SYMBOL::O_PLAYER)
		return m_KingPosPlayerO;
	return m_KingPosPlayerX;
}

//---------------------------------------Methods---------------------------------------//
bool ChessBoard::ValidationCheckForThreatsRequest(const Position& pos, string& errorMessage)
{
	if (!CheckPositionInBoard(pos))
	{
		errorMessage = "Invalid position!";
		return false;
	}
	else if (!GetCell(pos)->GetHaveStone())
	{
		errorMessage = "This position has no stone!";
		return false;
	}

	return true;
}