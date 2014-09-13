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
	void	  InitMap();
	void	  PrintMapData();
	MapState  GetEachPosDataInMap(ShipPos inputShipPos);
	MapState  GetEachPosDataInMap(char x, char y);

	void SetEachPosDataInMap(ShipPos shipPos);
	//void SetEachPosDataInMap(char x, char y);


	void MarkAttackResult(ShipPos attackedPos, MapState inputMapState);
private:
	MapState** m_Map;
};

