#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::SetSize(int _size)
{
	_ASSERT(_size < MAX_SHIP_SIZE && _size > SHIP_SIZE_ZERO);

	if (!(_size < MAX_SHIP_SIZE && _size > SHIP_SIZE_ZERO))
	{
		printf_s("Wrong size input \n");
		m_Size = SHIP_SIZE_ZERO;
		return;
	}

	m_Size = _size;
}

void Ship::SetHP(int _HP)
{
	_ASSERT(_HP < MAX_HP && _HP > HP_ZERO);

	if (!(_HP < MAX_HP && _HP > HP_ZERO))
	{
		printf_s("Wrong HP input \n");
		m_HP = HP_ZERO;
		return;
	}

	m_HP = _HP;

}

void Ship::SetShipName(std::string _name)
{
	m_ShipName = _name;
}

void Ship::SetShipType(ShipType inputShipType)
{
	_ASSERT(inputShipType <SHIP_TYPE_END  && inputShipType > SHIP_TYPE_NONE);

	if (!(inputShipType < SHIP_TYPE_END && inputShipType > SHIP_TYPE_NONE))
	{
		printf_s("Wrong ShipType input \n");
		m_ShipType = SHIP_TYPE_NONE;
		return;
	}

	m_ShipType = inputShipType;
}


void Ship::MakeDir()
{
	m_ShipDir[NORTH] = { 0, -1 };
	m_ShipDir[EAST]  = { 1,  0 };
	m_ShipDir[SOUTH] = { 0,  1 };
	m_ShipDir[WEST]  = { 1,  0 };
}

ShipPos Ship::GetPos(int posIdx)
{
	_ASSERT(posIdx < MAX_SHIP_SIZE && posIdx >= 0);
	if (!(posIdx < MAX_SHIP_SIZE && posIdx >= 0))
	{
		ShipPos none_Pos;
		none_Pos.x = 0;
		none_Pos.y = 0;

		return none_Pos;
	}

	return m_Pos[posIdx];
}

bool Ship::AddPos(ShipPos inputPos, int posIdx)
{
	_ASSERT(inputPos.x <= MAX_HORIZONTAL &&
			inputPos.x > HORIZONTAL_ZERO);
	_ASSERT(inputPos.y <= MAX_VERTICAL &&
			inputPos.y > VERTICAL_ZERO);
	_ASSERT(posIdx < MAX_SHIP_SIZE && posIdx >= 0);

	if (!(inputPos.x <= MAX_HORIZONTAL &&
		inputPos.x > HORIZONTAL_ZERO))
	{
		inputPos.x = 0;
		inputPos.y = 0;
		m_Pos[posIdx] = inputPos;
		return false;
	}
	if (!(inputPos.y <= MAX_VERTICAL &&
		inputPos.y > VERTICAL_ZERO))
	{
		inputPos.x = 0;
		inputPos.y = 0;
		m_Pos[posIdx] = inputPos;
		return false;
	}
	if (!(posIdx < MAX_SHIP_SIZE && posIdx >= 0))
	{
		return false;
	}

	m_Pos[posIdx] = inputPos;
	return true;

}

OverLapCheck Ship::IsOverlap(ShipPos inputPos)
{
	_ASSERT(inputPos.x <= MAX_HORIZONTAL &&
		inputPos.x > HORIZONTAL_ZERO);
	_ASSERT(inputPos.y <= MAX_VERTICAL &&
		inputPos.y > VERTICAL_ZERO);

	if (!(inputPos.x <= MAX_HORIZONTAL &&
		inputPos.x > HORIZONTAL_ZERO))
	{
		return WRONGINPUT;
	}
	if (!(inputPos.y <= MAX_VERTICAL &&
		inputPos.y > VERTICAL_ZERO))
	{
		
		return WRONGINPUT;
	}

	for (int i = 0; i < m_Size; ++i)
	{
		if (inputPos.x == m_Pos[i].x && inputPos.y == m_Pos[i].y)
		{
			return OVERLAP;
		}

	}

	return OVERLAP_NONE;
}


