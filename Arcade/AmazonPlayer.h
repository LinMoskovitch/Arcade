#pragma once
#include "Player.h"
#include "AmazonBoard.h"

class AmazonPlayer : public Player
{
public:
	//Constructors
	AmazonPlayer() = delete;
	AmazonPlayer(PLAYER_SYMBOL symbol, bool turn);
	AmazonPlayer(const AmazonPlayer& other);
	AmazonPlayer(AmazonPlayer&& other);
	AmazonPlayer(ifstream& f, PLAYER_SYMBOL symbol);

	//Destructor
	virtual ~AmazonPlayer();

	//Setters
	void SetStonesArr();

	//Getters
	int GetNumOfBlockedStones();

	//Methods
	void StoneGotBlocked();
	virtual void LoadStoneFromFile(ifstream& f);

private:
	int m_BlockedStones;
};

