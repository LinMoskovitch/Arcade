#pragma once
#include "Cell.h"
#include "CheckersStone.h"

class CheckersCell : public Cell
{
public:
	//Constructors
	CheckersCell();
	CheckersCell(const CheckersCell& other);
	CheckersCell(CheckersCell&& other);

	//Destructor
	virtual ~CheckersCell();

	//Getters
	
	//Setters

	//Methods
	void AddNewThreat(const Position& newThreat);

private:
	
};

