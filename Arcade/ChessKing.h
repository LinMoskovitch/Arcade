#pragma once
#include "ChessStone.h"
#include "ChessBoard.h"

class ChessKing : public ChessStone
{
public:
	//Constructors
	ChessKing() = delete;
	ChessKing(const Position& pos, const char symbol, int index, PLAYER_SYMBOL playerProperty);
	ChessKing(const ChessKing& other);
	ChessKing(ChessKing&& other);

	//Destructor
	virtual ~ChessKing();

	//Setters
	virtual void SetPossibleMoves(ChessBoard* board);
	void SetChecked(bool newCheckedMode);

	//Getters
	bool GetCheckedStatus() const;

	//Methods


private:
	bool m_Checked;
};

