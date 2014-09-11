#include "stdafx.h"
#include "BattleShip.h"


BattleShip::BattleShip()
{
}


BattleShip::~BattleShip()
{
}

HitResult BattleShip::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? BATTLESHIP_DESTROY : result;
}

