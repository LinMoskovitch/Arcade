#include "AmazonCell.h"

//---------------------------------------Constructors---------------------------------------//
AmazonCell::AmazonCell()
	: Cell() , m_marked(false) {}

AmazonCell::AmazonCell(const AmazonCell & other)
	: Cell(other), m_marked(other.m_marked) {}

AmazonCell::AmazonCell(AmazonCell&& other)
	: Cell(other), m_marked(other.m_marked) {}

//---------------------------------------Destructor---------------------------------------//
AmazonCell::~AmazonCell(){}

//---------------------------------------Setters---------------------------------------//


//---------------------------------------Getters---------------------------------------//
bool AmazonCell::GetMarkedStatus() const
{
	return m_marked;
}

//---------------------------------------Methods---------------------------------------//
void AmazonCell::CellMarked()
{
	m_marked = true;
}