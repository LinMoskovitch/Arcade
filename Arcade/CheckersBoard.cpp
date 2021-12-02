#include "CheckersBoard.h"

//---------------------------------------Constructors---------------------------------------//
CheckersBoard::CheckersBoard(int rows, int cols)
	: Board(rows, cols)
{
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Cols; ++j)
		{
			m_CellsArr[i].push_back(new CheckersCell());

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

CheckersBoard::CheckersBoard(const CheckersBoard& other)
	: Board(other) 
{
	if (this != &other)
	{
		for (int i = 0; i < m_Rows; ++i)
		{
			for (int j = 0; j < m_Cols; ++j)
			{
				CheckersCell* currCell = static_cast<CheckersCell*>(other.m_CellsArr[i][j]);
				m_CellsArr[i][j] = new CheckersCell(*currCell);

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
}

CheckersBoard::CheckersBoard(CheckersBoard&& other)
	: CheckersBoard(other) {}

//---------------------------------------Destructor---------------------------------------//
CheckersBoard::~CheckersBoard() {}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//
CheckersCell* CheckersBoard::GetCell(const Position & pos) const
{
	return static_cast<CheckersCell*>(m_CellsArr[pos.row][pos.col]);
}

//---------------------------------------Methods---------------------------------------//