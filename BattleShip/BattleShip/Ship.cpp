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

