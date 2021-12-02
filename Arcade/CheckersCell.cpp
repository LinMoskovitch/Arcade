#include "CheckersCell.h"

//---------------------------------------Constructors---------------------------------------//
CheckersCell::CheckersCell() 
	: Cell() {}

CheckersCell::CheckersCell(const CheckersCell & other) 
	: Cell(other) {}

CheckersCell::CheckersCell(CheckersCell && other) 
	: Cell(other) {}

//---------------------------------------Destructor---------------------------------------//
CheckersCell::~CheckersCell() {}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
void CheckersCell::AddNewThreat(const Position& newThreat)
{
	m_ThreatsArr.push_back(newThreat);
}