#include "ChessPlayer.h"

//---------------------------------------Constructors---------------------------------------//
ChessPlayer::ChessPlayer(PLAYER_SYMBOL symbol, bool turn)
	: Player(symbol, turn) 
{
	m_NumOfStartingStones = 16;
	SetStonesArr();
}

ChessPlayer::ChessPlayer(const ChessPlayer& other)
	: Player(other) 
{
	if (this != &other)
	{
		int numOfStones = m_StonesArr.size();
		for (int i = 0; i < numOfStones; ++i)
		{
			Stone* currStone = other.m_StonesArr[i];

			if (typeid(*currStone) == typeid(ChessPawn))
				m_StonesArr.push_back(new ChessPawn(*static_cast<ChessPawn*>(currStone)));
			else if (typeid(*currStone) == typeid(ChessKnight))
				m_StonesArr.push_back(new ChessKnight(*static_cast<ChessKnight*>(currStone)));
			else if (typeid(*currStone) == typeid(ChessBishop))
				m_StonesArr.push_back(new ChessBishop(*static_cast<ChessBishop*>(currStone)));
			else if (typeid(*currStone) == typeid(ChessRook))
				m_StonesArr.push_back(new ChessRook(*static_cast<ChessRook*>(currStone)));
			else if (typeid(*currStone) == typeid(ChessQueen))
				m_StonesArr.push_back(new ChessQueen(*static_cast<ChessQueen*>(currStone)));
			else //ChessKing
				m_StonesArr.push_back(new ChessKing(*static_cast<ChessKing*>(currStone)));

			if (nullptr == m_StonesArr[i])
			{
				m_StonesArr.clear();
				throw bad_alloc();
			}
		}
	}
}

ChessPlayer::ChessPlayer(ChessPlayer&& other)
	: Player(other) {}

ChessPlayer::ChessPlayer(ifstream& f, PLAYER_SYMBOL symbol)
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
ChessPlayer::~ChessPlayer() {}

//---------------------------------------Setters---------------------------------------//
void ChessPlayer::SetStonesArr()
{
	int pawnsRow = 1, specialsRow = 0, numOfPawns = static_cast<int>(CHESS_NUMBERS::NUM_OF_PAWNS);
	int symbolChanger = (m_Symbol == PLAYER_SYMBOL::X_PLAYER) ? 'A' - 'a' : 0;
	Position pawnPos;
	
	if (m_Symbol == PLAYER_SYMBOL::O_PLAYER)
	{
		pawnsRow = 6;
		specialsRow = 7;
	}

	//Creating the special stones
	Position specialPosArr[8] = { {specialsRow, 4}, {specialsRow, 3}, {specialsRow, 0}, {specialsRow, 7},{specialsRow, 1},{specialsRow, 6},
		{specialsRow, 2}, {specialsRow, 5} };

	//Creating the king - so the index of the king is always 0 for both players
	m_StonesArr.push_back(new ChessKing(specialPosArr[0],
		static_cast<char>(CHESS_SYMBOL::O_KING) + symbolChanger, 0, m_Symbol));

	//Creating the queen
	m_StonesArr.push_back(new ChessQueen(specialPosArr[1],
		static_cast<char>(CHESS_SYMBOL::O_QUEEN) + symbolChanger, 1, m_Symbol));

	//Creating the rooks
	m_StonesArr.push_back(new ChessRook(specialPosArr[2],
		static_cast<char>(CHESS_SYMBOL::O_ROOK) + symbolChanger, 2, m_Symbol));
	m_StonesArr.push_back(new ChessRook(specialPosArr[3],
		static_cast<char>(CHESS_SYMBOL::O_ROOK) + symbolChanger, 3, m_Symbol));

	//Creating the knights
	m_StonesArr.push_back(new ChessKnight(specialPosArr[4],
		static_cast<char>(CHESS_SYMBOL::O_KNIGHT) + symbolChanger, 4, m_Symbol));
	m_StonesArr.push_back(new ChessKnight(specialPosArr[5],
		static_cast<char>(CHESS_SYMBOL::O_KNIGHT) + symbolChanger, 5, m_Symbol));

	//Creating the bishops
	m_StonesArr.push_back(new ChessBishop(specialPosArr[6],
		static_cast<char>(CHESS_SYMBOL::O_BISHOP) + symbolChanger, 6, m_Symbol));
	m_StonesArr.push_back(new ChessBishop(specialPosArr[7],
		static_cast<char>(CHESS_SYMBOL::O_BISHOP) + symbolChanger, 7, m_Symbol));

	for (int i = 8; i < 16; ++i)
	{//Creating the pawns
		pawnPos = { pawnsRow, i % 8 };
		m_StonesArr.push_back(new ChessPawn(pawnPos,
			static_cast<char>(CHESS_SYMBOL::O_PAWN) + symbolChanger, i, m_Symbol));
	}

	for (int i = 0; i < 16; ++i)
	{//Checking if any of the allocations failed
		if (nullptr == m_StonesArr[i])
		{
			m_StonesArr.clear();
			throw bad_alloc();
		}
	}
}

void ChessPlayer::LoadStoneFromFile(ifstream& f)
{
	char cStoneSymbol;
	Position stonePos;
	char firstMove;
	CHESS_SYMBOL eStoneSymbol;

	f.read(rcastc(&cStoneSymbol), sizeof(char));
	f.read(rcastc(&stonePos), sizeof(Position));

	eStoneSymbol = static_cast<CHESS_SYMBOL>(cStoneSymbol);

	if (CHESS_SYMBOL::O_PAWN == eStoneSymbol || CHESS_SYMBOL::X_PAWN == eStoneSymbol)
	{
		m_StonesArr.push_back(new ChessPawn(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
		f.read(rcastc(&firstMove), sizeof(char));

		if (!firstMove)
			static_cast<ChessPawn*>(m_StonesArr[m_StonesArr.size() - 1])->MadeFirstMove();
	}
	else if (CHESS_SYMBOL::O_KNIGHT == eStoneSymbol || CHESS_SYMBOL::X_KNIGHT == eStoneSymbol)
		m_StonesArr.push_back(new ChessKnight(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
	else if (CHESS_SYMBOL::O_ROOK == eStoneSymbol || CHESS_SYMBOL::X_ROOK == eStoneSymbol)
		m_StonesArr.push_back(new ChessRook(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
	else if (CHESS_SYMBOL::O_BISHOP == eStoneSymbol || CHESS_SYMBOL::X_BISHOP == eStoneSymbol)
		m_StonesArr.push_back(new ChessBishop(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
	else if (CHESS_SYMBOL::O_QUEEN == eStoneSymbol || CHESS_SYMBOL::X_QUEEN == eStoneSymbol)
		m_StonesArr.push_back(new ChessQueen(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
	else //CHESS_SYMBOL::O_KING == eStoneSymbol || CHESS_SYMBOL::X_KING == eStoneSymbol
		m_StonesArr.push_back(new ChessKing(stonePos, cStoneSymbol, m_StonesArr.size(), m_Symbol));
}

//---------------------------------------Getters---------------------------------------//


//---------------------------------------Methods---------------------------------------//
