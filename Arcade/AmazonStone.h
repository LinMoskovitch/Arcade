#pragma once
#include "Stone.h"

enum class AMAZON_SYMBOL { X_SYMBOL = 'X', O_SYMBOL = 'O', MARKED_SYMBOL = '#' };

class AmazonStone : public Stone
{
public:
	//Constructors
	AmazonStone() = delete;
	AmazonStone(const Position& pos, char symbol, PLAYER_SYMBOL playerProperty, int index);
	AmazonStone(const AmazonStone& other);

	//Destructor
	virtual ~AmazonStone();

	//Setters
	void AmazonBlocked();

	//Getters
	bool GetBlockedStatus() const;

private:
	bool m_IsBlocked;
};