#pragma once
#include "ChessStone.h"

class ChessRook : public ChessStone
{
public:
	//Constructors
	ChessRook() = delete;
	ChessRook(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessRook(const ChessRook& other);
	ChessRook(ChessRook&& other);

	//Destructor
	virtual ~ChessRook();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);

	//Getters


	//Methods

private:

};

