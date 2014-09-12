#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	MakeMap();
}


Map::~Map()
{
	DeleteMap();
}


void Map::MakeMap()
{
	m_Map = new int*[MAX_HORIZONTAL];

	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		m_Map[i] = new int[MAX_VERTICAL];
	}
	return;
}

void Map::DeleteMap()
{
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		delete[] m_Map[i];
	}

	delete[] m_Map;
}

void Map::InitMap()
{

	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		memset(m_Map[i], 0, sizeof(int)*MAX_VERTICAL);
	}
	return;
}

void Map::PrintMapData()
{
	printf_s("\n");
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			printf_s("%d ", m_Map[i][j]);
		}
		printf_s("\n");
	}
}

int Map::GetEachPosDataInMap(ShipPos inputShipPos)
{
	_ASSERT(inputShipPos.x  <  MAX_HORIZONTAL &&
		    inputShipPos.x  >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y  <  MAX_VERTICAL &&
			inputShipPos.y  >= VERTICAL_ZERO);

	if (!(inputShipPos.x  <  MAX_HORIZONTAL &&
		  inputShipPos.x  >= HORIZONTAL_ZERO))
	{
		return MAP_NONE;
	}
	if (!(inputShipPos.y  <  MAX_VERTICAL &&
		  inputShipPos.y    >= VERTICAL_ZERO))
	{
		return MAP_NONE;
	}

	int tmpData = m_Map[inputShipPos.x][inputShipPos.y];

	return tmpData;
}

int Map::GetEachPosDataInMap(char _x, char _y)
{
	_ASSERT(_x < MAX_HORIZONTAL && _y >= HORIZONTAL_ZERO);
	_ASSERT(_x < MAX_VERTICAL && _y >= VERTICAL_ZERO);

	if (!(_x < MAX_HORIZONTAL && _y >= HORIZONTAL_ZERO) || !(_x < MAX_VERTICAL && _y >= VERTICAL_ZERO))
	{
		return MAP_NONE;
	}

	int tmpData = m_Map[_x][_y];
	return tmpData;

}



void Map::SetEachPosDataInMap(ShipPos inputShipPos)
{
	_ASSERT(inputShipPos.x < MAX_HORIZONTAL &&
		    inputShipPos.x >= HORIZONTAL_ZERO);
	_ASSERT(inputShipPos.y < MAX_VERTICAL &&
			inputShipPos.y >= VERTICAL_ZERO);

	if (!(inputShipPos.x < MAX_HORIZONTAL &&
		  inputShipPos.x >= HORIZONTAL_ZERO))
	{
		return;
	}
	if (!(inputShipPos.y < MAX_VERTICAL &&
		  inputShipPos.y >= VERTICAL_ZERO))
	{
		return;
	}
	m_Map[inputShipPos.x][inputShipPos.y] = SHIP_LAUNCH;

}

void Map::MarkAttackedPos(ShipPos AttackedPos)
{
	_ASSERT(AttackedPos.x < MAX_HORIZONTAL &&
		AttackedPos.x >= HORIZONTAL_ZERO);
	_ASSERT(AttackedPos.y < MAX_VERTICAL &&
		AttackedPos.y >= VERTICAL_ZERO);

	if (!(AttackedPos.x < MAX_HORIZONTAL &&
		  AttackedPos.x >= HORIZONTAL_ZERO))
	{
		printf_s("Attacking is not available to current pos\n");
		return;
	}
	if (!(AttackedPos.y < MAX_VERTICAL &&
		  AttackedPos.y >= VERTICAL_ZERO))
	{
		printf_s("Attacking is not available to current pos\n");
		return;
	}

	if (m_Map[AttackedPos.x][AttackedPos.y] == SHIP_LAUNCH)
	{
		m_Map[AttackedPos.x][AttackedPos.y] = SHIP_ATTACEKED;
	}
	else if (m_Map[AttackedPos.x][AttackedPos.y] == MAP_NONE)
	{
		m_Map[AttackedPos.x][AttackedPos.y] = MISSED_ATTACK;
	}
	else
	{
		printf_s("Attacking is not available to current pos\n");
	}
	
}
