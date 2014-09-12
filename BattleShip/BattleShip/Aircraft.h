#pragma once
#include "Ship.h"
class Aircraft :
	public Ship
{
public:
	Aircraft();
	virtual ~Aircraft();

	HitResult CheckAttack(ShipPos attackPos);
	void	  InitHP(){ m_HP = AIRCRAFT_HP; }

};