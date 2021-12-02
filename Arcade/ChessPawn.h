#pragma once
#include "ChessStone.h"

class ChessPawn : public ChessStone
{
public:
	//Constructors
	ChessPawn() = delete;
	ChessPawn(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessPawn(const ChessPawn& other);
	ChessPawn(ChessPawn&& other);

	//Destructor
	virtual ~ChessPawn();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);
	void MadeFirstMove();

	//Getters
	bool GetFirstTurn() const;

	//Methods

private:
	bool m_FirstTurn;
};