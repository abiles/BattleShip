#pragma once
#include "EnumHeader.h"

class Map
{
public:
	Map();
	virtual ~Map();

private:
	void MakeMap();
	void MakeIntMap();
	void DeleteMap();
	void DeleteIntMap();

public:
	void	  InitMap();
	void	  InitIntMap();
	void	  PrintMapData();
	MapState  GetEachPosDataInMap(ShipPos inputShipPos);
	int		  GetIntDataInMap(ShipPos inputShipPos);
	MapState  GetEachPosDataInMap(char _x, char _y);
	int		  GetIntDataInMap(char _x, char _y);

	void	  SetEachPosDataInMap(ShipPos inputShipPos);
	//void SetEachPosDataInMap(char x, char y);

	void	  SetEachPointInMap(ShipPos inputShipPos, int point);
	void	  SetEachPointInMap(char _x, char _y, int point);
	
	void	  PointPlusInintMap(ShipPos inputShipPos, int point);

	void	  MarkAttackResult(ShipPos attackedPos, MapState inputMapState);
private:
	MapState** m_Map;
	int**	   m_IntMap;
};

