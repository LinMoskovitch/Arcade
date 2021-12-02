#pragma once
#include "Board.h"
#include "AmazonCell.h"

enum class AMAZONS_NUMBERS { ROWS = 10, COLS = 10 };

class AmazonBoard : public Board
{
public:
	//Constructors
	AmazonBoard() = delete;
	AmazonBoard(int rows,int cols);
	AmazonBoard(const AmazonBoard& other);
	AmazonBoard(AmazonBoard&& other);

	//Destructor
	virtual ~AmazonBoard();//d'tor

	//Setters
	
	//Getters
	AmazonCell* GetCell(const Position& pos) const;
	const vector<Position>& GetMarkedPositions() const;

	//Methods
	virtual void PrintBoard(ostream& os);
	void MarkPosition(const Position& pos);
	virtual bool ValidationCheckForThreatsRequest(const Position& pos, string& errorMessage);
	void MarkPositionsFromFile(ifstream& f);

private:
	vector<Position> m_MarkedPositions;
};

