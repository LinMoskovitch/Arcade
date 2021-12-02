#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4267)

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <exception>
#include <array>
#include <string>
#include <list>
#include <vector>

#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*> 

using namespace std;

enum class PLAYER_SYMBOL { X_PLAYER = 'X', O_PLAYER = 'O' };

template <class T>
void Swap(T& x, T& y)
{
	T temp;

	temp = x;
	x = y;
	y = temp;
}

template <class T>
void Realloc(T*& arr, int& logSize, int& maxSize)
{
	int tmp = maxSize * 2 + 1;
	T* newArr = new T[tmp];

	for (int i = 0; i < logSize; ++i)
		newArr[i] = arr[i];

	delete[] arr;
	arr = newArr;
	maxSize = tmp;
}

struct Position
{
	int row;
	int col;
};

class Stone
{//Abstract class
protected:
	//Constructors
	Stone() = delete;
	Stone(const Position& pos, const char symbol, PLAYER_SYMBOL playerProperty, int index);
	Stone(const Stone& other);
	Stone(Stone&& other);
public:
	//Destructor
	virtual ~Stone();

	//Setters
	void SetPosition(const Position& pos);
	void SetStoneIndex(int index);

	//Getters
	char GetSymbol() const;
	const Position& GetPosition() const;
	vector<Position>& GetPossibleMoves();
	int GetNumOfPossibleMoves() const;
	PLAYER_SYMBOL GetPlayerProperty() const;
	int GetStoneIndexInArr() const;

	//Methods
	void DeletePossibleMoves();
	void AddPossibleMove(const Position& pos);

protected:
	char m_Symbol;
	Position m_Position;
	vector<Position> m_PossibleMoves;
	PLAYER_SYMBOL m_PlayerProperty;
	int m_StoneIndexInArr;
};

//Operators
 bool operator==(const Position& pos1, const Position& pos2);
 bool operator!=(const Position& pos1, const Position& pos2);
 ostream& operator<< (ostream& os, const Position& pos);
 istream& operator>> (istream& is, Position& pos);