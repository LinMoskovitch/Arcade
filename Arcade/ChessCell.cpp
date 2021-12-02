#include "ChessCell.h"

//---------------------------------------Constructors---------------------------------------//
ChessCell::ChessCell()
	: Cell() {}

ChessCell::ChessCell(const ChessCell& other)
	: Cell(other) {}

ChessCell::ChessCell(ChessCell&& other)
	: Cell(other) {}

//---------------------------------------Destructor---------------------------------------//
ChessCell::~ChessCell() {}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
void ChessCell::AddNewThreat(const Position& newThreat)
{
	m_ThreatsArr.push_back(newThreat);
}