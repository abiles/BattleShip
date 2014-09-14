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
	m_Map = new MapState*[MAX_HORIZONTAL];

	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		m_Map[i] = new MapState[MAX_VERTICAL];
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
		memset(m_Map[i], MAP_NONE, sizeof(int)*MAX_VERTICAL);
	}
	return;
}

void Map::PrintMapData()
{
	
	
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			printf_s("%d ", m_Map[i][j]);
		}
		printf_s("\n");
	}
}

MapState Map::GetEachPosDataInMap(ShipPos inputShipPos)
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

	MapState tmpData = m_Map[inputShipPos.x][inputShipPos.y];

	return tmpData;
}

MapState Map::GetEachPosDataInMap(char _x, char _y)
{
	_ASSERT(_x < MAX_HORIZONTAL && _y >= HORIZONTAL_ZERO);
	_ASSERT(_x < MAX_VERTICAL && _y >= VERTICAL_ZERO);

	if (!(_x < MAX_HORIZONTAL && _x >= HORIZONTAL_ZERO) || !(_y < MAX_VERTICAL && _y >= VERTICAL_ZERO))
	{
		return MAP_NONE;
	}

	MapState tmpData = m_Map[_x][_y];
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



void Map::MarkAttackResult(ShipPos attackedPos, MapState inputMapState)
{
	_ASSERT(attackedPos.x < MAX_HORIZONTAL &&
		attackedPos.x >= HORIZONTAL_ZERO);
	_ASSERT(attackedPos.y < MAX_VERTICAL &&
		attackedPos.y >= VERTICAL_ZERO);

	if (!(attackedPos.x < MAX_HORIZONTAL &&
		attackedPos.x >= HORIZONTAL_ZERO))
	{
		//printf_s("Attacking is not available to current pos\n");
		return;
	}
	if (!(attackedPos.y < MAX_VERTICAL &&
		attackedPos.y >= VERTICAL_ZERO))
	{
		//printf_s("Attacking is not available to current pos\n");
		return;
	}

	//attack result에 따라서 위치에 표시만 하는거야돼 이전에 판단은 player에서 해서 와야지 

	m_Map[attackedPos.x][attackedPos.y] = inputMapState;
}
