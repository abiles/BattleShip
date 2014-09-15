#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
	MakeDir();
}


Ship::~Ship()
{

}

void Ship::SetSize(int _size)
{
	_ASSERT(_size < MAX_SHIP_SIZE && _size > SHIP_SIZE_ZERO);

	if (!(_size < MAX_SHIP_SIZE && _size > SHIP_SIZE_ZERO))
	{
		//printf_s("Wrong size input \n");
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
		//printf_s("Wrong HP input \n");
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
		//printf_s("Wrong ShipType input \n");
		m_ShipType = SHIP_TYPE_NONE;
		return;
	}

	m_ShipType = inputShipType;
}


void Ship::MakeDir()
{
	m_ShipDir[NORTH]		  = { 0, -1 };
	m_ShipDir[EAST]			  = { 1,  0 };
	m_ShipDir[SOUTH]		  = { 0,  1 };
	m_ShipDir[WEST]			  = {-1,  0 };
	
}

ShipPos Ship::GetPos(int posIdx)
{
	_ASSERT(posIdx < MAX_SHIP_SIZE && posIdx >= 0);
	if (!(posIdx < MAX_SHIP_SIZE && posIdx >= 0))
	{
		ShipPos none_Pos;
		none_Pos.x = -1;
		none_Pos.y = -1;

		return none_Pos;
	}

	return m_Pos[posIdx];
}

bool Ship::AddPos(ShipPos inputPos, int posIdx)
{
	_ASSERT(inputPos.x < MAX_HORIZONTAL &&
			inputPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputPos.y < MAX_VERTICAL &&
			inputPos.y >= VERTICAL_ZERO);
	_ASSERT(posIdx < MAX_SHIP_SIZE && posIdx >= 0);

	if (!(inputPos.x < MAX_HORIZONTAL &&
		inputPos.x >= HORIZONTAL_ZERO))
	{
		inputPos.x = -1;
		inputPos.y = -1;
		m_Pos[posIdx] = inputPos;
		return false;
	}
	if (!(inputPos.y < MAX_VERTICAL &&
		inputPos.y >= VERTICAL_ZERO))
	{
		inputPos.x = -1;
		inputPos.y = -1;
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

bool Ship::IsPosFull()
{
	
	for (int i = 0; i < m_Size; ++i)
	{
		if (m_Pos[i].x == -1 || m_Pos[i].y == -1)
		{
			return false;
		}
	}

	return true;
	
}

OverLapCheck Ship::IsOverlap(ShipPos inputPos)
{
	_ASSERT(inputPos.x < MAX_HORIZONTAL &&
		inputPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputPos.y < MAX_VERTICAL &&
		inputPos.y >= VERTICAL_ZERO);

	if (!(inputPos.x  < MAX_HORIZONTAL &&
		inputPos.x >= HORIZONTAL_ZERO))
	{
		return WRONGINPUT;
	}
	if (!(inputPos.y < MAX_VERTICAL &&
		inputPos.y >= VERTICAL_ZERO))
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

ShipPos Ship::GetDirPos(ShipDirection inputDir)
{
	_ASSERT(inputDir < MAX_DIRECTION && inputDir >= NORTH);
	if (!(inputDir < MAX_DIRECTION && inputDir >= NORTH))
	{
		ShipPos none_Pos;
		none_Pos.x = -1;
		none_Pos.y = -1;
		return  none_Pos;
	}

	return m_ShipDir[inputDir];

}

void Ship::InitPos()
{
	for (int i = 0; i < m_Size; ++i)
	{
		m_Pos[i].x = -1;
		m_Pos[i].y = -1;
	}
}

HitResult Ship::CheckAttack(ShipPos attackedPos)
{
	_ASSERT(attackedPos.x < MAX_HORIZONTAL && attackedPos.x >= HORIZONTAL_ZERO);
	_ASSERT(attackedPos.y < MAX_VERTICAL && attackedPos.y >= VERTICAL_ZERO);
	if (!(attackedPos.x < MAX_HORIZONTAL &&
		attackedPos.x >= HORIZONTAL_ZERO))
	{
		return HIT_NONE;
	}
	if (!(attackedPos.y < MAX_VERTICAL &&
		attackedPos.y >= VERTICAL_ZERO))
	{
		return HIT_NONE;
	}

	for (int i = 0; i < GetSize(); ++i)
	{
		if (GetPos(i).x == attackedPos.x && GetPos(i).y == attackedPos.y)
		{
			HitResultApply();

			if (GetHP() == 0)
			{
				return DESTROY;
			}
			return HIT;
		}
	}

	return HIT_NONE;
}

void Ship::HitResultApply()
{
	--m_HP;
}

void Ship::PrintShipPos()
{
	char tmpChar = 0;
	printf_s("%s\t:\t", m_ShipName.c_str());

	for (int i = 0; i < m_Size; ++i)
	{
		if (m_Pos[i].x == -1)
		{
			break;
		}
		tmpChar = m_Pos[i].x + 'a';
		
		printf_s("%c%d\t", tmpChar, m_Pos[i].y);
	}
	printf_s("\t\t\t\t");
	printf_s("\n");
}




