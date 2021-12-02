#include "CheckersStone.h"

//---------------------------------------Constructors---------------------------------------//
CheckersStone::CheckersStone(const Position & pos, char symbol, PLAYER_SYMBOL playerProperty, int index)
	: Stone(pos, symbol, playerProperty, index), m_isKing(false) {}

CheckersStone::CheckersStone(const CheckersStone & other) 
	: Stone(other), m_isKing(other.m_isKing) {}

CheckersStone::CheckersStone(CheckersStone&& other)
	: Stone(other), m_isKing(other.m_isKing) {}

//---------------------------------------Destructor---------------------------------------//
CheckersStone::~CheckersStone() {}

//---------------------------------------Setters---------------------------------------//
void CheckersStone::SetSymbol(char symbol)
{
	m_Symbol = symbol;
}

//---------------------------------------Getters---------------------------------------//
bool CheckersStone::GetKingStatus() const
{
	return m_isKing;
}

//---------------------------------------Methods---------------------------------------//
void CheckersStone::MakeKing()
{
	m_isKing = true;

	if (m_Symbol ==(char) CHECKERS_SYMBOL::O_PAWN_SYMBOL)
		m_Symbol = (char)CHECKERS_SYMBOL::O_KING_SYMBOL;
	else
		m_Symbol = (char)CHECKERS_SYMBOL::X_KING_SYMBOL;
}