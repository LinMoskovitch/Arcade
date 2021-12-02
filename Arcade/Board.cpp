#include "Board.h"

//---------------------------------------Constructors---------------------------------------//
Board::Board(int rows, int cols) : m_Rows(rows), m_Cols(cols) 
{
	try
	{
		m_CellsArr.resize(rows);
	}
	catch (bad_alloc& ba)
	{
		m_CellsArr.clear();
		throw;
	}
}

Board::Board(const Board& other) 
	: m_Rows(other.m_Rows), m_Cols(other.m_Cols) {}

Board::Board(Board&& other)
	: m_Rows(other.m_Rows), m_Cols(other.m_Cols)
{
	if (this != &other)
		m_CellsArr = move(other.m_CellsArr);
}

//---------------------------------------Destructor---------------------------------------//
Board::~Board() {}

//---------------------------------------Setters---------------------------------------//
void Board::SetStoneInCell(Stone* stone, const Position& stonePos)
{
	m_CellsArr[stonePos.row][stonePos.col]->SetStone(stone);
}

//---------------------------------------Getters---------------------------------------//
Cell*& Board::GetCell(const Position& pos)
{
	return m_CellsArr[pos.row][pos.col];
}

vector<vector<Cell*>>& Board::GetBoard()
{
	return m_CellsArr;
}

int Board::GetRows()
{
	return m_Rows;
}

int Board::GetCols()
{
	return m_Cols;
}

//---------------------------------------Methods---------------------------------------//
void Board::UpdateBoard(const Position& oldPos, const Position& newPos)
{
	Swap(m_CellsArr[newPos.row][newPos.col], m_CellsArr[oldPos.row][oldPos.col]);
	m_CellsArr[newPos.row][newPos.col]->GetStoneInCell()->SetPosition(newPos);
}

void Board::InitBoard(vector<Stone*> PlayerOStones, vector<Stone*> PlayerXStones)
{
	auto PlayersStonesArr = { PlayerOStones , PlayerXStones };

	for (auto& currPlayerStones : PlayersStonesArr)
	{
		int size = currPlayerStones.size();
		for (int i = 0; i < size; ++i)
		{
			SetStoneInCell(currPlayerStones[i], currPlayerStones[i]->GetPosition());
		}
	}
}

void Board::PrintBoard(ostream& os)
{
	int i;
	Position pos;
	Cell* currCell;
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
		os << "| " << pos.row + 1 << " ";
		for (pos.col = 0; pos.col < m_Cols; ++pos.col)
		{
			os << "| ";
			currCell = GetCell(pos);
			if (currCell->GetHaveStone() == true)
				os << (char)currCell->GetStoneInCell()->GetSymbol() << " ";
			else
				os << "  ";
		}
		os << "|";
		PrintSeparateLine(os);
	}
}

 void Board::PrintSeparateLine(ostream& os) const
{//helper for printion the board
	int i;

	os << endl;
	for (i = 0; i < m_Cols + 1; ++i)
	{
		os << "----";
	}
	os << "--" << endl;
}

 bool Board::CheckPositionInBoard(const Position & pos)
 {
	 //this method checks if the position entered is in the boarders.
	 if (pos.row < 0 || pos.row >= m_Rows)
		 return false;
	 else if (pos.col < 0 || pos.col >= m_Cols)
		 return false;

	 return true;
 }

 void Board::ValidationCheckForThreatsRequest(const Position& pos)
 {
	if (!CheckPositionInBoard(pos))
		throw invalid_argument("Invalid position!");
	else if (GetCell(pos)->GetHaveStone() == false)
		throw invalid_argument("This position is empty!");
 }

 void Board::DeleteThreatsOnBoard()
 {
	 for (int i = 0; i < m_Rows; ++i)
	 {
		 for (int j = 0; j < m_Cols; ++j)
		 {
			 m_CellsArr[i][j]->DeleteThreats();
		 }
	 }
 }

 //---------------------------------------Operators---------------------------------------//
 ostream& operator<<(ostream& os, Board& board)
 {
	 board.PrintBoard(os);
	 return os;
 }