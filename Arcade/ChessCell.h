#pragma once
#include "Cell.h"
#include "ChessStone.h"
#include "ChessPawn.h"
#include "ChessRook.h"
#include "ChessBishop.h"
#include "ChessKnight.h"
#include "ChessQueen.h"
#include "ChessKing.h"

class ChessCell : public Cell
{
public:
	//Constructors
	ChessCell();
	ChessCell(const ChessCell& other);
	ChessCell(ChessCell&& other);

	//Desturctor
	virtual ~ChessCell();

	//Methods
	void AddNewThreat(const Position& newThreat);

private:

};