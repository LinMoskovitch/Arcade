#pragma once
#include "Cell.h"

class Board
{//Abstract class
protected:
	//Constructors
	Board() = delete;
	Board(int rows,int cols);
	Board(const Board& other);
	Board(Board&& other);
public:
	//Destructor
	virtual ~Board();

	//Setters
	void SetStoneInCell(Stone* stone, const Position& stonePos);

	//Getters
	Cell*& GetCell(const Position& pos);
	vector<vector<Cell*>>& GetBoard();
	int GetRows();
	int GetCols();

	//Methods
	void UpdateBoard(const Position& prevPos, const Position& nextPos);
	void InitBoard(vector<Stone*> PlayerOStones, vector<Stone*> PlayerXStones);
	virtual void PrintBoard(ostream& os);
	void PrintSeparateLine(ostream& os) const;
	bool CheckPositionInBoard(const Position& pos);
	virtual void ValidationCheckForThreatsRequest(const Position& pos);
	void DeleteThreatsOnBoard();

	//Operators
	friend ostream& operator<<(ostream& os, Board& board);
	
protected:
	vector<vector<Cell*>> m_CellsArr;
	int m_Rows;
	int m_Cols;
};