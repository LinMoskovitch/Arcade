#pragma once
#include "Stone.h"

enum class CHECKERS_SYMBOL { X_PAWN_SYMBOL = 'x', O_PAWN_SYMBOL = 'o', X_KING_SYMBOL = 'X', O_KING_SYMBOL = 'O' };

class CheckersStone : public Stone
{
public:
	//Constructors
	CheckersStone() = delete;
	CheckersStone(const Position& pos, char symbol, PLAYER_SYMBOL playerProperty, int index);
	CheckersStone(const CheckersStone& other);
	CheckersStone(CheckersStone&& other);

	//Destructor
	virtual ~CheckersStone();

	//Setters
	void SetSymbol(char symbol);

	//Getters
	bool GetKingStatus() const;

	//Methods
	void MakeKing();

private:
	bool m_isKing;
};