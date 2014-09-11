#include "stdafx.h"
#include "Cruiser.h"


Cruiser::Cruiser()
{
}


Cruiser::~Cruiser()
{
}

HitResult Cruiser::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? CRUISER_DESTROY : result;
}
