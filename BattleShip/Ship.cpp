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
	for (int i = 0; i < MAX_SHIP_LENGTH; i++)
	{
		if (m_Pos[i].x == 0)
		{
			m_Pos[i] = pos;
			break;
		}
	}


	return;
	
}

void Ship::AddPosition(char x, char y)
{
	Position AddPos;

	AddPos.x = x;
	AddPos.y = y;

	AddPosition(AddPos);

}

void Ship::PrintHP()
{
	printf_s("HP of %s : %d \n", m_Name.c_str(), m_HP);
}

void Ship::Print()
{
	Position buf;

	printf_s("%s: ", m_Name.c_str());

	for (int i = 0; i < m_Size; i++)
	{
		buf = GetPos(i);

		printf_s("%c%c ", buf.x, buf.y);

	}

	printf_s("\n");
}


