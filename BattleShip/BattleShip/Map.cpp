#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	
	//MakeMap();
	//MakeIntMap();
}


Map::~Map()
{
	//DeleteMap();
	//DeleteIntMap();
}


//void Map::MakeMap()
//{
//	m_Map = new char*[MAX_HORIZONTAL];
//
//	for (int i = 0; i < MAX_HORIZONTAL; ++i)
//	{
//		m_Map[i] = new char[MAX_VERTICAL];
//		
//	}
//
//	InitMap();
//	return;
//}
//
//void Map::DeleteMap()
//{
//	for (int i = 0; i < MAX_HORIZONTAL; ++i)
//	{
//		delete[] m_Map[i];
//		m_Map[i] = nullptr;
//	}
//
//	delete[] m_Map;
//	m_Map = nullptr;
//}
//
void Map::InitMap()
{

	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		memset(m_Map[i], 0, sizeof(char)*MAX_VERTICAL);
	}
	return;
}

void Map::PrintMapData()
{
	std::string tmpStr;


	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		printf_s("\t\t\t\t");
		if (i == 0)
		{
			printf_s("  ");
			for (int k = 0; k < MAX_VERTICAL; ++k)
			{
				printf_s("%d ", k);
			}
			printf_s("\n");
			printf_s("\t\t\t\t");
		}
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			if (j == 0)
			{
				
				printf_s("%c ", 'a' + i);
			}

			if (m_Map[i][j] == MAP_NONE)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
				tmpStr = "■";
			}
			else if (m_Map[i][j] == SHIP_LAUNCH)
			{
				tmpStr = "Д" ;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0006);
			}
			else if (m_Map[i][j] == SHIP_ATTACEKED)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004);
				tmpStr = "▣";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0001);
				tmpStr = "□";
			}
			printf_s("%s", tmpStr.c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0008);
		}
		
		printf_s("\n");
	}
}

char Map::GetEachPosDataInMap(ShipPos inputShipPos)
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

	char tmpData = m_Map[inputShipPos.x][inputShipPos.y];

	return tmpData;
}

char Map::GetEachPosDataInMap(char _x, char _y)
{
	_ASSERT(_x < MAX_HORIZONTAL && _x >= HORIZONTAL_ZERO);
	_ASSERT(_y < MAX_VERTICAL && _y >= VERTICAL_ZERO);

	if (!(_x < MAX_HORIZONTAL && _x >= HORIZONTAL_ZERO) || !(_y < MAX_VERTICAL && _y >= VERTICAL_ZERO))
	{
		return MAP_NONE;
	}

	char tmpData = m_Map[_x][_y];
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






