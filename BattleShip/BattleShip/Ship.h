#pragma once

#include "EnumHeader.h"

class Ship
{
public:
	Ship();
	virtual ~Ship();

public:
	int			GetSize() const { return m_Size; }
	void		SetSize(int _size);

	int			GetHP() const { return m_HP; }
	void		SetHP(int _HP);

	std::string GetShipName() const { return m_ShipName; }
	void		SetShipName(std::string _name);


protected:
	int			m_Size;
	int			m_HP;
	ShipType	m_ShipType;
	std::string m_ShipName;
	ShipPos		m_Pos[MAX_SHIP_SIZE];
	ShipPos		m_ShipDir[MAX_DIRECTION];


};

