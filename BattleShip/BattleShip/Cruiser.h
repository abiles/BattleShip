#pragma once
#include "Ship.h"
class Cruiser :
	public Ship
{
public:
	Cruiser();
	virtual ~Cruiser();

	HitResult CheckAttack(ShipPos attackPos);
};

