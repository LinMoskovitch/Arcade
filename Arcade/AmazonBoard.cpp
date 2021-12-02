#include "AmazonBoard.h"

//---------------------------------------Constructors---------------------------------------//
AmazonBoard::AmazonBoard(int rows,int cols) 
	: Board(rows,cols)
{
	int i, j;
	try
	{
		for (i = 0; i < m_Rows; ++i)
		{
			for (j = 0; j < m_Cols; ++j)
				m_CellsArr[i].push_back(new AmazonCell());
		}
	}
	catch (bad_alloc& ba)
	{
		for (int k = 0; k <= i; ++k)
		{
			for (int h = 0; h < j; ++h)
				delete m_CellsArr[k][h];
		}
		throw;
	}
}

AmazonBoard::AmazonBoard(const AmazonBoard& other)
	: Board(other) 
{
	int i, j;
	try
	{
		if (this != &other)
		{
			for (i = 0; i < m_Rows; ++i)
			{
				for (j = 0; j < m_Cols; ++j)
				{
					AmazonCell* currCell = static_cast<AmazonCell*>(other.m_CellsArr[i][j]);
					m_CellsArr[i].push_back(new AmazonCell(*currCell));
				}
			}
		}
	}
	catch (bad_alloc& ba)
	{
		for (int k = 0; k <= i; ++k)
		{
			for (int h = 0; h < j; ++h)
				delete m_CellsArr[k][h];
		}
		throw;
	}
}

AmazonBoard::AmazonBoard(AmazonBoard&& other)
	: Board(other) {}

//---------------------------------------Destructor---------------------------------------//
AmazonBoard::~AmazonBoard() {}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//
AmazonCell* AmazonBoard::GetCell(const Position & pos) const
{
	return static_cast<AmazonCell*>(m_CellsArr[pos.row][pos.col]);
}

const vector<Position>& AmazonBoard::GetMarkedPositions() const
{
	return m_MarkedPositions;
}

//---------------------------------------Methods---------------------------------------//
void AmazonBoard::PrintBoard(ostream& os)
{//Prints the board
		int i;
		Position pos;
		AmazonCell* currCell;
		PrintSeparateLine(os);

		//Printing the row of columns index
		os << "|   ";
		for (i = 0; i < m_Cols; ++i)
		{
			os << "| " << i + 1 << " ";
		}
		os << "|";

		PrintSeparateLine(os);

		//Printing the board itself
		for (pos.row = 0; pos.row < m_Rows; ++pos.row)
		{

			os << "| " << pos.row + 1;
			if (pos.row < 9)
				os << " ";

			for (pos.col = 0; pos.col < m_Cols; ++pos.col)
			{
				currCell = static_cast<AmazonCell*>(GetCell(pos));
				os << "| ";
				if (currCell->GetHaveStone() == true)
					os << (char)currCell->GetStoneInCell()->GetSymbol() << " ";
				else if (currCell->GetMarkedStatus() == true)
					os << (char)AMAZON_SYMBOL::MARKED_SYMBOL<< " ";
				else
					os << "  ";

				if (pos.col >= 9)
					os << " ";
			}
			os << "|";
			PrintSeparateLine(os);
		}
	}

void AmazonBoard::MarkPosition(const Position& pos)
{
	(static_cast<AmazonCell*>(m_CellsArr[pos.row][pos.col]))->CellMarked();
	m_MarkedPositions.push_back(pos);
}

bool AmazonBoard::ValidationCheckForThreatsRequest(const Position& pos, string& errorMessage)
{
	if (!CheckPositionInBoard(pos))
	{
		errorMessage = "Invalid position!";
		return false;
	}
	else if (GetCell(pos)->GetHaveStone() == true)
	{
		errorMessage = "This position has an amazon!";
		return false;
	}
	else if (GetCell(pos)->GetMarkedStatus() == true)
	{
		errorMessage = "This position is already marked!";
		return false;
	}

	return true;
}

void AmazonBoard::MarkPositionsFromFile(ifstream& f)
{
	int numOfMarked;
	Position markedPos;
	
	f.read(rcastc(&numOfMarked), sizeof(int));
	m_MarkedPositions.resize(numOfMarked);
	
	for (int i = 0; i < numOfMarked; ++i)
	{
		f.read(rcastc(&markedPos), sizeof(Position));
		static_cast<AmazonCell*>(m_CellsArr[markedPos.row][markedPos.col])->CellMarked();
		m_MarkedPositions[i] = markedPos;
	}
}
