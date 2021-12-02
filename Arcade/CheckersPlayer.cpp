#include "CheckersPlayer.h"

//---------------------------------------Constructors---------------------------------------//
CheckersPlayer::CheckersPlayer(PLAYER_SYMBOL symbol, bool turn)
	: Player(symbol, turn) 
{
	m_NumOfStartingStones = 12;
	SetStonesArr();
}

CheckersPlayer::CheckersPlayer(const CheckersPlayer& other)
	: Player(other)
{
	if (this != &other)
	{
		int numOfStones = m_StonesArr.size();
		for (int i = 0; i < numOfStones; ++i)
		{
			m_StonesArr.push_back(new CheckersStone(other.m_StonesArr[i]->GetPosition(),
				other.m_StonesArr[i]->GetSymbol(), m_Symbol, other.m_StonesArr[i]->GetStoneIndexInArr()));

			if (nullptr == m_StonesArr[i])
			{
				m_StonesArr.clear();
				throw bad_alloc();
			}
		}
	}
}

CheckersPlayer::CheckersPlayer(CheckersPlayer&& other)
	: Player(other) {}

CheckersPlayer::CheckersPlayer(ifstream& f, PLAYER_SYMBOL symbol)
	: Player(f, symbol)
{
	int numOfStones;

	f.read(rcastc(&numOfStones), sizeof(int));
	for (int i = 0; i < numOfStones; ++i)
	{
		LoadStoneFromFile(f);
	}
}

//---------------------------------------Destructor---------------------------------------//
CheckersPlayer::~CheckersPlayer() {}

//---------------------------------------Setters---------------------------------------//
void CheckersPlayer::SetStonesArr()
{
	Stone* currStone;
	int i, currRow, currCol, counter = 0;
	Position currPos;
	char symbol;

	if (m_Symbol == PLAYER_SYMBOL::O_PLAYER) //PLAYERO stones
	{
		currRow = 5;
		currCol = 0;
		symbol = static_cast<char>(CHECKERS_SYMBOL::O_PAWN_SYMBOL);
	}
	else //PLAYERX stones
	{
		currRow = 0;
		currCol = 1;
		symbol = static_cast<char>(CHECKERS_SYMBOL::X_PAWN_SYMBOL);
	}

	for (i = 0; i < m_NumOfStartingStones; ++i)
	{
		currPos = { currRow, currCol % 8 };
		m_StonesArr.push_back(new CheckersStone(currPos, symbol, m_Symbol, i));

		if (nullptr == m_StonesArr[i])
		{
			m_StonesArr.clear();
			throw bad_alloc();
		}

		if (++counter % 4 == 0)
		{
			if (++currRow % 2 == 0)
				currCol = 1;
			else
				currCol = 0;
		}
		else
			currCol += 2;
	}
}

void CheckersPlayer::LoadStoneFromFile(ifstream& f)
{
	char stoneSymbol;
	Position stonePos;
	char isKing;

	f.read(rcastc(&stoneSymbol), sizeof(char));
	f.read(rcastc(&stonePos), sizeof(Position));

	m_StonesArr.push_back(new CheckersStone(stonePos, stoneSymbol, m_Symbol, m_StonesArr.size()));
	
	f.read(rcastc(&isKing), sizeof(char));
	if (isKing == true)
		static_cast<CheckersStone*>(m_StonesArr[m_StonesArr.size() - 1])->MakeKing();
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
