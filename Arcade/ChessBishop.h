#pragma once
#include "ChessStone.h"

class ChessBishop : public ChessStone
{
public:
	//Constructors
	ChessBishop() = delete;
	ChessBishop(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessBishop(const ChessBishop& other);
	ChessBishop(ChessBishop&& other);

	//Destructor
	virtual ~ChessBishop();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);

	//Getters


	//Methods

private:

};

