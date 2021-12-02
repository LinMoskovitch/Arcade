#include "Player.h"

//---------------------------------------Constructors---------------------------------------//
Player::Player(PLAYER_SYMBOL symbol, bool turn)
	: m_Symbol(symbol), m_Turn(turn), m_Won(false), m_NumOfStartingStones(0) {}

Player::Player(const Player& other)
	: m_Turn(other.m_Turn), m_Won(other.m_Won),
	  m_Symbol(other.m_Symbol), m_NumOfStartingStones(other.m_NumOfStartingStones) {}

Player::Player(Player&& other)
	: m_Turn(other.m_Turn), m_Won(other.m_Won), m_Symbol(other.m_Symbol),
	  m_NumOfStartingStones(other.m_NumOfStartingStones)
{
	if (this != &other)
		m_StonesArr = move(other.m_StonesArr);
}

Player::Player(ifstream& f, PLAYER_SYMBOL symbol)
	: m_Won(false), m_Turn(false), m_NumOfStartingStones(0)
{
	m_Symbol = symbol;
}

//---------------------------------------Destructor---------------------------------------//
Player::~Player() {}

void Player::SetTurn(bool ind)
{
	m_Turn = ind;
}

//---------------------------------------Getters---------------------------------------//
bool Player::GetTurn() const
{
	return m_Turn;
}

bool Player::GetWinner() const
{
	return m_Won;
}

vector<Stone*>& Player::GetStonesArr()
{
	return m_StonesArr;
}

PLAYER_SYMBOL Player::GetPlayerSymbol() const
{
	return m_Symbol;
}

int Player::GetNumOfStones() const
{
	return m_StonesArr.size();
}

int Player::GetNumOfStartingStones() const
{
	return m_NumOfStartingStones;
}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
void Player::ChangeTurn()
{
	m_Turn = true - m_Turn;
}

void Player::PlayerWon()
{
	m_Won = true;
}

void Player::DeleteStoneFromArr(Stone* toDelete)
{
	int index = toDelete->GetStoneIndexInArr();

	Swap(m_StonesArr.at(index), m_StonesArr.at(m_StonesArr.size() - 1));
	m_StonesArr[index]->SetStoneIndex(index);

	delete m_StonesArr[m_StonesArr.size() - 1];
	m_StonesArr.pop_back();
}