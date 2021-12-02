#pragma once
#include "Board.h"
#include "CheckersCell.h"

enum class CHECKERS_NUMBERS { ROWS = 8, COLS = 8 };

class CheckersBoard : public Board
{
public:
	//Constructors
	CheckersBoard() = delete;
	CheckersBoard(int rows, int cols);
	CheckersBoard(const CheckersBoard& other);
	CheckersBoard(CheckersBoard&& other);

	//Destructor
	virtual ~CheckersBoard();

	//Setters

	//Getters
	CheckersCell* GetCell(const Position& pos) const;

	//Methods
	
private:


};

