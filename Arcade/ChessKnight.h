#pragma once
#include "ChessStone.h"

class ChessKnight : public ChessStone
{
public:
	//Constructors
	ChessKnight() = delete;
	ChessKnight(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessKnight(const ChessKnight& other);
	ChessKnight(ChessKnight&& other);

	//Destructor
	virtual ~ChessKnight();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);

	//Getters
	

	//Methods

private:

};

