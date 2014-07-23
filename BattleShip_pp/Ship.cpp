#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
	memset(m_Pos, 0, sizeof(Position)*5);
}


Ship::~Ship()
{

}

void Ship::AddPosition(Position pos)
{
	int i = 0;

	for (i = 0; m_Pos[i].x && m_Pos[i].y; i++);

	m_Pos[i] = pos;


	return;
	
}

void Ship::PrintHP()
{
	printf_s("HP of %s : %d \n", m_Name.c_str(), m_HP);
}


