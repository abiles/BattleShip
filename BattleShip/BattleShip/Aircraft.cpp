#include "stdafx.h"
#include "Aircraft.h"


Aircraft::Aircraft()
{
}


Aircraft::~Aircraft()
{
}

HitResult Aircraft::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? AIRCRAFT_DESTROY : result;
}
