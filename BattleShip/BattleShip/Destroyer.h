#pragma once
#include "Ship.h"
class Destroyer :
	public Ship
{
public:
	Destroyer();
	virtual ~Destroyer();

	HitResult CheckAttack(ShipPos attackPos);
	void	  InitHP(){ m_HP = DESTROYER_HP; }
};

