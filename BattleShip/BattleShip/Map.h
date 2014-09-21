#pragma once
#include "EnumHeader.h"

class Map
{
public:
	Map();
	virtual ~Map();

private:
	void	  MakeMap();
	void	  MakeIntMap();
	void	  DeleteMap();
	void	  DeleteIntMap();

public:
	void	  InitMap();
	void	  PrintMapData();
	char	  GetEachPosDataInMap(ShipPos inputShipPos);
	char	  GetEachPosDataInMap(char _x, char _y);

	void	  SetEachPosDataInMap(ShipPos inputShipPos);
	//void    SetEachPosDataInMap(char x, char y);
	void	  MarkAttackResult(ShipPos attackedPos, MapState inputMapState);

private:
	char    m_Map[MAX_HORIZONTAL][MAX_VERTICAL];
};

