#pragma once
#include "EnumHeader.h"

class Map
{
public:
	Map();
	virtual ~Map();

private:
	void MakeMap();
	void DeleteMap();

public:
	void InitMap();
	void PrintMapData();
	int  GetEachPosDataInMap(ShipPos inputShipPos);
	int  GetEachPosDataInMap(char x, char y);

	void SetEachPosDataInMap(ShipPos shipPos);
	//void SetEachPosDataInMap(char x, char y);

	void MarkAttackedPos(ShipPos AttackedPos);
	//void MarkAttackedPos(char x, char y);

private:
	int** m_Map;
};

