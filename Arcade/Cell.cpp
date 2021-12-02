#include "Cell.h"

//---------------------------------------Constructors---------------------------------------//
Cell::Cell()
	: m_haveStone(false), m_pStone(nullptr) {}

Cell::Cell(const Cell& other) 
	: m_haveStone(other.m_haveStone), m_pStone(other.m_pStone)
{
	try
	{
		if (this != &other)
			m_ThreatsArr = other.m_ThreatsArr;
	}
	catch (bad_alloc& ba)
	{
		m_ThreatsArr.clear();
		throw;
	}
}

Cell::Cell(Cell&& other) 
	: m_haveStone(other.m_haveStone), m_pStone(other.m_pStone)
{
	m_ThreatsArr = move(other.m_ThreatsArr);

	other.m_pStone = nullptr;
	other.m_haveStone = false;
}

//---------------------------------------Destructor---------------------------------------//
Cell::~Cell()
{
	m_pStone = nullptr;
}

//---------------------------------------Setters---------------------------------------//
void Cell::SetStone(Stone* stone)
{
	m_haveStone = true;
	m_pStone = stone;
}

void Cell::SetThreats(vector<Position> threatsArr)
{
	m_ThreatsArr = threatsArr;
}

void Cell::SetHaveStone(bool ind)
{
	m_haveStone = ind;
}

//---------------------------------------Getters---------------------------------------//
bool Cell::GetHaveStone() const
{
	return m_haveStone;
}

Stone*& Cell::GetStoneInCell()
{
	return m_pStone;
}

vector<Position>& Cell::GetThreatsArr()
{
	return m_ThreatsArr;
}

int Cell::GetNumOfThreats() const
{
	return m_ThreatsArr.size();
}

//---------------------------------------Methods---------------------------------------//
void Cell::RemoveStoneFromCell()
{
	m_haveStone = false;
	m_pStone = nullptr;
}

void Cell::DeleteThreats()
{
	m_ThreatsArr.clear();
}