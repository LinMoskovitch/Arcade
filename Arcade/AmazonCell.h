#pragma once
#include "Cell.h"
#include "AmazonStone.h"

class AmazonCell : public Cell
{
public:
	//Constructors
	AmazonCell();
	AmazonCell(const AmazonCell& other);
	AmazonCell(AmazonCell&& other);

	//Destructor
	virtual ~AmazonCell();

	//Getters
	bool GetMarkedStatus() const;

	//Setters
	void CellMarked();

	//Methods

private:
	bool m_marked;
};