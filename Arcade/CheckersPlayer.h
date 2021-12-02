#pragma once
#include "Player.h"
#include "CheckersBoard.h"

class CheckersPlayer : public Player
{
public:
	//Constructors
	CheckersPlayer() = delete;
	CheckersPlayer(PLAYER_SYMBOL symbol, bool turn);
	CheckersPlayer(const CheckersPlayer& other);
	CheckersPlayer(CheckersPlayer&& other);
	CheckersPlayer(ifstream& f, PLAYER_SYMBOL symbol);

	//Destructor
	virtual ~CheckersPlayer();

	//Setters
	virtual void SetStonesArr();

	//Getters

	//Methods
	virtual void LoadStoneFromFile(ifstream& f);

private:

};

