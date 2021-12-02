#include "Stone.h"

//---------------------------------------Constructors---------------------------------------//
Stone::Stone(const Position& pos, const char symbol, PLAYER_SYMBOL playerProperty, int index)
	: m_Position(pos), m_Symbol(symbol), m_PlayerProperty(playerProperty), m_StoneIndexInArr(index) {}

Stone::Stone(const Stone& other)
	: m_Position(other.m_Position), m_Symbol(other.m_Symbol),
	  m_PlayerProperty(other.m_PlayerProperty), m_StoneIndexInArr(other.m_StoneIndexInArr)
{
	try
	{
		if (this != &other)
			m_PossibleMoves = other.m_PossibleMoves;
	}
	catch (bad_alloc& ba)
	{
		m_PossibleMoves.clear();
		throw;
	}
}

Stone::Stone(Stone&& other)
	: m_Position(other.m_Position), m_StoneIndexInArr(other.m_StoneIndexInArr),
	  m_PlayerProperty(other.m_PlayerProperty), m_Symbol(other.m_Symbol)
{
	if (this != &other)
		m_PossibleMoves = move(other.m_PossibleMoves);
}

//---------------------------------------Destructor---------------------------------------//
Stone::~Stone()
{
	DeletePossibleMoves();
}

//---------------------------------------Setters---------------------------------------//
void Stone::SetPosition(const Position& pos)
{
	m_Position = pos;
}

void Stone::SetStoneIndex(int index)
{
	m_StoneIndexInArr = index;
}

//---------------------------------------Getters---------------------------------------//
char Stone::GetSymbol() const
{
	return m_Symbol;
}

const Position& Stone::GetPosition() const
{
	return m_Position;
}

vector<Position>& Stone::GetPossibleMoves()
{
	return m_PossibleMoves;
}

int Stone::GetNumOfPossibleMoves() const
{
	return m_PossibleMoves.size();
}

PLAYER_SYMBOL Stone::GetPlayerProperty() const
{
	return m_PlayerProperty;
}

int Stone::GetStoneIndexInArr() const
{
	return m_StoneIndexInArr;
}

//---------------------------------------Methods---------------------------------------//
void Stone::AddPossibleMove(const Position& pos)
{
	m_PossibleMoves.push_back(pos);
}

void Stone::DeletePossibleMoves()
{
	m_PossibleMoves.clear();
}

//---------------------------------------Operators---------------------------------------//
bool operator==(const Position& pos1, const Position& pos2)
{
	return (pos1.row == pos2.row) && (pos1.col == pos2.col);
}

bool operator!=(const Position& pos1, const Position& pos2)
{
	return (pos1.row != pos2.row) || (pos1.col != pos2.col);
}

ostream& operator<<(ostream& os, const Position& pos)
{
	os << "(" << pos.row << "," << pos.col << ")";
	return os;
}

istream& operator>>(istream& is, Position& pos)
{
	is >> pos.row >> pos.col;
	return is;
}