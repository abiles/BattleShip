#pragma once
#include <EnumHeader.h>
class Ship
{
public:
	Ship();
	virtual ~Ship();

public:

protected:
	int		m_Size;
	int		m_HP;
	ShipType	m_ShipType;
	std::string m_ShipName;
	ShipPos		m_Pos[MAX_SHIP_SIZE];
	ShipPos		m_ShipDir[MAX_DIRECTION];


};

