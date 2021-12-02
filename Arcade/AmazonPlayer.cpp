#include "AmazonPlayer.h"

//---------------------------------------Constructors---------------------------------------//
AmazonPlayer::AmazonPlayer(PLAYER_SYMBOL symbol, bool turn)
	: Player(symbol,turn), m_BlockedStones(0)
{
	m_NumOfStartingStones = 4;
	SetStonesArr();
}

AmazonPlayer::AmazonPlayer(const AmazonPlayer& other) 
	: Player(other), m_BlockedStones(other.m_BlockedStones)
{
	if (this != &other)
	{
		int size = m_StonesArr.size();

		for (int i = 0; i < size; ++i)
		{
			m_StonesArr.push_back(new AmazonStone(other.m_StonesArr[i]->GetPosition(),
				other.m_StonesArr[i]->GetSymbol(), m_Symbol, i));

			if (nullptr == m_StonesArr[i])
			{
				m_StonesArr.clear();
				throw bad_alloc();
			}
		}
	}
}

AmazonPlayer::AmazonPlayer(AmazonPlayer&& other)
	: Player(other) {}

AmazonPlayer::AmazonPlayer(ifstream& f, PLAYER_SYMBOL symbol)
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
AmazonPlayer::~AmazonPlayer() {}

//---------------------------------------Setters---------------------------------------//
void AmazonPlayer::SetStonesArr()
{
	Position posArr[4];

	if (m_Symbol == PLAYER_SYMBOL::X_PLAYER)
	{//PlayerX amazons
		posArr[0] = { 0, 3 };
		posArr[1] = { 0, 6 };
		posArr[2] = { 3, 0 };
		posArr[3] = { 3, 9 };
	}
	else
	{//PlayerO amazons
		posArr[0] = { 6, 0 };
		posArr[1] = { 6, 9 };
		posArr[2] = { 9, 3 };
		posArr[3] = { 9, 6 };
	}

	for (int i = 0; i < m_NumOfStartingStones; ++i)
	{
		m_StonesArr.push_back(new AmazonStone{ posArr[i] , (char)m_Symbol, m_Symbol, i});
		if (nullptr == m_StonesArr[i])
		{
			m_StonesArr.clear();
			throw bad_alloc();
		}
	}
}

//---------------------------------------Getters---------------------------------------//
int AmazonPlayer::GetNumOfBlockedStones()
{
	return m_BlockedStones;
}

//---------------------------------------Methods---------------------------------------//
void AmazonPlayer::StoneGotBlocked()
{
	++m_BlockedStones;
}

void AmazonPlayer::LoadStoneFromFile(ifstream& f)
{
	char stoneSymbol;
	Position stonePos;
	char isBlocked;

	f.read(rcastc(&stoneSymbol), sizeof(char));
	f.read(rcastc(&stonePos), sizeof(Position));

	m_StonesArr.push_back(new AmazonStone(stonePos, stoneSymbol, m_Symbol, m_StonesArr.size()));

	f.read(rcastc(&isBlocked), sizeof(char));
	if (isBlocked == true)
		static_cast<AmazonStone*>(m_StonesArr[m_StonesArr.size() - 1])->AmazonBlocked();
}