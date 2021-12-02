#include "AmazonStone.h"

//---------------------------------------Constructors---------------------------------------//
AmazonStone::AmazonStone(const Position & pos, char symbol, PLAYER_SYMBOL playerProperty, int index)
	: Stone(pos, symbol, playerProperty, index), m_IsBlocked(false){}

AmazonStone::AmazonStone(const AmazonStone& other)
	: Stone(other), m_IsBlocked(other.m_IsBlocked) {}

//---------------------------------------Destructor---------------------------------------//
AmazonStone::~AmazonStone(){}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//
bool AmazonStone::GetBlockedStatus() const
{
	return m_IsBlocked;
}

//---------------------------------------Methods---------------------------------------//
void AmazonStone::AmazonBlocked()
{
	m_IsBlocked = true;
}