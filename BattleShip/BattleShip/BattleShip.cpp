#include "stdafx.h"
#include "BattleShip.h"


BattleShip::BattleShip()
{
	m_ShipType = BATTLESHIP;
	m_ShipName = "BattleShip";
	m_Size = BATTLESHIP_SZIE;
	m_HP = BATTLESHIP_HP;
}


BattleShip::~BattleShip()
{
}

HitResult BattleShip::CheckAttack(ShipPos attackPos)
{
	HitResult result = Ship::CheckAttack(attackPos);

	return (result == DESTROY) ? BATTLESHIP_DESTROY : result;
}

