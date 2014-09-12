#pragma once
#include "Ship.h"
class Cruiser :
	public Ship
{
public:
	Cruiser();
	virtual ~Cruiser();

	HitResult CheckAttack(ShipPos attackPos);
	void	  InitHP(){ m_HP = CRUISER_HP; }
};

