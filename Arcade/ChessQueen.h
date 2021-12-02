#pragma once
#include "ChessStone.h"

class ChessQueen : public ChessStone
{
public:
	//Constructors
	ChessQueen() = delete;
	ChessQueen(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessQueen(const ChessQueen& other);
	ChessQueen(ChessQueen&& other);

	//Destructor
	virtual ~ChessQueen();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);

	//Getters
	

	//Methods

private:

};

