#pragma once

#include "Stone.h"
class Cell
{
public:
	//Constructors
	Cell();
	Cell(const Cell& other);
	Cell(Cell&& other);

	//Destructor
	virtual ~Cell();

	//Setters
	void SetStone(Stone* stone);
	void SetThreats(vector<Position> threatsArr);
	void SetHaveStone(bool ind);

	//Getters
	bool GetHaveStone() const;
	Stone*& GetStoneInCell();
	vector<Position>& GetThreatsArr();
	int GetNumOfThreats() const;

	//Methods
	void RemoveStoneFromCell();
	void DeleteThreats();
	
	//Operators

protected:
	bool m_haveStone;
	Stone* m_pStone;
	vector<Position> m_ThreatsArr;
};