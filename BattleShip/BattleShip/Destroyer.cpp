#include "stdafx.h"
#include "Destroyer.h"


Destroyer::Destroyer()
{
}


Destroyer::~Destroyer()
{
}

HitResult Destroyer::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? DESTROYER_DESTROY : result;
}
