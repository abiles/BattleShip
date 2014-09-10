#pragma once

#include "EnumHeader.h"

class Ship
{
public:
	Ship();
	virtual ~Ship();

public:
	int				  GetSize() const { return m_Size; }
	void			  SetSize(int _size);

	int				  GetHP() const { return m_HP; }
	void			  SetHP(int _HP);

	std::string		  GetShipName() const { return m_ShipName; }
	void			  SetShipName(std::string _name);

	ShipType		  GetShipType() const { return m_ShipType; }
	void			  SetShipType(ShipType inputShipType);

	ShipPos			  GetPos(int posIdx);
	bool			  AddPos(ShipPos inputPos, int posIdx);

	OverLapCheck 	  IsOverlap(ShipPos inputPos);

	void		      MakeDir();

	virtual HitResult CheckAttack(ShipPos attackedPos);

protected:
	int			m_Size;
	int			m_HP;
	std::string m_ShipName;
	ShipType	m_ShipType;
	ShipPos		m_Pos[MAX_SHIP_SIZE];
	ShipPos		m_ShipDir[MAX_DIRECTION];


};

